//Veneziani Michele 2007955
#include "Computer.h"
#include <thread>
Computer::Computer(std::string colore, char c, int massimo)
{
   setColor(colore);
   setMax(massimo);
   setTransform(c);
}
Computer::Computer(char c, int massimo)
{
   setMax(massimo);
   srand(time(NULL));
   int random = rand() % 2;
   if (random == 0)
      setColor("Bianco");
   else
      setColor("Nero");
   setTransform(c);
}
void Computer::move(chessTable& scacchiera, std::ofstream& is)
{
   srand(time(NULL));

   int indicePartenza;
   int indiceArrivo;
   int rigaPartenza;
   int colonnaPartenza;
   Pair coppiaArrivo;
   Pezzo* pezzo_casella_partenza;
   
   //Variabili per scrivere nel file
   std::string partenza = "";
   std::string arrivo = "";
   
   //Iteratori per scorrere le rispettive liste
   std::list<Pezzo*>::iterator itPezzo;
   std::list<Pezzo*> listaPezzi;
   std::list<Pair>::iterator itPair;
   std::list<Pair> lista;
   
   //Variabili utilizzate nell'arrocco
   Pezzo* arrocco_;
   int rigaPartenzaArrocco;
   int colonnaPartenzaArrocco;
   Pair coppiaArrocco;
   bool checkArrocco;
   
   //listaPezzi contiene i pezzi con il colore del giocatore che hanno almeno una mossa disponibile
   if (getColor() == "Nero")
      listaPezzi = scacchiera.getListNero();
   else
      listaPezzi = scacchiera.getListBianco();
      
   if(listaPezzi.size() != 0)
   {
		std::list<Pezzo*> help = scacchiera.getHelp();
		std::list<Pezzo*>::iterator itHelp = help.begin();
		
		//Pezzi obbligati a muoversi nel caso in cui il re dello stesso giocatore si trovi sotto scacco
		if (!help.empty())
		{
			//Scelta casuale del pezzo
			int indiceHelp = rand() % help.size();
			for (int i = 0; i < indiceHelp; ++i)
				itHelp++;
			pezzo_casella_partenza = *itHelp;
			rigaPartenza = pezzo_casella_partenza->getCurrent_position().getLine();
			colonnaPartenza = pezzo_casella_partenza->getCurrent_position().getColumn();
			
			//Scelta casuale della mossa tra quelle disponibili  
			int indiceMosseHelp = rand() % (pezzo_casella_partenza->getAvailable_actions()).size();
			std::list<Pair>::iterator itHelpPair = (pezzo_casella_partenza->getAvailable_actions()).begin();
			for (int i = 0; i < indiceMosseHelp; ++i)
				itHelpPair++;
			Pair paScacco = *itHelpPair;
         coppiaArrivo = paScacco;
		}
		else
		{
			//Istruzione per rendere più casuale la scelta dei pezzi
			std::this_thread::sleep_for(chrono::milliseconds(200));
			
			//Scelta casuale del pezzo
			indicePartenza = rand() % listaPezzi.size();
			itPezzo = listaPezzi.begin();
			for (int i = 0; i < indicePartenza; ++i)
				itPezzo++;
			pezzo_casella_partenza = *itPezzo;
			rigaPartenza = pezzo_casella_partenza->getCurrent_position().getLine();
			colonnaPartenza = pezzo_casella_partenza->getCurrent_position().getColumn();
               
			//Scelta casuale della mossa tra quelle disponibili  
			indiceArrivo = rand() % (pezzo_casella_partenza->getAvailable_actions()).size();
			itPair = (pezzo_casella_partenza->getAvailable_actions()).begin();
			for (int i = 0; i < indiceArrivo; i++)
				itPair++;
			coppiaArrivo = *itPair;    
			checkArrocco = arroccoElements(pezzo_casella_partenza, colonnaPartenza, coppiaArrivo.getColumn(), rigaPartenzaArrocco, colonnaPartenzaArrocco, coppiaArrocco);
      }
		checkPatta(scacchiera, Pair(rigaPartenza, colonnaPartenza), coppiaArrivo);
		
		//Effettuo la mossa del pezzo scelto, rendo vuota la casella di partenza e incremento il numero di mosse effettuate dal pezzo di 1
		pezzo_casella_partenza = new Pezzo(pezzo_casella_partenza->getName(), coppiaArrivo, pezzo_casella_partenza->getNumMosse());
		scacchiera.setValue(coppiaArrivo, pezzo_casella_partenza);
		scacchiera.setValue(Pair(rigaPartenza, colonnaPartenza), nullptr);
		pezzo_casella_partenza->setNumMosse(pezzo_casella_partenza->getNumMosse() +  1);
         
		//Inserisco la mossa nel file
		partenza.push_back(colonnaPartenza + 65);
		partenza.push_back(-1 * rigaPartenza + 56);
		arrivo.push_back(coppiaArrivo.getColumn() + 65);
		arrivo.push_back(-1 * coppiaArrivo.getLine() + 56);
		is << partenza + " " + arrivo << std::endl;
         
		//Se viene effettuato l'arrocco del re allora viene effettuata la mossa della torre corretta
		if (checkArrocco)
		{
			partenza = "";
			arrivo = "";
			arrocco_ = new Pezzo(scacchiera.getValue(Pair(rigaPartenzaArrocco, colonnaPartenzaArrocco))->getName(), coppiaArrocco, scacchiera.getValue(Pair(rigaPartenzaArrocco, colonnaPartenzaArrocco))->getNumMosse());
			scacchiera.setValue(coppiaArrocco, arrocco_);
			scacchiera.setValue(Pair(rigaPartenzaArrocco, colonnaPartenzaArrocco), nullptr);
			arrocco_->setNumMosse(arrocco_->getNumMosse() +  1);
			partenza.push_back(colonnaPartenzaArrocco + 65);
			partenza.push_back(-1 * rigaPartenzaArrocco + 56);
			arrivo.push_back(coppiaArrocco.getColumn() + 65);
			arrivo.push_back(-1 * coppiaArrocco.getLine() + 56);
		}
   }
   
   //Aggiorno i pedoni in caso si sia spostato nella casella di promozione e successivamente aggiorno le mosse dei pezzi
   scacchiera.pedestrian_becomes_queen(getTransform());
   ricercaMosse(scacchiera);
}
int Computer::getMax()
{
   return max;
}
void Computer::setMax(int massimo)
{
   max = massimo;
}
