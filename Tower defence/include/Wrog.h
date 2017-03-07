#include <iostream>
#define WROG_H
#include <cstdlib>
#include <windows.h>
#define SIZE 25
#define SIZE1 70
#include<math.h>
#include<vector>

using namespace std;
class Wieza;
class Pocisk;
class Gracz;
class Swiat;

class Wrog
{

    int dmg , hp ,exp ;
    string typ;
    int x ,y ;
    int stanataku=1;//moze atakowac gracza
    int stan_chodzenia=1;//moze chodzic zalezne od zamrozenia
public:

    Wrog(int ,int, string,int);
    ~Wrog(){};
    void dodaj();
    void dodaj_losowo();
    void wypisz();
    void dodaj_z_pliku(int pozx,int pozy);
    void chodzenie(class Swiat* mapa);
    void stanie(class Swiat* mapa);
    friend class Wieza;
    friend class Pocisk;
    friend class Pocisk_laser;
    friend class Pocisk_rakieta;
    friend class Pocisk_zamrozenie;
    friend class Gracz;
    friend class Swiat;
};

