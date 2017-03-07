#include "Wrog.h"
#include <iostream>
#include <cstdlib>
#include <windows.h>
#define SIZE 25
#define SIZE1 70
#include<math.h>
#include<vector>
#include<Swiat.h>
using namespace std;
Wrog::Wrog(int hp1, int dmg1 ,string nazwa,int exp1) //zycie ,atak,nazwa, exp
{
    hp=hp1;
    dmg=dmg1;
    typ=nazwa;
    exp=exp1;
}

void Wrog::dodaj()  //to samo co dla wiezy
{
    cout <<"Podaj polozenie wroga:" <<endl;
    cout<< "x:";
    cin >> x ;
    if(x>69)
        x=69;
    cout<< "y:";
    cin >> y;
    if(y>=24)
        y=23;
}
void Wrog::dodaj_losowo()
{
    do
    {
        x=rand()%15; //losowe polozenie
        y=rand()%24;
    }
    while (x==0 || y==0 || y==24);


    cout<<"Polozenie jego to "<<x<<" , "<<y<<endl;
}
void Wrog::wypisz()
{
    cout<<typ<<endl<<"  - X: "<<x<<endl<<"  - Y: "<<y<<endl;
}
void Wrog::chodzenie(class Swiat* mapa)
{
    mapa->tab[x][y]=' '; //stara pozycja znika znak
    x=x+1;
    mapa->tab[x][y]=typ[0];//nowa pokazuje
}
void Wrog::stanie(class Swiat* mapa) //cofa chodzenie
{
    mapa->tab[x][y]=' ';
    x=x-1;
    mapa->tab[x][y]=typ[0];
}

void Wrog::dodaj_z_pliku(int pozx,int pozy)
{
    x=pozx;
    y=pozy;
}


