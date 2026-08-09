//Michele Veneziani 2007955
#include "GiocatoreUmano.h"
GiocatoreUmano::GiocatoreUmano(std::string colore, char c)
{
   setColor(colore);
   setTransform(c);
}
GiocatoreUmano::GiocatoreUmano()
{
   srand(time(NULL));
   int random = rand() % 2;
   if (random == 0)
      setColor("Bianco");
   else
      setColor("Nero");
   setTransform('D');
}
int GiocatoreUmano::checkPedestrian = 0;
int GiocatoreUmano::checkAte = 0;
void GiocatoreUmano::move(chessTable& scacchiera, std::string partenza, std::string arrivo)
{
   //Converto le lettere e i numeri in base alla tabella ASCII in mododa usare facilmente i metodi disponibili della classe chessTable
   //e salvo il puntatore del pezzo che si trova nella casella indicata da partenza
   int colonnaPartenza = std::toupper(partenza[0]) - 65;
   int colonnaArrivo = std::toupper(arrivo[0]) - 65;
   int rigaPartenza = -1 * (partenza[1] - 56);
   int rigaArrivo = -1 * (arrivo[1] - 56);
   
   //Variabili utilizzate nell'arrocco
   Pezzo* arrocco_;
   int rigaPartenzaArrocco;
   int colonnaPartenzaArrocco;
   Pair coppiaArrocco;
   Pezzo* pezzo_casella_partenza = scacchiera.getValue(Pair(rigaPartenza, colonnaPartenza));
   bool checkArrocco = arroccoElements(pezzo_casella_partenza, colonnaPartenza, colonnaArrivo, rigaPartenzaArrocco, colonnaPartenzaArrocco, coppiaArrocco);

	//Inserisco il pezzo che si trova nella casella indicata da partenza nella casella indicata da arrivo, in caso sovrapponendolo al pezzo precedente,
   //rendo vuota la casella di partenza e incremento il numero di mosse effettuate dal pezzo di 1
   pezzo_casella_partenza = new Pezzo(pezzo_casella_partenza->getName(), Pair(rigaArrivo, colonnaArrivo), pezzo_casella_partenza->getNumMosse());
   scacchiera.setValue(Pair(rigaArrivo, colonnaArrivo), pezzo_casella_partenza);
   scacchiera.setValue(Pair(rigaPartenza, colonnaPartenza), nullptr);
   
	//Se viene effettuato l'arrocco del re allora viene effettuata la mossa della torre corretta
   if (checkArrocco)
   {
      arrocco_ = new Pezzo(scacchiera.getValue(Pair(rigaPartenzaArrocco, colonnaPartenzaArrocco))->getName(), coppiaArrocco, scacchiera.getValue(Pair(rigaPartenzaArrocco, colonnaPartenzaArrocco))->getNumMosse());
      scacchiera.setValue(coppiaArrocco, arrocco_);
      scacchiera.setValue(Pair(rigaPartenzaArrocco, colonnaPartenzaArrocco), nullptr);
   }
   scacchiera.pedestrian_becomes_queen(getTransform());
}
void GiocatoreUmano::move(chessTable& scacchiera, std::string partenza, std::string arrivo, std::ofstream& is)
{
   //Converto le lettere e i numeri in base alla tabella ASCII in mododa usare facilmente i metodi disponibili della classe chessTable
   //e salvo il puntatore del pezzo che si trova nella casella indicata da partenza
   int colonnaPartenza = std::toupper(partenza[0]) - 65;
   int colonnaArrivo = std::toupper(arrivo[0]) - 65;
   int rigaPartenza = -1 * (partenza[1] - 56);
   int rigaArrivo = -1 * (arrivo[1] - 56);
   Pezzo* pezzo_casella_partenza = scacchiera.getValue(Pair(rigaPartenza, colonnaPartenza));

   //Variabili per scrivere nel file
   std::string s1 = "";
   std::string s2 = "";
   
   //Variabili utilizzate nell'arrocco
   Pezzo* arrocco_;
   int rigaPartenzaArrocco;
   int colonnaPartenzaArrocco;
   Pair coppiaArrocco;
   std::string partenzaArrocco = "";
   std::string arrivoArrocco = "";
   bool checkArrocco = arroccoElements(pezzo_casella_partenza, colonnaPartenza, colonnaArrivo, rigaPartenzaArrocco, colonnaPartenzaArrocco, coppiaArrocco);
   checkPatta(scacchiera, Pair(rigaPartenza, colonnaPartenza), Pair(rigaArrivo, colonnaArrivo));
   
   //Inserisco il pezzo che si trova nella casella indicata da partenza nella casella indicata da arrivo, in caso sovrapponendolo al pezzo precedente,
   //rendo vuota la casella di partenza e incremento il numero di mosse effettuate dal pezzo di 1
   pezzo_casella_partenza = new Pezzo(pezzo_casella_partenza->getName(), Pair(rigaArrivo, colonnaArrivo), pezzo_casella_partenza->getNumMosse());
   scacchiera.setValue(Pair(rigaArrivo, colonnaArrivo), pezzo_casella_partenza);
   scacchiera.setValue(Pair(rigaPartenza, colonnaPartenza), nullptr);
   pezzo_casella_partenza->setNumMosse(pezzo_casella_partenza->getNumMosse() +  1);
   
   //Inserisco la mossa nel file
   s1.push_back(colonnaPartenza + 65);
   s1.push_back(-1 * rigaPartenza + 56);
   s2.push_back(colonnaArrivo + 65);
   s2.push_back(-1 * rigaArrivo + 56);
   is << s1 + " " + s2 << std::endl;
   
   //Se viene effettuato l'arrocco del re allora viene effettuata la mossa della torre corretta
   if (checkArrocco)
   {
      arrocco_ = new Pezzo(scacchiera.getValue(Pair(rigaPartenzaArrocco, colonnaPartenzaArrocco))->getName(), coppiaArrocco, scacchiera.getValue(Pair(rigaPartenzaArrocco, colonnaPartenzaArrocco))->getNumMosse());
      scacchiera.setValue(coppiaArrocco, arrocco_);
      scacchiera.setValue(Pair(rigaPartenzaArrocco, colonnaPartenzaArrocco), nullptr);
      arrocco_->setNumMosse(arrocco_->getNumMosse() +  1);
      partenzaArrocco.push_back(colonnaPartenzaArrocco + 65);
      partenzaArrocco.push_back(-1 * rigaPartenzaArrocco + 56);
      arrivoArrocco.push_back(coppiaArrocco.getColumn() + 65);
      arrivoArrocco.push_back(-1 * coppiaArrocco.getLine() + 56);
      //is <<partenzaArrocco + " " + arrivoArrocco << std::endl;
   }
	
	//Aggiorno i pedoni in caso si sia spostato nella casella di promozione e successivamente aggiorno le mosse dei pezzi
   scacchiera.pedestrian_becomes_queen(getTransform());
   ricercaMosse(scacchiera);
}
std::string GiocatoreUmano::getColor()
{
   return color;
}
void GiocatoreUmano::setColor(std::string colore)
{
   color = colore;
}
char GiocatoreUmano::getTransform()
{
   return transform;
}
void GiocatoreUmano::setTransform(char c)
{
   transform = c;
}
int GiocatoreUmano::getCheckPedestrian()
{
   return checkPedestrian;
}
void GiocatoreUmano::setCheckPedestrian(int i)
{
   checkPedestrian = i;
}
int GiocatoreUmano::getCheckAte()
{
	return checkAte;
}
void GiocatoreUmano::setCheckAte(int i)
{
   checkAte = i;
}
void GiocatoreUmano::ricercaMosse(chessTable& scacchiera)
{
   for (int i = 0; i < 8; i++)
   {
      for (int j = 0; j < 8; j++)
      {
         if(scacchiera.getValue((Pair(i, j))) != nullptr)
         {
		      Pezzo* pezzo = scacchiera.getValue((Pair(i, j)));
		      pezzo->setAvailable_actions();
            switch(std::toupper(pezzo->getName()))
            {
		         case 'T':
		            scacchiera.ricercaMosseTorre(pezzo);
		         break;
		         case 'A':
		            scacchiera.ricercaMosseAlfiere(pezzo);
		         break;
		         case 'C':
		            scacchiera.ricercaMosseCavallo(pezzo);
		         break;
		         case 'D':
		            scacchiera.ricercaMosseDonna(pezzo);
		         break;
		         case 'R':
		            scacchiera.ricercaMosseRe(pezzo);
		         break;
		         case 'P':
		            scacchiera.ricercaMossePedone(pezzo);
		         break;
		      }
         }
      }
   }
}
bool GiocatoreUmano::arroccoElements(Pezzo* pe, int colonnaPartenza, int colonnaArrivo, int& rigaPartenzaArrocco, int& colonnaPartenzaArrocco, Pair& coppiaArrocco)
{
	//Caso arrocco re nero
   if (pe->getName() == 'R' && (colonnaPartenza - colonnaArrivo == 2 || colonnaPartenza - colonnaArrivo == -2))
   {
   	//Caso arrocco lungo
      if (colonnaPartenza - colonnaArrivo == 2)
      {
         rigaPartenzaArrocco = 0;
         colonnaPartenzaArrocco = 0;
         coppiaArrocco = Pair(0, 3);
         return true;
      }
      //Caso arrocco corto
      else
      {
         rigaPartenzaArrocco = 0;
         colonnaPartenzaArrocco = 7;
         coppiaArrocco = Pair(0, 5);
         return true;
      }
   }
   //Caso arrocco re bianco
   else if (pe->getName() == 'r' && (colonnaPartenza - colonnaArrivo == 2 || colonnaPartenza - colonnaArrivo == -2))
   {
   	//Caso arrocco lungo
      if (colonnaPartenza - colonnaArrivo == 2)
      {
         rigaPartenzaArrocco = 7;
         colonnaPartenzaArrocco = 0;
         coppiaArrocco = Pair(7, 3);
         return true;
      }
      //Caso arrocco corto
      else
      {
         rigaPartenzaArrocco = 7;
         colonnaPartenzaArrocco = 7;
         coppiaArrocco = Pair(7, 5);
         return true;
      }
   }
   //Nessun arrocco
   return false;
}
void GiocatoreUmano::checkPatta(chessTable& scacchiera, Pair partenza, Pair arrivo)
{
	//Se non viene mosso nessun pedone incremento la variabile checkPedestrian, altrimenti la reimposto a 0
   if (scacchiera.getValue(partenza)->getName() == 'P' || scacchiera.getValue(partenza)->getName() == 'p')
      setCheckPedestrian(0);
   else 
      checkPedestrian++;

	//Se non mangia nessun pezzo allora nella casella di arrivo non c'è nessun pezzo
   if (scacchiera.getValue(arrivo) == nullptr)
      checkAte++;
   else
      setCheckAte(0);
}
