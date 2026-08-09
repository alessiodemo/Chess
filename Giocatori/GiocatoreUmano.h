//Veneziani Michele 2007955
#ifndef GIOCATOREUMANO_H
#define GIOCATOREUMANO_H
#include "../Scacchiera/chess.h"
#include <fstream>
#include <ctime>
class GiocatoreUmano
{
   public:
      /*
         Costruttore di default che imposta come colore del giocatore un colore random
      */
      GiocatoreUmano();
      /*
         Costruttore per impostare color e trasform (il secondo viene messo di default a 'D' per indicare la donna)
      */
      GiocatoreUmano(std::string colore, char c = 'D');
      /*
         Effettua il movimento di un pezzo dalla casella indicata dalla stringa partenza alla casella indicata dalla stringa arrivo e salva
         i movimenti sul file tramite il parametro is. Considera valide le caselle di partenza e di arrivo
      */
      void move(chessTable& scacchiera, std::string partenza, std::string arrivo, std::ofstream& is);
      /*
         Effettua il movimento di un pezzo dalla casella indicata dalla stringa partenza alla casella indicata dalla stringa arrivo. Considera
         valide le caselle di partenza e di arrivo
      */
      void move(chessTable& scacchiera, std::string partenza, std::string arrivo);
      /*
         Ritorna il valore di color
      */
      std::string getColor();
      /*
         Setta color in base al parametro dato
      */
      void setColor(std::string colore);
      /*
      	Ritorna il valore di transform
      */
      char getTransform();
      /*
         Setta transform in base al parametro dato
      */
      void setTransform(char c);
		/*
			Ritorna il valore di checkPedestrian
		*/
      int getCheckPedestrian();
		/*
         Setta checkPedestrian in base al parametro dato
      */
      void setCheckPedestrian(int i);
      /*
			Ritorna il valore di checkAte
		*/
      int getCheckAte();
		/*
         Setta checkAte in base al parametro dato
      */
      void setCheckAte(int i);

   protected:
		/*
      	Metodo che effettua la ricerca delle mosse di tutti i pezzi
      */
      void ricercaMosse(chessTable& scacchiera);
      /*
      	Metodo che setta le variabili necessarie per l'arrocco passate tramite riferimento e restituisce true se la mossa scelta casualmente è l'arrocco
      */
      bool arroccoElements(Pezzo* pe, int colonnaPartenza, int colonnaArrivo, int& rigaPartenzaArrocco, int& colonnaPartenzaArrocco, Pair& coppiaArrocco);
      /*
         Metodo che aggiorna i valori di checkPedestrian e checkAte per il controllo della patta
      */
      void checkPatta(chessTable& scacchiera, Pair partenza, Pair arrivo);
      /*
         color indica il colore del giocatore che può essere Bianco o Nero
      */
      std::string color;
      /*
      	transform indica il pezzo in cui il pedone si deve trasformare nella promozione
      */
      char transform;
		/*
      	checkPedestrian indica il numero di mosse consecutive avvenute nella partita in cui non viene mosso nessun pedone
      */
      static int checkPedestrian;
		/*
      	checkAte indica il numero di mosse consecutive avvenute nella partita in cui non viene mangiato nessun pezzo
      */
      static int checkAte;
};
#endif
