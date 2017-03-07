#define SWIAT_H
#include <iostream>
#include <cstdlib>
#include <windows.h>
#define SIZE 25
#define SIZE1 70
#include<math.h>
#include<vector>
#include<fstream>
using namespace std;
class Wieza;
class Pocisk;
class Wrog;
class Gracz;

class Swiat
{
    char tab[SIZE1][SIZE];

public:
    Swiat();
    ~Swiat() {};
    void wypelnienie();
    void dodaj_wieze(class Gracz* gracz);
    void usun ();
    void dodaj_wroga() ;
    int losowy_wrog(class Gracz* gracz);
    void wypisz_wektor();
    void level(class Gracz* gracz);
    int save(class Gracz* gracz , class Swiat * mapa);
    int load(class Gracz* gracz , class Swiat * mapa);
    int gamestart(class Gracz *gracz,class Swiat* mapa);
    void wypisz_pole();
    vector<Wieza*> vectorWieza;
    vector<Wrog*> vectorWrog; // 3 wektory dla ka¿dego typu klas
    vector<Pocisk*> vectorPocisk;


    friend class Wieza;
    friend class Pocisk;
    friend class Wrog;
    friend class Gracz;
    friend class Pocisk_laser;
    friend class Pocisk_rakieta;
    friend class Pocisk_zamrozenie;
};


