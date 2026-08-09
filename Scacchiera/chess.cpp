//Alessio Demo 2007956  
#include <iostream>
#include "chess.h"
#include <list>
#include "math.h"
using namespace std;

//costruttore
chessTable::chessTable()
{
    matrix[0][0] = new Pezzo('T', Pair(0,0),0);
    matrix[0][1] = new Pezzo('C', Pair(0,1),0);
    matrix[0][2] = new Pezzo('A', Pair(0,2),0);
    matrix[0][3] = new Pezzo('D', Pair(0,3),0);
    matrix[0][4] = new Pezzo('R', Pair(0,4),0);
    matrix[0][5] = new Pezzo('A', Pair(0,5),0);
    matrix[0][6] = new Pezzo('C', Pair(0,6),0);
    matrix[0][7] = new Pezzo('T', Pair(0,7),0);

    for(int i=0;i<8;i++)
        matrix[1][i] = new Pezzo('P',Pair(1,i),0);


    for (int i=2;i<6;i++)
        for(int j=0;j<8;j++)
            matrix[i][j] = nullptr/*new Pezzo(' ', Pair(i,j))*/;

    for(int i=0;i<8;i++)
        matrix[6][i] = new Pezzo('p',Pair(6,i),0);

    matrix[7][0] = new Pezzo('t', Pair(7,0),0);
    matrix[7][1] = new Pezzo('c', Pair(7,1),0);
    matrix[7][2] = new Pezzo('a', Pair(7,2),0);
    matrix[7][3] = new Pezzo('d', Pair(7,3),0);
    matrix[7][4] = new Pezzo('r', Pair(7,4),0);
    matrix[7][5] = new Pezzo('a', Pair(7,5),0);
    matrix[7][6] = new Pezzo('c', Pair(7,6),0);
    matrix[7][7] = new Pezzo('t', Pair(7,7),0);

   
    //inizializzazione mosse disponibili
    for (int i = 0; i < 8; i++)
      {
         for (int j = 0; j < 8; j++)
         {
            if(getValue((Pair(i, j))) != nullptr)
            {
               Pezzo* ricerca = getValue((Pair(i, j)));
               char nome = ricerca->getName();
               nome = std::toupper(nome);
               switch(nome)
               {
                  case 'T':
                     ricercaMosseTorre(ricerca);
                  break;
                  case 'A':
                     ricercaMosseAlfiere(ricerca);
                  break;
                  case 'C':
                     ricercaMosseCavallo(ricerca);
                  break;
                  case 'D':
                     ricercaMosseDonna(ricerca);
                  break;
                  case 'R':
                     ricercaMosseRe(ricerca);
                  break;
                  case 'P':
                     ricercaMossePedone(ricerca);
                  break;
               }
            }
         }
      }
      
}

//costruttore  e assegnamento di copia
chessTable::chessTable(const chessTable& arg)
{  
      for(int i=0;i<8;i++)
      {
         for(int j=0;j<8;j++)
            matrix[i][j]=arg.matrix[i][j];
      }
}
chessTable& chessTable::operator=(const chessTable& t)
{
      for(int i=0;i<8;i++)
      {
         for(int j=0;j<8;j++)
         {
            if(t.getValue(Pair(i,j)) != nullptr)
            {
               Pezzo* tmp=t.getValue(Pair(i,j));
               std::list<Pair> l ;
               for(std::list<Pair>::iterator it = tmp->getAvailable_actions().begin() ; it!= tmp->getAvailable_actions().end() ; ++it)
                  l.push_back(*it);

               setValue(Pair(i,j) , new Pezzo(tmp->getName(),tmp->getCurrent_position(),l,tmp->getNumMosse()));
            }
            else
               setValue(Pair(i,j),nullptr);

         }
            
      }
      return *this;

}
chessTable::chessTable(chessTable& arg)
{
   for(int i=0;i<8;i++)
      {
         for(int j=0;j<8;j++)
            matrix[i][j]=arg.matrix[i][j];
      }

   for(int i=0;i<8;i++)
        {
            for(int j=0;j<8;j++)
            {
               matrix[i][j] = nullptr;;
            }
        }
}
chessTable& chessTable::operator=( chessTable&& t)
{
   for(int i=0;i<8;i++)
        {
            for(int j=0;j<8;j++)
            {
               delete matrix[i][j];
            }
        }

   for(int i=0;i<8;i++)
      {
         for(int j=0;j<8;j++)
            matrix[i][j]=t.matrix[i][j];
      }

   for(int i=0;i<8;i++)
        {
            for(int j=0;j<8;j++)
            {
               t.matrix[i][j] = nullptr;
            }
        }

        return *this;
}

//metodi getter setter per restituire o settare un puntatore a pezzo nella scacchiera
Pezzo* chessTable::getValue(Pair pa) const 
{
    if(matrix[pa.getLine()][pa.getColumn()] == nullptr)
    	return nullptr;
    	
    else 
    return matrix[pa.getLine()][pa.getColumn()];
}
void chessTable::setValue(Pair pa, Pezzo* pe)
{
    int line=pa.getLine();
    int column=pa.getColumn();
    if(pe == nullptr)
     {
      	matrix[line][column] = nullptr;
      	return;
    }
     matrix[line][column] = pe;
    pe->setCurrent_position(pa); 
}

//metodo per comando speciale
vector<string> chessTable::special()
{
  string s;
  int temp;
  vector<string> vec;
  vec.push_back ("\nCHESSBOARD    \n");
  int tmp=8;
  for(int i=0;i<8;i++)
   {
      temp = 8-i;
     string s = to_string(temp) + " ";
      for(int j=0;j<8;j++)
      {
         if(getValue(Pair(i,j)) == nullptr)
            s = s + " ";
         else
         {
            s = s + getValue(Pair(i,j))->getName();
         }
      }
      tmp--;
      
      vec.push_back (s);
      s = "";
   }
   vec.push_back ("\n  ABCDEFGH");
  return vec;

}

