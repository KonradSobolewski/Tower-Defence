#include <iostream>
#include "Wieza.h"
#include "Wrog.h"
#include "Gracz.h"
#include "pocisk.h"
#include "Swiat.h"
#include <cstdlib>
#include <windows.h>
#define SIZE 25
#define SIZE1 70
#include<math.h>
#include<vector>

using namespace std;
Wieza::Wieza(int hp1, int dmg1 , string typ1,int cena1) //zycie ,atak, nazwa,exp ,cena
{
    hp=hp1;
    dmg=dmg1;
    typ=typ1;
    cena=cena1;
}
void Wieza::dodaj()
{
    cout <<"Podaj polozenie Wiezy:" <<endl;
    cout<< "x:";
    cin >> x ;
    if(x>68) //zeby nie wyjsc za mape
        x=68;
    if(x<1)
        x=1;
    cout<< "y:";
    cin >> y;
    if(y>23) //to samo
        y=23;
    if(y<2)
        y=2;
}

void Wieza::dodaj_z_pliku(int pozx,int pozy)
{
    x=pozx;
    y=pozy;
}

void Wieza::wypisz()
{
    cout<<"  - DMG: "<<dmg<<endl<<"  - HP: "<<hp<<endl<<"  - LEVEL: "<<level<<endl<<"  - X: "<<x<<endl<<"  - Y: "<<y<<endl;
}

int Wieza::szukanie1(int xw ,int yw ,vector<Wrog*> &vectorWrog)
{
    //szuka z tw pitagorasa najmniejszej odleglosci do wroga
    int m;
    double minimum=round(sqrt(pow((xw-(vectorWrog[0]->x)),2)+pow((yw-(vectorWrog[0]->y)),2)));
    m=vectorWrog[0]->x;
    for(int j=1; j<vectorWrog.size(); j++)
    {
        if(round(sqrt(pow((xw-(vectorWrog[j]->x)),2)+pow((yw-(vectorWrog[j]->y)),2)))<minimum)
        {
            minimum=round(sqrt(pow((xw-(vectorWrog[j]->x)),2)+pow((yw-(vectorWrog[j]->y)),2)));
            m=vectorWrog[j]->x;
        }
    }
    return m;
}
int Wieza::szukanie2(int xw ,int yw ,vector<Wrog*> &vectorWrog)
{
    //---//---
    //szuka z tw pitagorasa najmniejszej odleglosci do wroga
    int m;
    double minimum=round(sqrt(pow((xw-(vectorWrog[0]->x)),2)+pow((yw-(vectorWrog[0]->y)),2)));
    m=vectorWrog[0]->y;
    for(int j=1; j<vectorWrog.size(); j++)
    {
        if(round(sqrt(pow((xw-(vectorWrog[j]->x)),2)+pow((yw-(vectorWrog[j]->y)),2)))<minimum)
        {
            minimum=round(sqrt(pow((xw-(vectorWrog[j]->x)),2)+pow((yw-(vectorWrog[j]->y)),2)));
            m=vectorWrog[j]->y;
        }
    }
    return m;
}
void Wieza_rakieta::setlevel_up()
{
    hp+=10;
    dmg+=10;
    level+=1;
}
void Wieza_laser::setlevel_up()
{
    hp+=15;
    dmg+=10;
    level+=1;
}
void Wieza_zamrazacz::setlevel_up()
{
    hp+=20;
    dmg+=10;
    level+=1;
}




