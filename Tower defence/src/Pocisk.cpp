#include "Pocisk.h"
#include "Wrog.h"
#include <iostream>
#include "Wieza.h"
#include <cstdlib>
#include <windows.h>
#define SIZE 25
#define SIZE1 70
#include<math.h>
#include<vector>
#include<Swiat.h>
using namespace std;

Pocisk::Pocisk( int pozx ,int pozy,string nazwa,int cx,int cy,int dmg1 )// polozenie x ,polozenie y ,nazwa, cel x cel y,siłą
{
    dmg=dmg1;
    if(pozx>cx)
    x=pozx-1;
    else if(pozx<cx)
       x=pozx+1;
    else x=pozx+1;
     if(pozy>cy)
    y=pozy-1;
    else if(pozy<cy)
        y=pozy+1;
     else y=pozy+1;
    typ=nazwa;
    celx=cx;
    cely=cy;
}
void Pocisk_rakieta::lot(class Swiat* mapa) // kieruje sie w strone wroga
{
    int lastx=x,lasty=y;
    if(x>celx)
        x-=1;
    else if (x<celx)
        x+=1;
    else x=x;
    if(y<cely)
        y+=1;
    else if(y>cely)
        y-=1;
    else y=y;
    mapa->tab[x][y]='-';
    mapa->tab[lastx][lasty]=' ';

}

void Pocisk_laser::laser(int x,int y,int pozycja,class Swiat* mapa ) //podobonie do zamrozenia ale nie zatrzymuje
{
    for(int i=0; i<mapa->vectorWrog.size(); i++)
    {
        if(x==mapa->vectorWrog[i]->x && y==mapa->vectorWrog[i]->y)
        {
            mapa->vectorWrog[i]->hp-=mapa->vectorPocisk[pozycja]->dmg;

            if(mapa->vectorWrog[i]->hp<=0)
            {
                mapa->tab[mapa->vectorWrog[i]->x][mapa->vectorWrog[i]->y]='!';
                delete mapa->vectorWrog[i];
                mapa->vectorWrog.erase(mapa->vectorWrog.begin()+i);
            }
        }
        else
        {
            continue;
        }
    }
}

void Pocisk_zamrozenie::zamrozenie (int x,int y,int pozycja,class Swiat* mapa ,int iter)
{//celx,cely ,ktory pocisk,wektoty , mapa, iteracja gamestart
    for(int i=0; i<mapa->vectorWrog.size(); i++)
    {
        if(x==mapa->vectorWrog[i]->x && y==mapa->vectorWrog[i]->y) //pozycje takie same
        {
            mapa->vectorWrog[i]->stan_chodzenia=0;
            //mapa->vectorWrog[i]->stanie(mapa); //cofa ruch przeciwnika czyli stoi w miesjscu
            mapa->vectorWrog[i]->hp-=mapa->vectorPocisk[pozycja]->dmg;
            mapa->tab[mapa->vectorPocisk[pozycja]->celx+1][mapa->vectorPocisk[pozycja]->cely]='+';
            if(iter%7>=2 && iter%7<=5)
                mapa->vectorWrog[i]->stan_chodzenia=1;

            if(mapa->vectorWrog[i]->hp<=0) //jesli te¿ zabija to usuwa oba elementy , powstaje gora lodowa bo bo pocisk gdy nie zabija nie jest usuwany
            {
                mapa->tab[mapa->vectorWrog[i]->x][mapa->vectorWrog[i]->y]='+';
                mapa->tab[mapa->vectorWrog[i]->x+1][mapa->vectorWrog[i]->y]=' ';
                delete mapa->vectorWrog[i];
                mapa->vectorWrog.erase(mapa->vectorWrog.begin()+i);
            }
        }
        else mapa->vectorWrog[i]->stan_chodzenia=1; //moze chodzic
        {
            continue;
        }
    }
}