//metodi che restituiscono una lista di punatatori a oggetti di tipo pezzo che abbiano almeno una mossa disponibile; questo sia per il giocatore nero che per il bianco
std::list<Pezzo*> chessTable::getListNero() const
{
   std::list<Pezzo*> lst;
   for(int i=0;i<8;i++)
        {
            for(int j=0;j<8;j++)
            {
               if(getValue(Pair(i,j)) != nullptr && (getValue(Pair(i, j))->getColor() == "Nero") && ((getValue(Pair(i, j)))->getAvailable_actions()).size() != 0)
                  lst.push_back(getValue(Pair(i,j)));
            }
        }
return lst;
}
std::list<Pezzo*> chessTable::getListBianco() const
{
   std::list<Pezzo*> lst;
   for(int i=0;i<8;i++)
        {
            for(int j=0;j<8;j++)
            {
               if(getValue(Pair(i,j)) != nullptr && (getValue(Pair(i, j))->getColor() == "Bianco" && ((getValue(Pair(i, j)))->getAvailable_actions()).size() != 0))
                  lst.push_back(getValue(Pair(i,j)));
            }
        }
return lst;
}

//metodo per la mutazione del pedone in qualsiasi altro pezzo quando raggiunge il lato opposto della scacchiera
void chessTable::pedestrian_becomes_queen (char c)
{
    char carattere=std::toupper(c);
      for (int j = 0; j < 8; j++)
      {
         if (getValue(Pair(7, j)) != nullptr  &&  (getValue(Pair(7, j)))->getName() == 'P')
         {
            switch (carattere)
            {
               case 'T':
                  matrix[7][j]->setName('T');
                  break;

               case 'C':
                  matrix[7][j]->setName('C');
                  break;

               case 'A':
                  matrix[7][j]->setName('A');
                  break;

               case 'D':
                  matrix[7][j]->setName('D');
                  break;

               case 'R':
                  matrix[7][j]->setName('R');
                  break;

               case 'P':
                  break;
            }
         }
      }
    
      for (int j = 0; j < 8; j++)
      {
         if (getValue(Pair(0, j)) != nullptr  &&  (getValue(Pair(0, j)))->getName() == 'p')
         {
            switch (carattere)
            {
               case 'T':
                  matrix[0][j]->setName('t');
                  break;

               case 'C':
                  matrix[0][j]->setName('c');
                  break;

               case 'A':
                  matrix[0][j]->setName('a');
                  break;

               case 'D':
                  matrix[0][j]->setName('d');
                  break;

               case 'R':
                  matrix[0][j]->setName('r');
                  break;

               case 'P':
                  break;
            }
         }
      }
}

//metodo che controlla che l'oggetto di classe Pair passato come parametro abbia i membri privati line e column nel giusto range per la scacchiera (0-7)
bool chessTable::check_range(Pair pa) const
{
   return ((pa.getColumn() >= 0 && pa.getColumn() <= 7) && (pa.getLine() >= 0 && pa.getLine() <= 7));
}
//metodo che controlla che sulla casella da cui parte il pezzo non sia nullptr oppure che non ci sia un pezzo della squadra opposta rispetto al giocatore che sta inserendo la mossa da effettuare
bool chessTable::check_start(string s, string color) const
{
   int colonna_partenza = std::toupper(s[0]) - 65;
   int riga_partenza = -1 * (s[1] - 56);
   if( getValue(Pair(riga_partenza,colonna_partenza))->getColor() == color  &&  getValue(Pair(riga_partenza,colonna_partenza)) != nullptr)
      return true;

   return false;
}
//metodo che controlla che nella casella di arrivo non cia sia un pezzo della stessa squadra
bool chessTable::isSamePlayer(Pair pa1, Pair pa2) const
{
   if(getValue(pa1)==nullptr ||  getValue(pa2) == nullptr)
   	return false;
   	
   if ((*(getValue(pa1))).getColor() == (*(getValue(pa2))).getColor())
   	return true;
   	
   return false;
}
//metodo che controlla che nella casa passata come parametro attraverso un oggetto di tipo Pair non ci sia un puntatore nullo
bool chessTable::isNull(Pair pa1) const
{
   return getValue(pa1) == nullptr;
}

