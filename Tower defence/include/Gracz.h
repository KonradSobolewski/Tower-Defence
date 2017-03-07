#define GRACZ_H
#include <iostream>
#include <cstdlib>
#include <windows.h>
#define SIZE 25
#define SIZE1 70
#include<math.h>
#include<vector>
using namespace std;
class Wrog;
class Pocisk;
class Wieza;

class Gracz
{

public:
    int hp,fale=0;
    int ilosc_wrogow=0;
    int pktdokupienia;//kupujesz za to wieze i levelujesz
    Gracz(int,int=100);
    ~Gracz() {};
    void statystyki();
    friend class Wrog;
    friend class Pocisk;
    friend class Wieza;
};

