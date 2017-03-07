#include "Gracz.h"
#include <iostream>
#include <cstdlib>
#include <windows.h>
#define SIZE 25
#define SIZE1 70
#include<math.h>
#include<vector>
using namespace std;

Gracz::Gracz(int a, int b)
{
    hp=a;
    pktdokupienia=b;

}
void Gracz::statystyki()
{
    cout<<"Twoje zycie :"<<hp<<endl;
    cout<<"Kredyt na wieze :"<<pktdokupienia<<endl;
    cout<<"Przetrwane fale:"<<fale<<endl;
}