//metodi ricercaMosse per ciascun tipo di pedina
void chessTable::ricercaMosseTorre(Pezzo* to)
{
   ricercaScaccoTorre(to);
   virtualization(to);

   // posizioni dell'arrocco
   if(arrocco(to->getCurrent_position(),to->getColor()))
   {
      if(to->getColor()=="Nero")
      {
         Pair posizione_re = getPos_re(to->getColor());
         if(to->getCurrent_position().getColumn() - posizione_re.getColumn() == 3)
            to->setAvailable_actions(Pair(0,5));

         if(to->getCurrent_position().getColumn() - posizione_re.getColumn() == -4)
            to->setAvailable_actions(Pair(0,3));
      }

      if(to->getColor()=="Bianco")
      {
         Pair posizione_re = getPos_re(to->getColor());
         if(to->getCurrent_position().getColumn() - posizione_re.getColumn() == 3)
            to->setAvailable_actions(Pair(7,5));

         if(to->getCurrent_position().getColumn() - posizione_re.getColumn() == -4)
            to->setAvailable_actions(Pair(7,3));
      }
   }
        
}
void chessTable::ricercaMosseAlfiere(Pezzo* al)
{
   ricercaScaccoAlfiere(al);
   virtualization(al);
}
void chessTable::ricercaMosseCavallo(Pezzo* ca)
{
   ricercaScaccoCavallo(ca);
      virtualization(ca);
}
void chessTable::ricercaMosseDonna(Pezzo* da)
{
   ricercaScaccoTorre(da);
   ricercaScaccoAlfiere(da);
   virtualization(da);
}
void chessTable::ricercaMosseRe(Pezzo* re)
{

   //mosse arrocco
   if(re->getColor() == "Nero")
   {
      if(arrocco(Pair(0,7),"Nero"))
               re->setAvailable_actions(Pair(0,6));

      if(arrocco(Pair(0,0),"Nero"))
               re->setAvailable_actions(Pair(0,2));
   }

   if(re->getColor() == "Bianco")
   {
      if(arrocco(Pair(7,7),"Bianco"))
               re->setAvailable_actions(Pair(7,6));

      if(arrocco(Pair(7,0),"Bianco"))
               re->setAvailable_actions(Pair(7,2));
   } 
   
   ricercaScaccoRe(re);
   
   virtualization(re);


}
void chessTable::ricercaMossePedone(Pezzo *pe)
{ 

   // mosse en-passant 
   if(pe->getColor()== "Nero")
   {
      if(getValue(Pair(pe->getCurrent_position().getLine(),pe->getCurrent_position().getColumn()+1)) != nullptr  &&   getValue(Pair(pe->getCurrent_position().getLine(),pe->getCurrent_position().getColumn()+1))->getName() == 'p' &&   pe->getCurrent_position().getLine() == 4)
      {
         Pezzo* tmp = getValue(Pair(pe->getCurrent_position().getLine(),pe->getCurrent_position().getColumn()+1));
         if(tmp->getNumMosse() == 1  )
            pe->setAvailable_actions(Pair(pe->getCurrent_position().getLine(), pe->getCurrent_position().getColumn()+1));
      }

       if(getValue(Pair(pe->getCurrent_position().getLine(),pe->getCurrent_position().getColumn()-1)) != nullptr  &&   getValue(Pair(pe->getCurrent_position().getLine(),pe->getCurrent_position().getColumn()-1))->getName() == 'p'  &&  pe->getCurrent_position().getLine() == 4)
      {
         Pezzo* tmp1 = getValue(Pair(pe->getCurrent_position().getLine(),pe->getCurrent_position().getColumn()-1));
         if(tmp1->getNumMosse() == 1)
            pe->setAvailable_actions(Pair(pe->getCurrent_position().getLine(), pe->getCurrent_position().getColumn()-1));
      }
   }

   if(pe->getColor()== "Bianco")
   {
      if(getValue(Pair(pe->getCurrent_position().getLine(),pe->getCurrent_position().getColumn()+1)) != nullptr  &&   getValue(Pair(pe->getCurrent_position().getLine(),pe->getCurrent_position().getColumn()+1))->getName() == 'P'  &&  pe->getCurrent_position().getLine() == 3)
      {
         Pezzo* tmp = getValue(Pair(pe->getCurrent_position().getLine(),pe->getCurrent_position().getColumn()+1));
         if(tmp->getNumMosse() == 1)
            pe->setAvailable_actions(Pair(pe->getCurrent_position().getLine(), pe->getCurrent_position().getColumn()+1));
      }

       if(getValue(Pair(pe->getCurrent_position().getLine(),pe->getCurrent_position().getColumn()-1)) != nullptr  &&   getValue(Pair(pe->getCurrent_position().getLine(),pe->getCurrent_position().getColumn()-1))->getName() == 'P'  &&  pe->getCurrent_position().getLine() == 3)
      {
         Pezzo* tmp1 = getValue(Pair(pe->getCurrent_position().getLine(),pe->getCurrent_position().getColumn()-1));
         if(tmp1->getNumMosse() == 1)
            pe->setAvailable_actions(Pair(pe->getCurrent_position().getLine(), pe->getCurrent_position().getColumn()-1));
      }
   }
   ricercaScaccoPedone(pe);
   virtualization(pe);
}

//metodi che vengono richimati nei corrispettivi metodi "ricercaMosse..." e hanno il compito di inserire nell'oggetto di tipo Pezzo le case raggiungibili a seconda del tipo di pezzo (Cavallo, Pedone ecc...)
void chessTable::ricercaScaccoTorre(Pezzo* pezzo)
{
   int k = 1;
   Pair tmp = Pair(pezzo->getCurrent_position().getLine(), pezzo->getCurrent_position().getColumn() + k);
   while (check_range(tmp))
   {  
      if (!isSamePlayer(tmp, pezzo->getCurrent_position()))
      {
         pezzo->setAvailable_actions(tmp);
         if (!isNull(tmp))
            break;
         k++;
         tmp = Pair(pezzo->getCurrent_position().getLine(), pezzo->getCurrent_position().getColumn() + k);
      }
      else
         break; 
   }
   k = 1;
   tmp = Pair(pezzo->getCurrent_position().getLine(), pezzo->getCurrent_position().getColumn() - k);
   while (check_range(tmp))
   {  	
      
      if (!isSamePlayer(tmp, pezzo->getCurrent_position()))
      {
         pezzo->setAvailable_actions(tmp);
         if (!isNull(tmp))
            break;
         k++;
         tmp = Pair(pezzo->getCurrent_position().getLine(), pezzo->getCurrent_position().getColumn() - k);
      }
      else
         break; 
   }
   k = 1;
   tmp = Pair(pezzo->getCurrent_position().getLine() + k, pezzo->getCurrent_position().getColumn());
   while (check_range(tmp))
   {  
      
      if (!isSamePlayer(tmp, pezzo->getCurrent_position()))
      {
         pezzo->setAvailable_actions(tmp);
         if (!isNull(tmp))
            break;
         k++;
         tmp = Pair(pezzo->getCurrent_position().getLine() + k, pezzo->getCurrent_position().getColumn());
      }
      else
         break; 
   }
   k = 1;
   tmp = Pair(pezzo->getCurrent_position().getLine() - k, pezzo->getCurrent_position().getColumn());
   while (check_range(tmp))
   {  
      if (!isSamePlayer(tmp, pezzo->getCurrent_position()))
      {
         pezzo->setAvailable_actions(tmp);
         if (!isNull(tmp))
            break;
         k++;
         tmp = Pair(pezzo->getCurrent_position().getLine() - k, pezzo->getCurrent_position().getColumn());
      }
      else
         break; 
   }
}

