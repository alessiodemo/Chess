#include "GameSession.h"
#include "../Partite/Metodi.h"   // isMoveCorrect()
#include <cctype>
#include <cstdlib>
#include <ctime>

namespace
{
    std::string pieceCode(char nome)
    {
        bool nero = std::isupper(static_cast<unsigned char>(nome));
        char lettera = std::toupper(static_cast<unsigned char>(nome));
        char tipo;

        switch (lettera)
        {
            case 'T': tipo= 'R'; break; //Torre -> Rook
            case 'C': tipo= 'N'; break; //Cavallo -> Knight
            case 'A': tipo= 'B'; break; //Alfiere -> Bishop
            case 'D': tipo= 'Q'; break; //Donna -> Queen
            case 'P': tipo= 'P'; break; //Pedone -> Pawn
            case 'R': tipo= 'K'; break; //Re -> King
        }
        std::string codice;
        codice += (nero ? 'b' : 'w');
        codice += tipo;
        return codice;
    }

    std::string squareName(int riga, int colonna)
    {
        std::string s;
        s += static_cast<char>('a' + colonna);
        s += static_cast<char>('0' + (8-riga));
        return s;
    }
}

GameSession::GameSession(const std::string& id, const std::string& mode, std::string humanColor) 
    : id(id), mode(mode), chessboard(), log("WebLog" + id + ".txt"),
      humanPlayer(nullptr), pcPlayer(nullptr), computerBianco(nullptr), computerNero(nullptr), turn("Bianco"), over(false)

{

     if (mode == "pc")
    {
        if (humanColor != "Bianco" && humanColor != "Nero")
        {
            srand(static_cast<unsigned>(time(nullptr)));
            humanColor = (rand() % 2 == 0) ? "Bianco" : "Nero";
        }
        std::string computerColor = (humanColor == "Bianco") ? "Nero" : "Bianco";
        humanPlayer = new GiocatoreUmano(humanColor, 'D');
        pcPlayer = new Computer(computerColor, 'D', 1500);
    }
    else // "cc"
    {
        computerBianco = new Computer("Bianco", 'D', 1500);
        computerNero = new Computer("Nero", 'D', 1500);
    }
}

GameSession::~GameSession()
{
    delete humanPlayer;
    delete pcPlayer;
    delete computerBianco;
    delete computerNero;
}

bool GameSession::isComputerTurn() const
{
    if (mode == "cc") return true;
    return (pcPlayer != nullptr) && (turn == pcPlayer->getColor());
}

bool GameSession::applyHumanMove(std::string from, std::string to)
{
    if (over || mode != "pc" || isComputerTurn() || humanPlayer == nullptr || from.size() < 2 || to.size() < 2)
        return false;

    // normalizzo il case, come fa GiocatoreUmano::move internamente con std::toupper()
    from[0] = static_cast<char>(std::toupper(static_cast<unsigned char>(from[0])));
    to[0]   = static_cast<char>(std::toupper(static_cast<unsigned char>(to[0])));

    bool mossaValida = isMoveCorrect(from) && isMoveCorrect(to)
                     && chessboard.checkMove(from, to)
                     && chessboard.check_start(from, humanPlayer->getColor());
    if (!mossaValida)
        return false;

    humanPlayer->move(chessboard, from, to, log);
    afterHalfMove(humanPlayer->getColor(), from, to);
    return true;
}

void GameSession::computerMove()
{
    if (over) return;

    Computer* attore = (mode == "pc") ? pcPlayer
                                        : (turn == "Bianco" ? computerBianco : computerNero);
    if (attore == nullptr) return;

    attore->move(chessboard, log);
    // Computer::move non restituisce le case toccate: per la UI web ridisegniamo
    // l'intera scacchiera invece di animare la singola mossa del computer.
    afterHalfMove(
    attore->getColor(),
    attore->getLastMoveFrom(),
    attore->getLastMoveTo()
    );
}

void GameSession::afterHalfMove(const std::string& moverColor, const std::string& from, const std::string& to)
{
    if (!from.empty())
        history.push_back(from + " " + to);

    std::string avversario = (moverColor == "Bianco") ? "Nero" : "Bianco";

    GiocatoreUmano* riferimentoPatta = (mode == "pc") ? humanPlayer : static_cast<GiocatoreUmano*>(computerBianco);

    if (chessboard.scacco_matto(avversario))
    {
        over = true;
        status = "HA VINTO IL " + moverColor;
    }
    else if (chessboard.patta2())
    {
        over = true;
        status = "PATTA PER STALLO";
    }
    else if (chessboard.patta(riferimentoPatta->getCheckPedestrian(), riferimentoPatta->getCheckAte()))
    {
        over = true;
        status = "PATTA PER LA REGOLA DELLE 50 MOSSE";
    }
    else if (history.size() >= 300) // rete di sicurezza: evita partite infinite in modalita' "cc"
    {
        over = true;
        status = "PARTITA INTERROTTA: LIMITE MOSSE RAGGIUNTO";
    }
    else
    {
        turn = avversario;
    }
}

std::string GameSession::toJSON() const
{
    std::string json = "{";
    json += "\"id\":\"" + id + "\",";
    json += "\"mode\":\"" + mode + "\",";
    json += "\"turn\":\"" + turn + "\",";
    json += "\"over\":" + std::string(over ? "true" : "false") + ",";
    json += "\"status\":\"" + status + "\",";
    json += "\"isComputerTurn\":" + std::string(isComputerTurn() ? "true" : "false") + ",";

    json += "\"history\":[";
    for (size_t i = 0; i < history.size(); i++)
    {
        if (i > 0) json += ",";
        json += "\"" + history[i] + "\"";
    }
    json += "],";

    json += "\"position\":{";
    bool primo = true;
    for (int riga = 0; riga < 8; riga++)
    {
        for (int colonna = 0; colonna < 8; colonna++)
        {
            Pezzo* pe = chessboard.getValue(Pair(riga, colonna));
            if (pe == nullptr) continue;
            if (!primo) json += ",";
            primo = false;
            json += "\"" + squareName(riga, colonna) + "\":\"" + pieceCode(pe->getName()) + "\"";
        }
    }
    json += "}}";
    return json;
}

