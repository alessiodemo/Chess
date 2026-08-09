//Veneziani Michele 2007955
#include "Pezzo.h"
Pezzo::Pezzo(char n, Pair pa, int number)
{
   setName(n);
   if (n >= 'a' && n <= 'z')
      setColor("Bianco");
   else
      setColor("Nero");
   setCurrent_position(pa);
   setNumMosse(number);
}
Pezzo::Pezzo(char n, Pair pa, std::list<Pair> lista, int number)
{
   setName(n);
   if (n >= 'a' && n <= 'z')
      setColor("Bianco");
   else
      setColor("Nero");
   setCurrent_position(pa);
   available_actions = lista;
   setNumMosse(number);
}
string Pezzo::getColor()
{
   return color;
}
void Pezzo::setColor(string c)
{
   color = c;
}
char Pezzo::getName()
{
   return name;
}
void Pezzo::setName(char n)
{
   name = n;
}
std::list<Pair>& Pezzo::getAvailable_actions()
{
   return available_actions;
}
void Pezzo::setAvailable_actions()
{
   available_actions.clear();
}
void Pezzo::setAvailable_actions(Pair pa)
{
   available_actions.push_back(pa);
}
Pair Pezzo::getCurrent_position()
{
   return current_position;
}
void Pezzo::setCurrent_position(Pair p)
{
   current_position = p;
}
int Pezzo::getNumMosse()
{
   return numMosse;
}
void Pezzo::setNumMosse(int number)
{
   numMosse = number;
}
