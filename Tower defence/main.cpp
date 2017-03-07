#include <iostream>
#include "Wieza.h"
#include "Wrog.h"
#include "Pocisk.h"
#include "Gracz.h"
#include "Swiat.h"
#include <string>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <cstdio>
#include <windows.h>
#include <math.h>
#define SIZE 25
#define SIZE1 70
#include<fstream>

using namespace std;


int main()
{
    int wygrana,stan_fali; //przechowuje stan rozgrywki
    srand( time( NULL ) );
    Gracz *gracz= new Gracz (50,100);//to gracz
    Swiat *mapa= new Swiat();//tworze mape
    mapa->wypelnienie();
    cout<<"   _: Tower Defence :_"<<endl<<"Legenda:"<<endl<<"+ - znak zabicia lub trafienia lodu"<<endl<<"! - znak zabicia przez laser"<<endl;
    cout<<endl<<"Za pkt kupujesz i levelujesz wieze , zycie rosnie wraz z postepami w grze"<<endl;
    cout<<"Wieze:"<<endl<<endl;
    cout<<"Rakieta - szybko strzela ,duzo pociskow , sredni atak"<<endl<<endl;
    cout<<"Zamrazacz - slaby atak , srednia predkosc strzalu , zostawia na mapie lod ktory atakuje przeciwnika gdy w niego wejdzie i spowalnia"<<endl<<endl;
    cout<<"Laser - duza sila ataku,wolno strzela, atak natychmiastowy"<<endl<<endl;
    cout<<"Stworz wieze > stworz fale > graj! "<<endl;
    cout<<endl<<"Wybierz opcje gry :"<<endl;
    char i;
    do
    {
        gracz->statystyki();
        cout<<endl;
        cout<<"1. Wyswietl liste Elementow"<<endl;
        cout<<"2. Stworz Wieze"<<endl;
        cout<<"3. Stworz Przeciwnika"<<endl;
        cout<<"4. Fala przeciwnikow"<<endl;
        cout<<"5. Pokaz mape"<<endl;
        cout<<"6. Usun element"<<endl;
        cout<<"7. LEVEL UP!"<<endl;
        cout<<"8. GAMESTART!"<<endl;
        cout<<"S. Save Game"<<endl;
        cout<<"L. Load game"<<endl;
        cout<<"0. Wyjscie"<<endl;
        cout<<"Twoj wybor: "<<endl;
        cin>>i;
        system("CLS");
        if (i == '1')  mapa->wypisz_wektor();
        else if (i == '2') mapa->dodaj_wieze(gracz);
        else if (i == '3') mapa->dodaj_wroga();
        else if (i == '4') stan_fali=mapa->losowy_wrog(gracz);
        else if (i == '5') mapa->wypisz_pole();
        else if (i == '6') mapa->usun();
        else if (i == '7') mapa->level(gracz);
        else if (i == '8')
        {
            if (stan_fali==1 ) //musi najpierw sie stowrzyc fale wrogow dopiero mozna grac
            {
                wygrana=mapa->gamestart(gracz,mapa); //zwyciestwo

                if(wygrana==0)
                    return 0;//przegrana
                else if(wygrana==1)//druga runda
                {
                    gracz->hp+=40;
                    gracz->pktdokupienia+=80;
                }
                stan_fali=0;
            }
            else cout<<"Stworz fale (4) "<<endl;
        }
        else if (i == 'S') mapa->save(gracz,mapa);
        else if (i == 'L') stan_fali=mapa->load(gracz,mapa);
        else
            continue;
        cout<<endl;
    }
    while (i != '0');
    delete gracz;
    delete mapa;
    return 0;
}
