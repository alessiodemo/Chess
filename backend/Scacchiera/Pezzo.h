//Veneziani Michele 2007955
#ifndef PEZZO_H
#define PEZZO_H
#include <iostream>
#include "Pair.h"
#include <list>
class Pezzo
{
	private:
		/*
         name indica il nome del pezzo
      */
		char name;
		/*
         color indica il colore del pezzo che può essere Bianco o Nero
      */
      std::string color;
      /*
         current_position indica la casella in cui si trova il pezzo attualmente
      */
      Pair current_position;
      /*
         available_actions indica la lista di caselle in cui può andare il pezzo
      */
      std::list<Pair> available_actions;
      /*
         numMosse indica il numero di mosse effettuato dal pezzo
      */
      int numMosse;
	public:
		/*
			Costruttore per impostare name, color (se la lettera è maiuscola allora il pezzo è nero, altrimenti è bianco), current_position, available_actions a una
         lista vuota e numMosse a 0 di default
		*/
		Pezzo(char n, Pair pa, int number = 0);
		/*
         Costruttore per impostare name, color (se la lettera è maiuscola allora il pezzo è nero, altrimenti è bianco), current_position, available_actions e numMosse
		*/
		Pezzo(char n, Pair pa, std::list<Pair> lista, int number = 0);
		/*
      	Ritorna il valore di name
      */
		char getName();
		/*
         Setta name in base al parametro dato
      */
		void setName(char n);
		/*
      	Ritorna il valore di color
      */
		std::string getColor();
		/*
         Setta color in base al parametro dato
      */
		void setColor(string colore);
		/*
      	Ritorna il valore di current_position
      */
		Pair getCurrent_position();
		/*
         Setta current_position in base al parametro dato
      */
		void setCurrent_position(Pair pa);
		/*
      	Ritorna il valore di available_actions
      */
		std::list<Pair>& getAvailable_actions();
		/*
         Elimina tutti i valori contenuti in available_actions
      */
		void setAvailable_actions();
		/*
         Setta available_actions in base al parametro dato
      */
		void setAvailable_actions(Pair pa);
		/*
      	Ritorna il valore di numMosse
      */
		int getNumMosse();
		/*
         Setta numMosse in base al parametro dato
      */
		void setNumMosse(int number);
};
#endif
