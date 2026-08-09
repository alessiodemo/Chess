// Matteo Marcellin  2007946
#include <iostream>
#include "../Scacchiera/chess.h"
#include "../Giocatori/Computer.h"
#include "../Giocatori/GiocatoreUmano.h"
using namespace std;
bool isMatchPC()
{
    while(true)
    {
      string in;
      cout<<"Scegli il tipo di partita: "<<endl;
      cout<<"pc (minuscolo) per una partita player vs computer"<<endl;
      cout<<"cc (minuscolo) per una partita computer vs computer"<<endl;
      cin >> in;
      if (in == "pc")
      {
          return true;
      }
      else if (in == "cc")
      {
          return false;
      }
    }
}

bool isMoveCorrect(string s1)
{
	string str = s1;
        if (!str.length()==2)
			return false;
		//to upper case
            if (str[0]>='a'&&str[0]<='h')
            {
                str[0]=str[0]-32;
            }
        
		if ((str[0]>=65 && str[0]<=72) && (str[1]>=49 && str[1]<=56))
			return true;
	
	return false;
}
