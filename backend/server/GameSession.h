#ifndef GAME_SESSION_H
#define GAME_SESSION_H

#include <string>
#include <vector>
#include <fstream>
#include "../Scacchiera/chess.h"
#include "../Giocatori/Computer.h"
#include "../Giocatori/GiocatoreUmano.h"

class GameSession {

    //constructor
    public:
        GameSession(const std::string& id, const std::string& mode, std::string humanColor="");

        ~GameSession();
    
        //applica una mossa di un umano
        bool applyHumanMove(std::string from, std::string to);

        //fa muovere il computer
        void computerMove();

        bool isOver() const { return over; }
        std::string statusMessage() const { return status; }

        //true se è il turno del pc per fare la prossima mossa (in modalità cc sempre true)
        bool isComputerTurn() const;
        
        //serializzazione infos in json format
        std::string toJSON() const;

    private: 
        void afterHalfMove(const std::string& moverColor, const std::string& from, const std::string& to);

        std::string id;
        std::string mode;
        chessTable chessboard;
        std::ofstream log;

        //usati in modalità pc
        GiocatoreUmano* humanPlayer;
        Computer* pcPlayer;

        //usati in modalità cc
        Computer* computerBianco;
        Computer* computerNero;

        std::string turn;
        bool over;std::string status;
        std::vector<std::string> history;

};

#endif