void chessTable::ricercaScaccoAlfiere(Pezzo* pezzo)
{
   int k = 1;
   Pair tmp = Pair(pezzo->getCurrent_position().getLine() + k, pezzo->getCurrent_position().getColumn() + k);
   while (check_range(tmp))
   {  
      if (!isSamePlayer(tmp, pezzo->getCurrent_position()))
      {
         pezzo->setAvailable_actions(tmp);
         if (!isNull(tmp))
            break;
         k++;
         tmp = Pair(pezzo->getCurrent_position().getLine() + k, pezzo->getCurrent_position().getColumn() + k);
      }
      else
         break; 
   }
   k = 1;
   tmp = Pair(pezzo->getCurrent_position().getLine() + k, pezzo->getCurrent_position().getColumn() - k);
   while (check_range(tmp))
   {  
      if (!isSamePlayer(tmp, pezzo->getCurrent_position()))
      {
         pezzo->setAvailable_actions(tmp);
         if (!isNull(tmp))
            break;
         k++;
         tmp = Pair(pezzo->getCurrent_position().getLine() + k, pezzo->getCurrent_position().getColumn() - k);
      }
      else
         break; 
   }
   k = 1;
   tmp = Pair(pezzo->getCurrent_position().getLine() - k, pezzo->getCurrent_position().getColumn() + k);
   while (check_range(tmp))
   {  
      if (!isSamePlayer(tmp, pezzo->getCurrent_position()))
      {
         pezzo->setAvailable_actions(tmp);
         if (!isNull(tmp))
            break;
         k++;
         tmp = Pair(pezzo->getCurrent_position().getLine() - k, pezzo->getCurrent_position().getColumn() + k);
      }
      else
         break; 
   }
   k = 1;
   tmp = Pair(pezzo->getCurrent_position().getLine() - k, pezzo->getCurrent_position().getColumn() - k);
   while (check_range(tmp))
   {  
      if (!isSamePlayer(tmp, pezzo->getCurrent_position()))
      {
         pezzo->setAvailable_actions(tmp);
         if (!isNull(tmp))
            break;
         k++;
         tmp = Pair(pezzo->getCurrent_position().getLine() - k, pezzo->getCurrent_position().getColumn() - k);
      }
      else
         break; 
   }
}

void chessTable::ricercaScaccoCavallo(Pezzo* pezzo)
{
   int col = pezzo->getCurrent_position().getColumn();
   int rig = pezzo->getCurrent_position().getLine();
   if (check_range(Pair(rig - 2, col + 1)) && !isSamePlayer(Pair(rig - 2, col + 1), pezzo->getCurrent_position()))
      pezzo->setAvailable_actions(Pair(rig - 2, col + 1));
   if (check_range(Pair(rig - 2, col - 1)) && !isSamePlayer(Pair(rig - 2, col - 1), pezzo->getCurrent_position()))
      pezzo->setAvailable_actions(Pair(rig - 2, col - 1));
   if (check_range(Pair(rig + 2, col - 1)) && !isSamePlayer(Pair(rig + 2, col - 1), pezzo->getCurrent_position()))
      pezzo->setAvailable_actions(Pair(rig + 2, col - 1));
   if (check_range(Pair(rig + 2, col + 1)) && !isSamePlayer(Pair(rig + 2, col + 1), pezzo->getCurrent_position()))
      pezzo->setAvailable_actions(Pair(rig + 2, col + 1));
   if (check_range(Pair(rig + 1, col + 2)) && !isSamePlayer(Pair(rig + 1, col + 2), pezzo->getCurrent_position()))
      pezzo->setAvailable_actions(Pair(rig + 1, col + 2));
   if (check_range(Pair(rig + 1, col - 2)) && !isSamePlayer(Pair(rig + 1, col - 2), pezzo->getCurrent_position()))
      pezzo->setAvailable_actions(Pair(rig + 1, col - 2));
   if (check_range(Pair(rig - 1, col - 2)) && !isSamePlayer(Pair(rig - 1, col - 2), pezzo->getCurrent_position()))
      pezzo->setAvailable_actions(Pair(rig - 1, col - 2));
   if (check_range(Pair(rig - 1, col + 2)) && !isSamePlayer(Pair(rig - 1, col + 2), pezzo->getCurrent_position()))
      pezzo->setAvailable_actions(Pair(rig - 1, col + 2));
}

void chessTable::ricercaScaccoDonna(Pezzo* pezzo)
{
   //Torre
   int k = 1;
   Pair tmp = Pair(pezzo->getCurrent_position().getLine(), pezzo->getCurrent_position().getColumn() + k);
   while (check_range(tmp))
   {  
      if (!isSamePlayer(tmp, pezzo->getCurrent_position()))
      {
         pezzo->setAvailable_actions(tmp);
         if (!isNull(tmp))
            break;
         k++;
         tmp = Pair(pezzo->getCurrent_position().getLine(), pezzo->getCurrent_position().getColumn() + k);
      }
      else
         break; 
   }
   k = 1;
   tmp = Pair(pezzo->getCurrent_position().getLine(), pezzo->getCurrent_position().getColumn() - k);
   while (check_range(tmp))
   {  
      if (!isSamePlayer(tmp, pezzo->getCurrent_position()))
      {
         pezzo->setAvailable_actions(tmp);
         if (!isNull(tmp))
            break;
         k++;
         tmp = Pair(pezzo->getCurrent_position().getLine(), pezzo->getCurrent_position().getColumn() - k);
      }
      else
         break; 
   }
   k = 1;
   tmp = Pair(pezzo->getCurrent_position().getLine() + k, pezzo->getCurrent_position().getColumn());
   while (check_range(tmp))
   {  
      if (!isSamePlayer(tmp, pezzo->getCurrent_position()))
      {
         pezzo->setAvailable_actions(tmp);
         if (!isNull(tmp))
            break;
         k++;
         tmp = Pair(pezzo->getCurrent_position().getLine() + k, pezzo->getCurrent_position().getColumn());
      }
      else
         break; 
   }
   k = 1;
   tmp = Pair(pezzo->getCurrent_position().getLine() - k, pezzo->getCurrent_position().getColumn());
   while (check_range(tmp))
   {  
      if (!isSamePlayer(tmp, pezzo->getCurrent_position()))
      {
         pezzo->setAvailable_actions(tmp);
         if (!isNull(tmp))
            break;
         k++;
         tmp = Pair(pezzo->getCurrent_position().getLine() - k, pezzo->getCurrent_position().getColumn());
      }
      else
         break; 
   }
   //Alfiere
   k = 1;
   tmp = Pair(pezzo->getCurrent_position().getLine() + k, pezzo->getCurrent_position().getColumn() + k);
   while (check_range(tmp))
   {  
      if (!isSamePlayer(tmp, pezzo->getCurrent_position()))
      {
         pezzo->setAvailable_actions(tmp);
         if (!isNull(tmp))
            break;
         k++;
         tmp = Pair(pezzo->getCurrent_position().getLine() + k, pezzo->getCurrent_position().getColumn() + k);
      }
      else
         break; 
   }
   k = 1;
   tmp = Pair(pezzo->getCurrent_position().getLine() + k, pezzo->getCurrent_position().getColumn() - k);
   while (check_range(tmp))
   {  
      if (!isSamePlayer(tmp, pezzo->getCurrent_position()))
      {
         pezzo->setAvailable_actions(tmp);
         if (!isNull(tmp))
            break;
         k++;
         tmp = Pair(pezzo->getCurrent_position().getLine() + k, pezzo->getCurrent_position().getColumn() - k);
      }
      else
         break; 
   }
   k = 1;
   tmp = Pair(pezzo->getCurrent_position().getLine() - k, pezzo->getCurrent_position().getColumn() + k);
   while (check_range(tmp))
   {  
      if (!isSamePlayer(tmp, pezzo->getCurrent_position()))
      {
         pezzo->setAvailable_actions(tmp);
         if (!isNull(tmp))
            break;
         k++;
         tmp = Pair(pezzo->getCurrent_position().getLine() - k, pezzo->getCurrent_position().getColumn() + k);
      }
      else
         break; 
   }
   k = 1;
   tmp = Pair(pezzo->getCurrent_position().getLine() - k, pezzo->getCurrent_position().getColumn() - k);
   while (check_range(tmp))
   {  
      if (!isSamePlayer(tmp, pezzo->getCurrent_position()))
      {
         pezzo->setAvailable_actions(tmp);
         if (!isNull(tmp))
            break;
         k++;
         tmp = Pair(pezzo->getCurrent_position().getLine() - k, pezzo->getCurrent_position().getColumn() - k);
      }
      else
         break; 
   }
}

