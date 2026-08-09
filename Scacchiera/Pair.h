//Alessio Demo 2007956
#ifndef PAIR_H
#define PAIR_H
#include <iostream>
using namespace std;

class Pair
{
    private:
    int column;
    int line;

public:
    //costruttori
    Pair();
    Pair(int l,int c);
    Pair (string s );

    //metodi getter and setter
    int getColumn();
    int getLine();
    void setColumn(int c);
    void setLine(int l);
    bool operator==(Pair& pa);
};
#endif

