#define POCISK_H
#include <iostream>
#include <cstdlib>
#include <windows.h>
#define SIZE 25
#define SIZE1 70
#include<math.h>
#include<vector>
using namespace std;
class Wrog;
class Wieza;
class Gracz;
class Swiat;

class Pocisk
{
protected:
    int celx;
    int cely;
    string typ;
    int x,y;
    int dmg;
public:
    Pocisk(int,int,string ,int, int,int);
    virtual ~Pocisk() {};

    friend class Wrog;
    friend class Wieza;
    friend class Gracz;
    friend class Swiat;
    friend class Pocisk_laser;
    friend class Pocisk_rakieta;
    friend class Pocisk_zamrozenie;

};

class Pocisk_rakieta : public Pocisk
{
public:
    Pocisk_rakieta(int a,int b, string nazwa,int celx1,int cely1,int dmg1):Pocisk(a,b,nazwa,celx1,cely1,dmg1)
    {};
    virtual ~Pocisk_rakieta() {};
    void lot(class Swiat* mapa);

};
class Pocisk_laser : public Pocisk
{
public:
    Pocisk_laser(int a,int b, string nazwa,int celx1,int cely1,int dmg1):Pocisk(a,b,nazwa,celx1,cely1,dmg1)
    {};
    virtual ~Pocisk_laser() {};
    void laser(int x,int y,int pozycja,class Swiat* mapa);

};
class Pocisk_zamrozenie : public Pocisk
{
public:
    Pocisk_zamrozenie(int a,int b, string nazwa,int celx1,int cely1,int dmg1):Pocisk(a,b,nazwa,celx1,cely1,dmg1)
    {};
    virtual ~Pocisk_zamrozenie() {};
    friend class Swiat;
    void zamrozenie (int x,int y,int pozycja,class Swiat* mapa ,int iter);
};