void chessTable::ricercaScaccoRe(Pezzo* pezzo)
{
   int col;
   int rig;
   col = pezzo->getCurrent_position().getColumn();
   rig = pezzo->getCurrent_position().getLine();
   if (check_range(Pair(rig + 1, col + 1))   &&   !isSamePlayer(Pair(rig + 1, col + 1), pezzo->getCurrent_position())  )
      pezzo->setAvailable_actions(Pair(rig + 1, col + 1));
   if (check_range(Pair(rig + 1, col - 1)) && !isSamePlayer(Pair(rig + 1, col - 1), pezzo->getCurrent_position())  )
      pezzo->setAvailable_actions(Pair(rig + 1, col - 1));
   if (check_range(Pair(rig - 1, col + 1)) && !isSamePlayer(Pair(rig - 1, col + 1), pezzo->getCurrent_position())   )
      pezzo->setAvailable_actions(Pair(rig - 1, col + 1));
   if (check_range(Pair(rig - 1, col - 1)) && !isSamePlayer(Pair(rig - 1, col - 1), pezzo->getCurrent_position())   )
      pezzo->setAvailable_actions(Pair(rig - 1, col - 1));
   if (check_range(Pair(rig, col + 1)) && !isSamePlayer(Pair(rig, col + 1), pezzo->getCurrent_position())    )
      pezzo->setAvailable_actions(Pair(rig, col + 1));
   if (check_range(Pair(rig, col - 1)) && !isSamePlayer(Pair(rig, col - 1), pezzo->getCurrent_position())   )
      pezzo->setAvailable_actions(Pair(rig, col - 1));
   if (check_range(Pair(rig + 1, col)) && !isSamePlayer(Pair(rig + 1, col), pezzo->getCurrent_position())   )
      pezzo->setAvailable_actions(Pair(rig + 1, col));
   if (check_range(Pair(rig - 1, col)) && !isSamePlayer(Pair(rig - 1, col), pezzo->getCurrent_position())    )
      pezzo->setAvailable_actions(Pair(rig - 1, col));
}

