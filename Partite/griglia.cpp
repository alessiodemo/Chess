// Matteo Marcellin  2007946
#include <iostream>
#include "Metodi.h"
#include <string>
#include <vector>

using namespace std;

int main(int argc, char **arg)
{
		bool patta = false; 
		bool isPC;
		bool checkMate = false;
		int maxMoves = 200;
		string s = "";
		chessTable scacchiera = chessTable();
		vector<string> out;
	
    

		ofstream fs ("LogPC.txt");

		//write menu and get match type
		string tmp = arg[1];
		if (tmp == "pc")
			isPC = true;

		else if(tmp == "cc")
			isPC = false;

		else 
		{
			cout <<"Argomento errato"<<endl;
			isPC = isMatchPC();
		}

		if (!isPC)
		{
			Computer computerBianco = Computer("Bianco",'D',maxMoves);
			Computer computerNero = Computer("Nero",'D',maxMoves); 
			for (int i=0; i < maxMoves; i++) 
			{
				computerBianco.move(scacchiera, fs);
				if(scacchiera.scacco_matto("Nero"))
				{
					fs <<"HA VINTO IL Bianco"<<endl;
					cout<<"HA VINTO IL Bianco"<<endl;
					break;
				}	
				else if(scacchiera.patta2())
				{
					fs <<"PATTA PER STALLO"<<endl;
					cout<<"PATTA PER STALLO "<<endl;
					break;
				}
				else if(scacchiera.patta(computerBianco.getCheckPedestrian(),computerBianco.getCheckAte()))
				{
					fs <<"PATTA PER LA REGOLA DELLE 50 MOSSE"<<endl;
					cout<<"PATTA PER LA REGOLA DELLE 50 MOSSE"<<endl;
					break;
				}

				computerNero.move(scacchiera, fs);
				if(scacchiera.scacco_matto("Bianco"))
				{
					fs <<"HA VINTO IL Nero"<<endl;
					cout<<"HA VINTO IL Nero"<<endl;
					break;
				}
				else if(scacchiera.patta2())
				{
					fs <<"PATTA PER STALLO"<< std::endl;
					cout<<"PATTA PER STALLO "<<endl;
					break;
				}
				else if(scacchiera.patta(computerNero.getCheckPedestrian(),computerNero.getCheckAte()))
				{
					fs <<"PATTA PER LA REGOLA DELLE 50 MOSSE"<<endl;
					cout<<"PATTA PER LA REGOLA DELLE 50 MOSSE"<<endl;
					break;
				}
				
			}
		}


		else 
		{
			Computer computer = Computer('D',maxMoves);
			string s1;
			string s2;
			string test;
			bool isWrong;	
			GiocatoreUmano player = GiocatoreUmano("Bianco",'D');

			//singola mossa giocatore umano	
			if (computer.getColor() == "Nero")
			{
				cout<<"Giocatore umano gioca con il bianco; esegui la tua prima mossa, se vuoi visualizzare la scacchiera puoi in qualsiasi momento digitare 'XX XX': "<<endl;
				do
     		    {

				do
				{
				getline(cin, s);
				if (s.length()<5)
					cout<<"Comando inserito non corrisponde a mosse sulla scacchiera"<<endl;
				}
				while(s.length()<5);
		
  				s1 = s[0];
    			s1 =  s1 + s[1];
				s2 = s[3];
    			s2 =  s2 + s[4];
				
				test = s1 + " " +  s2;
				isWrong = (!isMoveCorrect(s1) || !isMoveCorrect(s2))|| (!scacchiera.checkMove(s1, s2) || !scacchiera.check_start(s1, player.getColor()));
				if (test == "XX XX"||test == "xx xx")
				{
      				out = scacchiera.special();
				for (int i = 0; i<out.size(); i++)
				{
					cout<<out[i]<<endl;
				}
				}
         		else if (isWrong)
                	cout<<"Mossa errata. Scegli un'altra mossa"<<endl;
					
           		}
       			while(isWrong);
				player.move(scacchiera, s1, s2, fs);
			}
			else 
			{
			player.setColor("Nero");
			cout<<"Giocatore umano gioca con il nero; esegui la tua prima mossa, se vuoi visualizzare la scacchiera puoi in qualsiasi momento digitare 'XX XX': "<<endl;
			}


			do
			{
				checkMate = false;
				computer.move(scacchiera, fs);
				if (scacchiera.scacco_matto(player.getColor()))
				{
					fs <<"HA VINTO IL "<<computer.getColor()<<endl;
					cout<<"HA VINTO IL "<<computer.getColor()<<endl;
					checkMate  = true;
				}
				else if(scacchiera.patta2())
				{
					fs <<"PATTA PER STALLO "<<endl;
					cout<<"PATTA PER STALLO "<<endl;
					break;
				}
				
				do
     		    {
					 
            	do
				{
				getline(cin, s);
				if (s.length()<5)
					cout<<"Comando inserito non corrisponde a mosse sulla scacchiera"<<endl;
				}
				while(s.length()<5);

  				s1 = s[0];
    			s1 =  s1 + s[1];
				s2 = s[3];
    			s2 =  s2 + s[4];
				test = s1 + " " +  s2;
				isWrong = (!isMoveCorrect(s1) || !isMoveCorrect(s2)) || (!scacchiera.checkMove(s1, s2) || !scacchiera.check_start(s1, player.getColor()));
				if (test == "XX XX"||test == "xx xx")
				{
      				  out = scacchiera.special();
					for (int i = 0; i<out.size(); i++)
					{
						cout<<out[i]<<endl;
					}
				}
				else if (isWrong)
                	cout<<"Mossa errata. Scegli un'altra mossa"<<endl;
					
           		}
       			while(isWrong);
			
				player.move(scacchiera, s1, s2, fs);
				
				if (scacchiera.scacco_matto(computer.getColor()))
					{
					fs <<"HA VINTO IL "<<player.getColor()<<endl;	
					cout<<"HA VINTO IL "<<player.getColor()<<endl;
					checkMate  = true;
					}
				else if(scacchiera.patta2())
				{
					fs <<"PATTA PER STALLO "<<endl;
					cout<<"PATTA PER STALLO "<<endl;
					checkMate  = true;
				}
				else if(scacchiera.patta(player.getCheckPedestrian(),player.getCheckAte())  &&  !patta)
				{
					patta = true;
					char control ;
					cout<<"PER TERMINARE LA PARTITA PER PATTA DI 50 MOSSE INSERISCI 'p' "<<endl;
					cin>>control;
					cout<<endl;
					if(control == 'p')
					{
					cout<<"PATTA PER LA REGOLA DELLE 50 MOSSE"<<endl;
					checkMate  = true;
					}
					
				}
				
			}
			while (!checkMate);
		}
	fs.close();
	}

