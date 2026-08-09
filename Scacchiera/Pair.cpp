//Alessio Demo 2007956
#include "Pair.h"
using namespace std;
Pair::Pair()
{

}
Pair::Pair(int l,int c)
{
    this->column=c;
    this->line=l;
}

Pair::Pair(string s)
{
    setColumn(toupper(s[0])-65);
    setLine(-1*(s[1]-56));
}

void Pair::setColumn(int c){this->column=c;}
void Pair::setLine(int l){this->line=l;}
int Pair::getColumn(){return this->column;}
int Pair::getLine(){return this->line;}
//overloading operator ==
bool Pair::operator==(Pair& pa)
{
   if (getLine() == pa.getLine() && getColumn() == pa.getColumn())
      return true;
   return false;
}