void chessTable::ricercaScaccoPedone(Pezzo* pezzo)
{
   if (pezzo->getColor() == "Nero")
      {
         if (pezzo->getNumMosse() == 0 && 
            ((getValue(Pair(pezzo->getCurrent_position().getLine() + 2, pezzo->getCurrent_position().getColumn()))) == nullptr
            && ((getValue(Pair(pezzo->getCurrent_position().getLine() + 1, pezzo->getCurrent_position().getColumn()))) == nullptr)))
               pezzo->setAvailable_actions(Pair(pezzo->getCurrent_position().getLine() + 2, pezzo->getCurrent_position().getColumn()));
         if (check_range(Pair(pezzo->getCurrent_position().getLine() + 1, pezzo->getCurrent_position().getColumn())) && ((getValue(Pair(pezzo->getCurrent_position().getLine() + 1, pezzo->getCurrent_position().getColumn()))))/*.getName()*/ == nullptr)
            pezzo->setAvailable_actions(Pair(pezzo->getCurrent_position().getLine() + 1, pezzo->getCurrent_position().getColumn()));
         if (check_range(Pair(pezzo->getCurrent_position().getLine() + 1, pezzo->getCurrent_position().getColumn() + 1)) && !isSamePlayer(Pair(pezzo->getCurrent_position().getLine() + 1, pezzo->getCurrent_position().getColumn() + 1), pezzo->getCurrent_position()) && ((getValue(Pair(pezzo->getCurrent_position().getLine() + 1, pezzo->getCurrent_position().getColumn() + 1))))/*.getName()*/ != nullptr)
            pezzo->setAvailable_actions(Pair(pezzo->getCurrent_position().getLine() + 1, pezzo->getCurrent_position().getColumn() + 1));
         if (check_range(Pair(pezzo->getCurrent_position().getLine() + 1, pezzo->getCurrent_position().getColumn() - 1)) && !isSamePlayer(Pair(pezzo->getCurrent_position().getLine() + 1, pezzo->getCurrent_position().getColumn() - 1), pezzo->getCurrent_position()) && ((getValue(Pair(pezzo->getCurrent_position().getLine() + 1, pezzo->getCurrent_position().getColumn() - 1))))/*.getName()*/ != nullptr)
            pezzo->setAvailable_actions(Pair(pezzo->getCurrent_position().getLine() + 1, pezzo->getCurrent_position().getColumn() - 1));
      }
      if(pezzo->getColor()=="Bianco")
      {
         if (pezzo->getNumMosse() == 0 && 
            ((getValue(Pair(pezzo->getCurrent_position().getLine() - 2, pezzo->getCurrent_position().getColumn()))) == nullptr
            && ((getValue(Pair(pezzo->getCurrent_position().getLine() - 1, pezzo->getCurrent_position().getColumn()))) == nullptr)))
               pezzo->setAvailable_actions(Pair(pezzo->getCurrent_position().getLine() - 2, pezzo->getCurrent_position().getColumn()));
         if (check_range(Pair(pezzo->getCurrent_position().getLine() - 1, pezzo->getCurrent_position().getColumn())) && (getValue(Pair(pezzo->getCurrent_position().getLine() - 1, pezzo->getCurrent_position().getColumn())))/*.getName()*/ == nullptr)
            pezzo->setAvailable_actions(Pair(pezzo->getCurrent_position().getLine() - 1, pezzo->getCurrent_position().getColumn()));
         if (check_range(Pair(pezzo->getCurrent_position().getLine() - 1, pezzo->getCurrent_position().getColumn() + 1)) && !isSamePlayer(Pair(pezzo->getCurrent_position().getLine() - 1, pezzo->getCurrent_position().getColumn() + 1), pezzo->getCurrent_position()) && ((getValue(Pair(pezzo->getCurrent_position().getLine() - 1, pezzo->getCurrent_position().getColumn() + 1))))/*.getName()*/ != nullptr)
            pezzo->setAvailable_actions(Pair(pezzo->getCurrent_position().getLine() - 1, pezzo->getCurrent_position().getColumn() + 1));
         if (check_range(Pair(pezzo->getCurrent_position().getLine() - 1, pezzo->getCurrent_position().getColumn() - 1)) && !isSamePlayer(Pair(pezzo->getCurrent_position().getLine() - 1, pezzo->getCurrent_position().getColumn() - 1), pezzo->getCurrent_position()) && ((getValue(Pair(pezzo->getCurrent_position().getLine() - 1, pezzo->getCurrent_position().getColumn() - 1))))/*.getName()*/ != nullptr)
            pezzo->setAvailable_actions(Pair(pezzo->getCurrent_position().getLine() - 1, pezzo->getCurrent_position().getColumn() - 1));
      }
}

//metodo che compie una "virtualizzazione" del pezzo passato come parametro, facendolo momentaneamente spostare in un determinata casella per poi controllare la condizione di scacco del proprio re e se spostando il pezzo il re finisce sotto scacco allora la mossa non può essere fatta
// ma se invece spostando il pezzo sia annulla la condizione di scacco per persisteva prima dello spostamento , allora si rende la mossa obbligatoria inserendola nella lista help (parametro di chessTable), questo metodo viene richiamato in tutti i metodi
//"ricercaMosse..."" dopo aver chiamato in ciascuno di essi il corrispettivo "ricercaScacco..."
void chessTable::virtualization(Pezzo* pezzo)
{
   std::list<Pair> tmp;
   std::list<Pair> paia;
            for(std::list<Pair>::iterator i=pezzo->getAvailable_actions().begin() ; i!=pezzo->getAvailable_actions().end() ; ++i)
               paia.push_back(*i);

     int rigaPartenza= pezzo->getCurrent_position().getLine();
      int colonnaPartenza= pezzo->getCurrent_position().getColumn();

   for(std::list<Pair>::iterator it = paia.begin() ; it != paia.end() ; ++it)
  {
      std::list<std::list<Pair>> y;
      std::list<Pezzo*> support;
      std::list<Pair> x;

      if(pezzo->getColor()=="Nero")
         support=getListBianco();
      else
         support=getListNero();

      for(std::list<Pezzo*>::iterator i4=support.begin() ; i4!=support.end() ; ++i4)
      {
         for(std::list<Pair>::iterator i5=(*i4)->getAvailable_actions().begin() ; i5!=(*i4)->getAvailable_actions().end() ; ++i5)
            x.push_back(*i5);

         y.push_back(x);
         x.clear();
      }

      Pezzo* temporaneo = getValue(*it);
                  //Spostamento temporaneo
                  pezzo = new Pezzo(pezzo->getName(), *it, pezzo->getNumMosse());
                  setValue(*it, pezzo);
                  setValue(Pair(rigaPartenza, colonnaPartenza), nullptr);
                  //ricerca mosse temporanea
                  for (int i = 0; i < 8; i++)
                  {
                     for (int j = 0; j < 8; j++)
                     {
                        if(getValue((Pair(i, j))) != nullptr && !isSamePlayer(Pair(i, j), *it))
                        {
		                     Pezzo* pezzo = getValue((Pair(i, j)));
		                     pezzo->setAvailable_actions();
                           switch(std::toupper(pezzo->getName()))
                           {
		                        case 'T':
                                 ricercaScaccoTorre(pezzo);
		                        break;

		                        case 'A':
		                           ricercaScaccoAlfiere( pezzo);
		                        break;

		                        case 'C':
		                              ricercaScaccoCavallo( pezzo);
		                        break;

		                        case 'D':
                                    ricercaScaccoDonna(pezzo);
		                        break;
		                        case 'R':
                                    ricercaScaccoRe( pezzo);
		                        break;
		                        case 'P':
		                           ricercaScaccoPedone(pezzo);
		                        break;
		                     }
                        }
                     }
                  }
                  //controllo
                  if (!scacco(getPos_re(pezzo->getColor()), pezzo->getColor()))
                     tmp.push_back(*it);

                  //ripristino
                  pezzo = new Pezzo(pezzo->getName(), Pair(rigaPartenza, colonnaPartenza), pezzo->getNumMosse());
                  setValue(Pair(rigaPartenza, colonnaPartenza), pezzo);
                  setValue(*it, temporaneo);
                  for (int i = 0; i < 8; i++)
                  {
                     for (int j = 0; j < 8; j++)
                     {
                        if(getValue((Pair(i, j))) != nullptr && !isSamePlayer(Pair(i, j), Pair(rigaPartenza,colonnaPartenza)))
                        {
		                     Pezzo* pezzo = getValue((Pair(i, j)));
		                     pezzo->setAvailable_actions();  
                        }
                     }
                  }


      std::list<Pezzo*>::iterator i4 = support.begin();
      for(std::list<list<Pair>>::iterator i5=y.begin() ; i5!=y.end() ; ++i5)
      {
         for(std::list<Pair>::iterator i6=(*i5).begin() ; i6!=(*i5).end() ; ++i6)
            (*i4)->setAvailable_actions(*i6);

         ++i4;
      }
   }
   pezzo->setAvailable_actions();
   for(std::list<Pair>::iterator it1=tmp.begin() ; it1!=tmp.end()  ;  ++it1)
      pezzo->setAvailable_actions(*it1);
}

