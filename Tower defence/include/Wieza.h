#include <iostream>
#define WIEZA_H
#include <string>
#include<vector>
#include <windows.h>
#define SIZE 25
#define SIZE1 70

using namespace std;
class Wrog;
class Pocisk;
class Gracz;
class Swiat;

class Wieza
{
    friend class Wrog;
    friend class Pocisk;
    friend class Gracz;
    friend class Swiat;
    friend class Pocisk_laser;
    friend class Pocisk_rakieta;
    friend class Pocisk_zamrozenie;
protected:
    int dmg,hp,exp,level=1,cena,x,y;
    string typ;
public:
    Wieza(int ,int, string ,int);
    virtual ~Wieza() {};
    void dodaj();
    void dodaj_z_pliku(int pozx,int pozy);
    virtual void setlevel_up()=0;
    void wypisz();
    int szukanie1(int xw ,int yw ,vector<Wrog*> &vectorWrog);
    int szukanie2(int xw ,int yw ,vector<Wrog*> &vectorWrog);
};

class Wieza_rakieta : public Wieza
{
public:
    Wieza_rakieta(int a,int b, string c,int d):Wieza(a,b,c,d){};
    virtual ~Wieza_rakieta() {};
    void setlevel_up();
};
class Wieza_zamrazacz : public Wieza
{
public:
    Wieza_zamrazacz(int a,int b, string c,int d):Wieza(a,b,c,d){};
    virtual ~Wieza_zamrazacz() {};
    void setlevel_up();
};
class Wieza_laser : public Wieza
{
public:
    Wieza_laser(int a,int b, string c,int d):Wieza(a,b,c,d){};
    virtual ~Wieza_laser() {};
    void setlevel_up();
};



