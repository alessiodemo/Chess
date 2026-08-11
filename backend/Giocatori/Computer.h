//Veneziani Michele 2007955
#ifndef COMPUTER_H
#define COMPUTER_H
#include "GiocatoreUmano.h"
class Computer:public GiocatoreUmano
{
   public:
      /*
         Costruttore per impostare color, trasform (viene messo di default a 'D' per indicare la donna) e max (viene messo di default a 1000)
      */
      Computer(std::string colore, char c = 'D', int massimo = 1500);
      /*
         Costruttore per impostare trasform (viene messo di default a 'D' per indicare la donna) e max (viene messo di default a 1000)
      */
      Computer(char c = 'D', int massimo = 1500);
      /*
         Effettua la mossa di un pezzo casuale in una casella casuale e salva i movimenti sul file tramite il parametro is.
      */
      void move(chessTable& scacchiera, std::ofstream& is);
      /*
         Ritorna il valore di max
      */
      int getMax();
      /*
         Setta max in base al parametro dato
      */
      void setMax(int massimo);
   private:
      /*
         max indica il numero massimo di mosse che il singolo computer può fare
      */
      int max;
};
#endif