//metodo per rilevazione patta per 50 mosse consecutive senza aver mangiato dei pezzi o spostato un pedone
bool chessTable::patta(int checkPedone, int checkMangiato)
{
   if(checkPedone>=50  ||  checkMangiato>=50)
      return true;

   return false;
      
}
//metodo per rilevazione patta per indisponibilita' di pezzi con almeno una mossa disponibile ( con il re che non  e' sotto scacco)
bool chessTable::patta2()
{
   std::list<Pezzo*> bianco =getListBianco();
   std::list<Pezzo*> nero = getListNero();

   if((bianco.size()== 0 && !scacco(getPos_re("Bianco"),"Bianco"))  ||  (nero.size()==0  && !scacco(getPos_re("Nero"),"Nero")))
      return true;

   return false;
}
//metodo per rilevazione arrocco
bool chessTable::arrocco( Pair t, string color)
{
   Pair alarm= Pair(-1,-1);
   Pair posizione = getPos_re(color);
   Pezzo* torre = getValue(t);
   if(torre != nullptr && !(posizione==alarm))
   {
      Pezzo* re = getValue(posizione);
         if(torre->getColor() == color  &&  (torre->getName() == 't' ||  torre->getName() == 'T'))
         {
               if (re->getNumMosse() == 0 && torre->getNumMosse() == 0)
               {
                  int diff = (t.getColumn()) - (posizione.getColumn());
                  if( diff==3)
                  {
                        for(int i=1 ; i<diff; i++)
                        {
                           if((getValue(Pair(re->getCurrent_position().getLine() , re->getCurrent_position().getColumn()+i)) != nullptr)  ||  scacco(Pair(posizione.getLine() , posizione.getColumn()+i),re->getColor()))
                              return false;
                        }
                  
                  return true;
                  }

                  else if(diff== -4 )
                  {
                        for(int i=1 ; i<(abs(diff)); i++)
                        {
                           if((getValue(Pair(re->getCurrent_position().getLine() , re->getCurrent_position().getColumn()-i)) != nullptr)  ||  scacco(Pair(posizione.getLine() , posizione.getColumn()-i),re->getColor()))
                              return false;
                        }
                        
                  return true;
                  }
               }
               return false;
         }
         return false;
   }
   return false;
}
//metodo per rilevazione scacco
 bool chessTable::scacco( Pair pa_re, string colore)
 {
      Pair tmp = Pair(-1,-1);
      if(dangerous(pa_re,colore) == tmp)
         return false;
      
      return true;
 }
 //metodo che restituisce la posizione del re della squadra indicata come parametro nella istanza corrente
 Pair chessTable::getPos_re(string color) const
 {
    for(int i=0;i<8;i++)
        {
            for(int j=0;j<8;j++)
            {
               if(getValue(Pair(i,j))!= nullptr)
               {
                  if(color=="Nero")
                  {
                     if(getValue(Pair(i,j)) -> getName() == 'R')
                        return getValue(Pair(i,j))-> getCurrent_position();
                  }

                  if(color=="Bianco")
                  {
                     if(getValue(Pair(i,j)) -> getName() == 'r')
                        return getValue(Pair(i,j))-> getCurrent_position();
                  }
               }
            }
        }
        return Pair(-1,-1);
 }
