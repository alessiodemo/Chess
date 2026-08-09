//Alessio Demo 2007956
#ifndef CHESS_H
#define CHESS_H
#include <vector>
#include "Pezzo.h"
using namespace std;


class chessTable
{
    //matrice
    private :
    Pezzo* matrix[8][8];
    //lista di aiuto che viene usata nel metodo scacco_matto, e contiene solamente pedine aventi delle mosse specifiche per "salvare il re dallo scacco"
    list<Pezzo*> help;

    //metodo che ritorna la posizione (se esiste) del pezzo avversario che tiene sotto scacco il re (il colore passato come parametro corrisponde al colore del re), la posizione del re è il primo parametro passato al metodo
    Pair dangerous( Pair pa_re, string colore);

    //metodi che vengono richimati nei corrispettivi metodi "ricercaMosse..." e hanno il compito di inserire nell'oggetto di tipo Pezzo le case raggiungibili a seconda del tipo di pezzo (Cavallo, Pedone ecc...)
    void ricercaScaccoTorre(Pezzo* pezzo);
    void ricercaScaccoAlfiere(Pezzo* pezzo);
    void ricercaScaccoDonna(Pezzo* pezzo);
    void ricercaScaccoCavallo(Pezzo* pezzo);
    void ricercaScaccoRe(Pezzo* pezzo);
    void ricercaScaccoPedone(Pezzo* pezzo);
    //metodo che compie una "virtualizzazione" del pezzo passato come parametro, facendolo momentaneamente spostare in un determinata casella per poi controllare la condizione di scacco del proprio re e se spostando il pezzo il re finisce sotto scacco allora la mossa non può essere fatta
    // ma se invece spostando il pezzo sia annulla la condizione di scacco per persisteva prima dello spostamento , allora si rende la mossa obbligatoria inserendola nella lista help (parametro di chessTable) 
    void virtualization(Pezzo* pezzo);

    public:
    Pair getPos_re(string color) const;
    //costruttore
    chessTable();

    //costruttori e assegnamenti di copia e spostamento
    chessTable(const chessTable& arg);
    chessTable& operator=(const chessTable& t); 
    chessTable(chessTable& arg);
    chessTable& operator=( chessTable&& t);

    //metodi getter and setter listaHelp
    list<Pezzo*>& getHelp();
    void setHelp();
    void setHelp(Pezzo* pe);
    
    //metodo getter che ritorna il puntatore a un oggetto di tipo pezzo presente in una determinata casa della scacchiera
    Pezzo* getValue( Pair pa) const;
    //metodo setter che posiziona un nuovo puntatore di tipo pezzo/nullo nella casella rappresentata dall'oggetto di classe Pair passato come parametro
    void setValue(Pair pa, Pezzo* pe);

    //metodo per rilevazione scacco matto --> esegue una "virtualizzazione" del re spostandolo in ogni casa in cui puo' andaree vedendo se in ciascuna di queste e' sotto scacco o meno
    //se in ciascuna di queste e' sotto scacco e la lista help e' vuota, allora e' sottoscacco matto, altrimenti no
    bool scacco_matto(string color);

    //metodo bool per il rilevamento della condizione di scacco, viene passata la posizione del re tramite un oggetto di classe Pair e il colore del re per cui si vuole controllare la condizione di scacco
    bool scacco(Pair pa_re, string colore);

    //metodo per rilevazione patta per 50 mosse consecutive senza aver mangiato dei pezzi o spostato un pedone
    bool patta(int chechPedone, int checkMangiato);
    //metodo per rilevazione patta per indisponibilita' di pezzi con almeno una mossa disponibile ( con il re che non  e' sotto scacco)
    bool patta2();
    
    //metodo che risponde al comando XX XX e stampa la configurazione corrente della tastiera
    vector<string> special();
   
    //metodo per rilevare la possibile mutazione del pedone in una qualsiasi altra pedina in caso raggiunga il lato opposto della tastiera il  metodo riceve come parametro un char che identifica la pedina in cui il pedone si trasformerà 
    void pedestrian_becomes_queen (char carattere);

    //metodo bool per il rilevamento della condizione di arrocco, il quale controlla che le posizioni di torri e re siano idonee e che nelle case che intercorrono tra i due pezzi  il re non finisca sotto scacco in nessuna di esse e che inoltre non ci sia alcuna pedina in nessuna di esse.
    bool arrocco (Pair t, string colore);

    //metodo che controlla la validità del range numerico della colonna e della riga della casa passata al metodo attraverso un oggetto di classe Pair
    bool check_range(Pair pa) const;
    //metodo che controlla che nella posizione iniziale della mossa , non ci sia un pezzo di colore diverso dal giocatore che sta effettuando la mossa, o che la casa non contenga un puntatore nullo
    bool check_start(string s, string color) const;
    //metodo che controlla che nella ipotetica casa di arrivo della mossa che si sta effettuando ci sia una pedina dello stesso colore di quella che sta effettuando la mossa
    bool isSamePlayer(Pair pa1, Pair pa2) const;
    //metodo che controlla che nella casa passata come parametro attraverso un oggetto di tipo Pair ci sia un puntatore nullo
    bool isNull(Pair pa1) const;

    //metodi ricercaMosse per ciascun tipo di pedina
    void ricercaMosseTorre(Pezzo* to);
    void ricercaMosseAlfiere(Pezzo* al);
    void ricercaMosseCavallo(Pezzo* ca);
    void ricercaMosseDonna(Pezzo* da);
    void ricercaMosseRe(Pezzo* re);
    void ricercaMossePedone(Pezzo* pe);    

    //metodo che ritorna una lista di puntatori a dei pezzi di colore nero , non nulli, con almeno una mossa disponibile
    std::list<Pezzo*> getListNero() const;
    //metodo che ritorna una lista di puntatori a dei pezzi di colore bianco , non nulli, con almeno una mossa disponibile
    std::list<Pezzo*> getListBianco() const;
    
    //metodo che controlla che il pezzo nella casa passata come primo parametro , abbia tra le proprie mosse disponibili la casa passata come secondo parametro, e che  quindi possa trasferirsi su quest' ultima
    bool checkMove(string partenza,string arrivo);
    //distruttore
    ~chessTable();

};

#endif
