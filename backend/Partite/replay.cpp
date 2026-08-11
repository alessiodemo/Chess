// Matteo Marcellin  2007946
#include <iostream>
#include "Metodi.h"
#include <chrono>
#include <thread>
#include <vector>
using namespace std;

int main(int argc, char** arg)
{
	chessTable scacchiera = chessTable();
	GiocatoreUmano player1 = GiocatoreUmano("Bianco");
	GiocatoreUmano player2 = GiocatoreUmano("Nero");
	string s1;
	string s2;
	ifstream inFile;
	vector<string> out;
	string s;
	int counter = 1;
	string type = arg[1];
	string input = arg[2];
	input = input + ".txt";
	inFile.open(input);
	
	if (type == "v" || type == "V")
	{
		//Lettura da log e stampa a video
		while (!inFile.eof())
		{
		getline(inFile, s);	
		if(s == "PATTA PER LA REGOLA DELLE 50 MOSSE")
		{
			cout<<"PATTA PER LA REGOLA DELLE 50 MOSSE"<<endl;
			break;
		}	
			
		if(s == "PATTA PER STALLO")	
		{
			cout<<"PATTA PER STALLO"<<endl;
			break;
		}
			
		if(s == "HA VINTO IL Bianco")
		{
			cout<<"HA VINTO IL Bianco"<<endl;
			break;
		}	
			
		if(s == "HA VINTO IL Nero")	
		{
			cout<<"HA VINTO IL Nero"<<endl;
			break;
		}
				
		if (s.length()<5)
			break;
		s1 = s[0];
		s1 =  s1 + s[1];
		s2 = s[3];
		s2 =  s2 + s[4];
		if (counter%2 == 1)
		{
			player1.move(scacchiera, s1, s2);
			cout<<"Mossa del bianco"<<endl;
		}
		else 
		{
			player2.move(scacchiera, s1, s2);
			cout<<"Mossa del nero"<<endl;
		}
		out = scacchiera.special();
		for (int i = 0; i<out.size(); i++)
		{
			cout<<out[i]<<endl;
		}
		cout<<endl;
		cout<<endl;
		counter++;
		std::this_thread::sleep_for(chrono::milliseconds(1000));
		}
	}

	//Lettura da log e stampa a file per s1 e s1
	else if(type == "F" || type == "f")
	{
		string output = arg[3];
		output = output + ".txt";
		ofstream outstream (output);
		while (!inFile.eof())
		{
		getline(inFile, s);	

		if(s == "PATTA PER LA REGOLA DELLE 50 MOSSE")
		{
			outstream<<"PATTA PER LA REGOLA DELLE 50 MOSSE"<<endl;
			break;
		}	
			
		if(s == "PATTA PER STALLO")	
		{
			outstream<<"PATTA PER STALLO"<<endl;
			break;
		}
			
		if(s == "HA VINTO IL Bianco")
		{
			outstream<<"HA VINTO IL Bianco"<<endl;
			break;
		}	
			
		if(s == "HA VINTO IL Nero")	
		{
			outstream<<"HA VINTO IL Nero"<<endl;
			break;
		}

		if (s.length() != 5)
			break;
		s1 = s[0];
		s1 =  s1 + s[1];
		s2 = s[3];
		s2 =  s2 + s[4];
		if (counter%2 == 1)
		{
			player1.move(scacchiera, s1, s2);
			outstream<<"Mossa del bianco"<<endl;
		}
		else 
		{
			player2.move(scacchiera, s1, s2);
			outstream<<"Mossa del nero"<<endl;
		}
		out = scacchiera.special();
		for (int i = 0; i<out.size(); i++)
		{
			outstream<<out[i]<<endl;
		}
		outstream<<endl;
		outstream<<endl;
		counter++;
		}
		outstream.close();
	}
	inFile.close();

return 0;
}