//metodi getter and setter di help
list<Pezzo*>& chessTable::getHelp()
{
   return help;
}
//setHelp per cancellare la lista help
void chessTable::setHelp()
{
   help.clear();
}
void chessTable::setHelp(Pezzo* pe)
{
   help.push_back(pe);
}
//metodo per rilevazione scacco matto --> esegue una "virtualizzazione" del re spostandolo in ogni casa in cui puo' andaree vedendo se in ciascuna di queste e' sotto scacco o meno
//se in ciascuna di queste e' sotto scacco e la lista help e' vuota, allora e' sottoscacco matto, altrimenti no
 bool chessTable::scacco_matto(string color)
 {
    setHelp();
    Pair coppia = getPos_re(color);
    Pair confronto = Pair(-1,-1);
    if(coppia == confronto)
    {
      return true;
    }
    
    Pezzo* tmp ;
    
     std::list<Pezzo*> lista ;
     if(color=="Bianco")
      lista=getListBianco();
     else
      lista=getListNero();


    if(scacco(coppia,color))
    {
       Pair position = dangerous(coppia,color);
       if(getValue(coppia)->getAvailable_actions().size() != 0)
         setHelp(getValue(coppia));

      for(std::list<Pezzo*>::iterator it=lista.begin() ; it!=lista.end() ; ++it)
      {
         Pezzo* ptr = (*it);
         if (std::toupper(ptr->getName()) != 'R')
         {
            tmp = new Pezzo(ptr->getName(),ptr->getCurrent_position(),ptr->getNumMosse());
            int rigaPartenza = ptr->getCurrent_position().getLine();
            int colonnaPartenza = ptr->getCurrent_position().getColumn();
            std::list<Pair> paia;
            for(std::list<Pair>::iterator i=ptr->getAvailable_actions().begin() ; i!=ptr->getAvailable_actions().end() ; ++i)
               paia.push_back(*i);
            for(std::list<Pair>::iterator i=paia.begin() ; i!=paia.end() ; ++i)
            {
               //controllo che possa arrivare al pezzo che tiene sotto scacco il re
               if((*i) == position) //position indica la posizione del pezzo che tiene sotto scacco il re
               {
                  tmp->setAvailable_actions(position);
               }
               else
               {
                  Pezzo* temporaneo = getValue(*i);
                  //Spostamento temporaneo
                  ptr = new Pezzo(ptr->getName(), *i, ptr->getNumMosse());
                  setValue(*i, ptr);
                  setValue(Pair(rigaPartenza, colonnaPartenza), nullptr);
                  //ricerca mosse temporanea
                  for (int i = 0; i < 8; i++)
                  {
                     for (int j = 0; j < 8; j++)
                     {
                        if(getValue((Pair(i, j))) != nullptr && !isSamePlayer(Pair(i, j), coppia))
                        {
		                     Pezzo* pezzo = getValue((Pair(i, j)));
		                     pezzo->setAvailable_actions();
                           switch(std::toupper(pezzo->getName()))
                           {
		                        case 'T':
		                           ricercaMosseTorre(pezzo);
		                        break;
		                        case 'A':
		                           ricercaMosseAlfiere(pezzo);
		                        break;
		                        case 'C':
		                           ricercaMosseCavallo(pezzo);
		                        break;
		                        case 'D':
		                           ricercaMosseDonna(pezzo);
		                        break;
		                        case 'R':
		                           ricercaMosseRe(pezzo);
		                        break;
		                        case 'P':
		                           ricercaMossePedone(pezzo);
		                        break;
		                     }
                        }
                     }
                  }
                  //controllo
                  if (!scacco(coppia, color))
                     tmp->setAvailable_actions(*i);
                  //ripristino
                  ptr = new Pezzo(ptr->getName(), Pair(rigaPartenza, colonnaPartenza), ptr->getNumMosse());
                  setValue(Pair(rigaPartenza, colonnaPartenza), ptr);
                  setValue(*i, temporaneo);
                  for (int i = 0; i < 8; i++)
                  {
                     for (int j = 0; j < 8; j++)
                     {
                        if(getValue((Pair(i, j))) != nullptr && !isSamePlayer(Pair(i, j), coppia))
                        {
		                     Pezzo* pezzo = getValue((Pair(i, j)));
		                     pezzo->setAvailable_actions();
                           switch(std::toupper(pezzo->getName()))
                           {
		                        case 'T':
		                           ricercaMosseTorre(pezzo);
		                        break;
		                        case 'A':
		                           ricercaMosseAlfiere(pezzo);
		                        break;
		                        case 'C':
		                           ricercaMosseCavallo(pezzo);
		                        break;
		                        case 'D':
		                           ricercaMosseDonna(pezzo);
		                        break;
		                        case 'R':
		                           ricercaMosseRe(pezzo);
		                        break;
		                        case 'P':
		                           ricercaMossePedone(pezzo);
		                        break;
		                     }
                        }
                     }
                  }
               }
            }
            if(tmp->getAvailable_actions().size() != 0)
               setHelp(tmp);
          }
      }

      if(help.size() == 0)
         return true;
    }
    
     return false;
 }
//metodo che ritorna la posizione (se esiste) del pezzo avversario che tiene sotto scacco il re (il colore passato come parametro corrisponde al colore del re)
 Pair chessTable::dangerous( Pair pa_re, string colore)
 {
        for(int i=0;i<8;i++)
        {
            for(int j=0;j<8;j++)
            {
               if(getValue(Pair(i,j)) != nullptr )
               {
                  if(getValue(Pair(i,j))->getColor() != colore)
                  {
                     std::list<Pair> tmp = getValue(Pair(i,j))->getAvailable_actions(); 
                     for(std::list<Pair>::iterator it = tmp.begin() ; it!= tmp.end() ; ++it)
                     {
                        if((*it)==pa_re)
                              return Pair(i,j);
                     }
                  }
               }
            }
        }

      return Pair(-1,-1);
 }

//metodo per verificare che il pezzo presente nella posizione di partenza abbia la casella di arrivo nella sua lista di case raggiungibili
bool chessTable::checkMove(string partenza,string arrivo)
{
   int colonna_partenza = std::toupper(partenza[0]) - 65;
   int colonna_arrivo = std::toupper(arrivo[0]) - 65;
   int riga_partenza = -1 * (partenza[1] - 56);
   int riga_arrivo = -1 * (arrivo[1] - 56);
   
   if(getValue(Pair(riga_partenza,colonna_partenza)) != nullptr)
   {
         Pezzo* pe = getValue(Pair(riga_partenza,colonna_partenza));
      
      for(std::list<Pair>::iterator it = (pe->getAvailable_actions()).begin() ; it != (pe->getAvailable_actions()).end() ; ++it)
      {
         Pair tmp=(*it);
         Pair tmp1=Pair(riga_arrivo, colonna_arrivo);
         if(tmp == tmp1)
            return true;
      }

      for(std::list<Pezzo*>::iterator it1=help.begin() ; it1!=help.end() ; ++it1)
      {
         Pezzo* tmp=*it1;
         Pair tmp2=tmp->getCurrent_position();
         Pair tmp3 = Pair(riga_partenza,colonna_partenza);
         if(tmp2 == tmp3)
            {
               for(std::list<Pair>::iterator it2= tmp->getAvailable_actions().begin() ; it2 != tmp->getAvailable_actions().end() ; ++it2)
               {
                  Pair coppia = *it2;
                  Pair tmp1=Pair(riga_arrivo, colonna_arrivo);
                  if(coppia == tmp1)
                     return true;


               }
            }
      }
   }
   		
   return false;
}
//distruttore
chessTable::~chessTable()
{

   for(int i=0;i<8;i++)
      for(int j=0;j<8;j++)
         delete matrix[i][j];
   
}
