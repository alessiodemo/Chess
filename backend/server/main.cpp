#include "httplib.h" // from third_party/httplib, added to include path in CMakeLists.txt
#include "GameSession.h"
#include <map>
#include <memory>
#include <mutex>
#include <iostream>

static std::map<std::string, std::unique_ptr<GameSession>> sessions;
static std::mutex mutex_sessioni;
static int prossimoId = 1;

static void inviaErrore(httplib::Response& res, int codice, const std::string& messaggio) {
    res.status = codice;
    res.set_content("{\"error\":\"" + messaggio + "\"}", "application/json");
}

int main() {
    httplib::Server server;

    server.Post("/api/games", [](const httplib::Request& req, httplib::Response& res) {
        std::string mode = req.has_param("mode") ? req.get_param_value("mode") : "pc";
        std::string colore = req.has_param("color") ? req.get_param_value("color") : "";
        if(mode != "pc" && mode != "cc" ) {
            inviaErrore(res, 400, "mode deve essere 'pc' o 'cc'");
            return;
        }

        std::lock_guard<std::mutex> lock(mutex_sessioni);
        std::string id ="g" + std::to_string(prossimoId++);
        auto sessione = std::make_unique<GameSession>(id, mode, colore); 

        if(!sessione->isOver() && sessione->isComputerTurn()) 
            sessione->computerMove();
        
        std::string json = sessione->toJSON();
        sessions[id] = std::move(sessione);
        res.set_content(json, "application/json");
    });

    server.Delete(R"(/api/games/([^/]+))", [](const httplib::Request& req, httplib::Response& res) {
        std::lock_guard<std::mutex> lock(mutex_sessioni);
        auto it = sessions.find(req.matches[1].str());
        if(it == sessions.end()) {inviaErrore(res, 404, "Partita non trovata"); return;}
        sessions.erase(it);

        res.status = 200;
        std::string json = "{\"deleted\":true}";
        res.set_content(json, "application/json");
    });

    server.Get(R"(/api/games/([^/]+))",[](const httplib::Request& req, httplib::Response& res) {
        std::lock_guard<std::mutex> lock(mutex_sessioni);
        auto it = sessions.find(req.matches[1].str());
        if(it == sessions.end()) {inviaErrore(res, 404, "Partita non trovata"); return;}
        res.set_content(it->second->toJSON(), "application/json");

    });

    
    server.Post(R"(/api/games/([^/]+)/move)", [](const httplib::Request& req, httplib::Response& res)
    {
        std::lock_guard<std::mutex> lock(mutex_sessioni);
        auto it = sessions.find(req.matches[1].str());
        if (it == sessions.end()) { inviaErrore(res, 404, "partita non trovata"); return; }

        GameSession& sessione = *it->second;
        std::string from = req.get_param_value("from");
        std::string to = req.get_param_value("to");

        if (!sessione.applyHumanMove(from, to))
        {
            inviaErrore(res, 400, "mossa non valida");
            return;
        }
        if (!sessione.isOver())
            sessione.computerMove();

        res.set_content(sessione.toJSON(), "application/json");
    });

    server.Post(R"(/api/games/([^/]+)/step)", [](const httplib::Request& req, httplib::Response& res)
    {
        std::lock_guard<std::mutex> lock(mutex_sessioni);
        auto it = sessions.find(req.matches[1].str());
        if (it == sessions.end()) { inviaErrore(res, 404, "partita non trovata"); return; }

        GameSession& sessione = *it->second;
        if (!sessione.isOver())
            sessione.computerMove();

        res.set_content(sessione.toJSON(), "application/json");
    });

    std::cout << "Server avviato: apri http://127.0.0.1:8080 nel browser (lancia il .exe dalla cartella principale del progetto!)" << std::endl;
    server.listen("0.0.0.0", 8080);
    return 0;
}