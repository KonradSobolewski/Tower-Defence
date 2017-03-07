#include "Swiat.h"
#include "Wieza.h"
#include "Gracz.h"
#include "Wrog.h"
#include "Pocisk.h"
#include <iostream>
#include <stdlib.h>
#include <windows.h>
#define SIZE 25
#define SIZE1 70
#include<math.h>
#include<vector>
#include<fstream>
#include <typeinfo>//badcast
#include <new> //badalloc
using namespace std;
Swiat::Swiat() {};
void Swiat::wypelnienie() // tworzy mape
{
    for(int i=0; i<SIZE; i++)
    {
        {
            for(int j=0; j<SIZE1; j++)
                tab[j][i]=' ';

        }
    }
    for(int j = 0; j<SIZE; j++)
    {
        tab[0][j]='.';
        tab[SIZE1 -1][j]='.';
    }

    for(int i=0; i<SIZE1; i++)
    {
        tab[i][0]='.';
        tab[i][SIZE - 1]='.';
    }
    for(int i=0; i<vectorWieza.size(); i++)//wypisuje istniejace wieze
    {
        tab[vectorWieza[i]->x][vectorWieza[i]->y]=vectorWieza[i]->typ[0];
    }
}
void Swiat::wypisz_pole() //wypisuje mape
{
    for(int i=0; i<SIZE; i++)
    {
        {
            for(int j=0; j<SIZE1; j++)
                cout<<tab[j][i];

        }
        cout<<"\n";
    }
}

void Swiat::dodaj_wieze(class Gracz* gracz)
{


    string typ_wiezy;
    cout << "Podaj typ wiezy: ( Do wyboru : Rakieta(50pkt),Zamrazacz(50pkt),Laser(100pkt) )"<<endl;
    cin>>typ_wiezy;
    if ((typ_wiezy=="Rakieta" || typ_wiezy=="1" || typ_wiezy=="rakieta") && gracz->pktdokupienia>=50)
    {
        try
        {
            Wieza_rakieta* rakieta  = new Wieza_rakieta(40,35,"Rakieta",50);
            rakieta->dodaj();  //przypisuje polozenie
            vectorWieza.push_back(rakieta); //wrzucam na wektor
            tab[rakieta->x][rakieta->y]=rakieta->typ[0]; //wypisuje na mapie Lucznika
            gracz->pktdokupienia-=rakieta->cena; //zmniejszam ilosc pieniedzy ktore posiadam
        }
        catch(bad_alloc&) {}
    }
    else if((typ_wiezy=="Zamrazacz"  || typ_wiezy=="2" || typ_wiezy=="zamrazanie") && gracz->pktdokupienia>=50)
    {
        try
        {
            Wieza_zamrazacz*zamrazacz= new  Wieza_zamrazacz(80,20,"Zamrazacz",50);
            zamrazacz->dodaj();
            vectorWieza.push_back(zamrazacz); //analogicznie
            tab[zamrazacz->x][zamrazacz->y]=zamrazacz->typ[0];
            gracz->pktdokupienia-=zamrazacz->cena;
        }
        catch(bad_alloc&) {}
    }
    else if ((typ_wiezy=="Laser" || typ_wiezy=="3" || typ_wiezy=="laser") && gracz->pktdokupienia>=100)
    {
        try
        {
            Wieza_laser*laser= new Wieza_laser(20,60,"Laser",100); //analogicznie
            laser->dodaj();
            vectorWieza.push_back(laser);
            tab[laser->x][laser->y]=laser->typ[0];
            gracz->pktdokupienia-=laser->cena;
        }
        catch(bad_alloc&) {}
    }
    else
    {
        if(gracz->pktdokupienia<=0) //gdy nie mam pieniedz
            cout<<"Brak srodkow na koncie";
        else  cout<<"Za malo pieniedzy lub nie ma takiej wiezy";
    }
    cout<<endl;
}
void Swiat::usun () //usuwam element po wspolrzednych
{
    int x,y;
    if(!vectorWieza.empty() || !vectorWrog.empty())
    {
        cout<<"Podaj polozenie elementu do usuniecia , sprawdz je uzywajac ( 1 ) z menu"<<endl;
        cout<<"Wspolrzedna x:";
        while (!(cin>>x)) // nie bierze pod uwage innych znakow poza cyframi
        {
            cin.clear();
            cin.sync();
        }
        cout<<"Wspolrzedna y:";
        while (!(cin>>y))
        {
            cin.clear();
            cin.sync();
        }
        int stan=0;//sygnalizuje sukcesywnosc
        for(int i=0; i<vectorWieza.size(); i++)
        {
            if(x==vectorWieza[i]->x && y==vectorWieza[i]->y ) //jesli pozycje s¹ takie same
            {
                delete vectorWieza[i]; //usuwa
                vectorWieza.erase(vectorWieza.begin()+i); //czyszcze wektor
                tab[x][y]=' ';
                cout<<endl<<"Sukces!!"<<endl;
                stan=1;
                break;
            }
            else
            {
                stan=0;
                continue;
            }
        }
        if (stan==0)
            for(int i=0; i<vectorWrog.size(); i++)
            {
                if(x==vectorWrog[i]->x && y==vectorWrog[i]->y)
                {
                    delete vectorWrog[i];
                    vectorWrog.erase(vectorWrog.begin()+i);
                    tab[x][y]=' ';
                    cout<<"Sukces!!"<<endl;
                    stan=1;
                    break;
                }
                else
                {
                    stan=0;
                    continue;
                }
            }
        if(stan==0)
            cout<<"Niepowodzenie!"<<endl;
    }
    else if (vectorWieza.empty() && vectorWrog.empty()) cout<<"Brak elementow do usuniecia"<<endl; //jesli obie listy puste
    cout<<endl;
}

void Swiat::dodaj_wroga() //tak samo jak dla wiezy
{
    string nazwa;
    cout<<"Wybierz wroga ( Do wyboru : Goblin , Smok , Ork )"<<endl;
    cin>>nazwa;
    if (nazwa=="Goblin" || nazwa=="1" || nazwa=="goblin")
    {
        try
        {
            Wrog *goblin= new Wrog (60 , 40,"Goblin",30);
            goblin->dodaj();
            vectorWrog.push_back(goblin);
            tab[goblin->x][goblin->y]=goblin->typ[0];
        }
        catch(bad_alloc&) {}
    }
    else if(nazwa=="Smok" || nazwa=="2" || nazwa=="smok")
    {
        try
        {
            Wrog *smok= new Wrog(75, 60,"Smok",50);
            smok->dodaj();
            vectorWrog.push_back(smok);
            tab[smok->x][smok->y]=smok->typ[0];
        }
        catch(bad_alloc&) {}
    }
    else if (nazwa=="Ork" || nazwa=="3" || nazwa=="ork")
    {
        try
        {
            Wrog *ork = new Wrog(130,20,"Ork",50);
            ork->dodaj();
            vectorWrog.push_back(ork);
            tab[ork->x][ork->y]=ork->typ[0];
        }
        catch(bad_alloc&) {}
    }
    else cout<<"Brak danych na temat wroga";
    cout<<endl;
}

int Swiat::losowy_wrog(class Gracz*gracz) // znow to samo lecz z uwzglednieniem losowosci pola i typu potwora
{
    int stan=1;
    gracz->ilosc_wrogow=gracz->ilosc_wrogow+5;
    string tab2[3]= {"Goblin","Smok","Ork"};
    for(int i=0; i<gracz->ilosc_wrogow; i++)
    {
        string x=tab2[rand()%3];
        cout<<"Twoj wrog to : "<<x<<endl;
        if (x=="Goblin")
        {
            try
            {
                Wrog *goblin= new Wrog (60, 40,"Goblin",30);
                goblin->dodaj_losowo();
                vectorWrog.push_back(goblin);
                tab[goblin->x][goblin->y]=goblin->typ[0];
            }
            catch(bad_alloc&) {}
        }
        else if(x=="Smok")
        {
            try
            {
                Wrog *smok= new Wrog(75, 60,"Smok",50);
                smok->dodaj_losowo();
                vectorWrog.push_back(smok);
                tab[smok->x][smok->y]=smok->typ[0];
            }
            catch(bad_alloc&) {}
        }
        else if (x=="Ork")
        {
            try
            {
                Wrog *ork = new Wrog(120,20,"Ork",50);
                ork->dodaj_losowo();
                vectorWrog.push_back(ork);
                tab[ork->x][ork->y]=ork->typ[0];
            }
            catch(bad_alloc&) {}
        }
    }
    cout<<endl;
    return stan;
}

void Swiat::wypisz_wektor() //wypisuje elementy wektora ktorego wybiore
{
    char x;
    cout<<"Wybierz liste do wypisania"<<endl<<"1 - Wieze"<<endl<<"2 - Wrogowie"<<endl;
    cin>>x;
    if (x=='1')
    {
        if(vectorWieza.empty())
            cout<<"Lista jest pusta"<<endl;
        for(int i=0; i<vectorWieza.size(); i++)
        {
            cout<<i+1<<"."<<vectorWieza[i]->typ<<endl;
            vectorWieza[i]->wypisz();
        }
    }
    else if(x=='2')
    {
        if(vectorWrog.empty())
            cout<<"Lista jest pusta"<<endl;
        for(int i=0; i<vectorWrog.size(); i++)
        {
            cout<<i+1<<".";
            vectorWrog[i]->wypisz();
        }
    }
    else cout<<"Brak danych na temat listy";
    cout<<endl;
}

void Swiat::level(class Gracz* gracz) //podnosi poziom wiez
{
    int znaleziona_wieza=0;//sygnalizuje sukcesywnosc znalezienie wiezy i strate pieniedzy
    string x;
    if(!vectorWieza.empty()) //jesli jakas wieza istnieje
    {

        cout<<"Koszt levelowania 50 pkt"<<endl<<endl;
        cout<<"Wybierz wieze:"<<endl<<"1.Rakieta"<<endl<<"2.Zamrazacz"<<endl<<"3.Laser"<<endl;
        cin>>x;
        if ((x=="Rakieta" || x=="1") && gracz->pktdokupienia>=50 ) //jesli masz pieni¹dze...
        {
            for(int i=0; i<vectorWieza.size(); i++) //przeszukuje vector
            {
                if("Rakieta"==vectorWieza[i]->typ)
                {
                    vectorWieza[i]->setlevel_up();    // i podnosze jej poziom
                    znaleziona_wieza=1;
                }
            }
            if (znaleziona_wieza==1)
                gracz->pktdokupienia-=50; //zaplacilem wiec trace pieniadze
        }
        else if((x=="Zamrazacz" || x=="2" )&& gracz->pktdokupienia>=50)
        {
            for(int i=0; i<vectorWieza.size(); i++)
            {
                if("Zamrazacz"==vectorWieza[i]->typ)
                {
                    vectorWieza[i]->setlevel_up();
                    znaleziona_wieza=1;
                }
            }
            if (znaleziona_wieza==1)
                gracz->pktdokupienia-=50;
        }
        else if ((x=="Laser" || x=="3"  )&& gracz->pktdokupienia>=50)
        {
            for(int i=0; i<vectorWieza.size(); i++)
            {
                if("Laser"==vectorWieza[i]->typ)
                {
                    vectorWieza[i]->setlevel_up();
                    znaleziona_wieza=1;
                }
            }
            if (znaleziona_wieza==1)
                gracz->pktdokupienia-=50;
        }
        else
        {
            znaleziona_wieza=1;
            if(gracz->pktdokupienia<=0)
                cout<<"Brak srodkow na koncie";
            else
                cout<<"Brak informacji na temat wiezy lub za malo pieniedzy";
        }
        if(znaleziona_wieza==0) // czyli nie ma takiej wiezy
            cout<<"Nie stworzyles takiej wiezy";
    }
    else cout<<"Brak wiez"<<endl;
    cout<<endl;
}


int Swiat::load(class Gracz* gracz , class Swiat * mapa)
{
    ///wczytuje wieze,potwory , ilosc pkt i zycie gracza
    string linia;
    int stan=0;
    ifstream dane ("Save.txt");
    if (dane.is_open())
    {
        int x,y;
        int i;
        vectorWrog.clear();
        vectorWieza.clear();
        while ( getline (dane,linia) )
        {
            if(linia=="Rakieta")
            {
                try
                {
                    Wieza_rakieta* rakieta  = new Wieza_rakieta(40,35,"Rakieta",50);
                    getline (dane,linia);
                    x=atoi(linia.c_str());
                    getline (dane,linia);
                    y=atoi(linia.c_str());
                    rakieta->dodaj_z_pliku(x,y);
                    getline (dane,linia);
                    i=atoi(linia.c_str());
                    if (i>1)
                        for(; i>1; i--)
                            rakieta->setlevel_up();
                    vectorWieza.push_back(rakieta);
                    tab[rakieta->x][rakieta->y]=rakieta->typ[0]; //wypisuje na mapie Lucznika
                }
                catch(bad_alloc&) {}
            }
            else if (linia=="Zamrazacz")
            {
                try
                {
                    Wieza_zamrazacz*zamrazacz= new  Wieza_zamrazacz(80,20,"Zamrazacz",50);
                    getline (dane,linia);
                    x=atoi(linia.c_str());
                    getline (dane,linia);
                    y=atoi(linia.c_str());
                    zamrazacz->dodaj_z_pliku(x,y);
                    getline (dane,linia);
                    i=atoi(linia.c_str());
                    if (i>1)
                        for(; i>=1; i--)
                            zamrazacz->setlevel_up();
                    vectorWieza.push_back(zamrazacz);
                    tab[zamrazacz->x][zamrazacz->y]=zamrazacz->typ[0];
                }
                catch(bad_alloc&) {}
            }
            else if (linia=="Laser")
            {
                try
                {
                    Wieza_laser*laser= new Wieza_laser(20,60,"Laser",100);
                    getline (dane,linia);
                    x=atoi(linia.c_str());
                    getline (dane,linia);
                    y=atoi(linia.c_str());
                    laser->dodaj_z_pliku(x,y);
                    getline (dane,linia);
                    i=atoi(linia.c_str());
                    if (i>1)
                        for(; i>=1; i--)
                            laser->setlevel_up();
                    vectorWieza.push_back(laser);
                    tab[laser->x][laser->y]=laser->typ[0];
                }
                catch(bad_alloc&) {}
            }
            else if (linia=="Smok")
            {
                try
                {
                    Wrog *smok= new Wrog(75, 60,"Smok",50);
                    getline (dane,linia);
                    x=atoi(linia.c_str());
                    getline (dane,linia);
                    y=atoi(linia.c_str());
                    smok->dodaj_z_pliku(x,y);
                    vectorWrog.push_back(smok);
                    tab[smok->x][smok->y]=smok->typ[0];
                    stan=1;
                }
                catch(bad_alloc&) {}
            }
            else if (linia=="Ork")
            {
                try
                {
                    Wrog *ork = new Wrog(120,20,"Ork",50);
                    getline (dane,linia);
                    x=atoi(linia.c_str());
                    getline (dane,linia);
                    y=atoi(linia.c_str());
                    ork->dodaj_z_pliku(x,y);
                    vectorWrog.push_back(ork);
                    tab[ork->x][ork->y]=ork->typ[0];
                    stan=1;
                }
                catch(bad_alloc&) {}
            }
            else if (linia=="Goblin")
            {
                try
                {
                    Wrog *goblin= new Wrog (60 , 40,"Goblin",30);
                    getline (dane,linia);
                    x=atoi(linia.c_str());
                    getline (dane,linia);
                    y=atoi(linia.c_str());
                    goblin->dodaj_z_pliku(x,y);
                    vectorWrog.push_back(goblin);
                    tab[goblin->x][goblin->y]=goblin->typ[0];
                    stan=1;
                }
                catch(bad_alloc&) {}
            }
            else if (linia=="Statystki gracza: ")
            {
                getline (dane,linia);
                gracz->hp=atoi(linia.c_str());
                getline (dane,linia);
                gracz->pktdokupienia=atoi(linia.c_str());
                getline(dane,linia);
                gracz->fale=atoi(linia.c_str());
                getline(dane,linia);
                gracz->ilosc_wrogow=atoi(linia.c_str());
            }
        }
        cout<<"Gra wczytana"<<endl;
        dane.close();
    }

    else cout << "Nie udany odczyt";

    return stan;
}


int Swiat::save(class Gracz* gracz , class Swiat * mapa)
{
///zapisuje wieze ,potwory ,ilosc punktow i zycie gracza
    ofstream dane ("Save.txt");
    if (dane.is_open())
    {
        if(!vectorWieza.empty())
        {
            for(int i =0 ; i< vectorWieza.size(); i++)
            {
                dane << vectorWieza[i]->typ<<endl;
                dane << vectorWieza[i]->x<<endl;
                dane << vectorWieza[i]->y<<endl;
                dane << vectorWieza[i]->level<<endl;
            }
        }
        if(!vectorWrog.empty())
        {
            for(int i =0 ; i< vectorWrog.size(); i++)
            {
                dane << vectorWrog[i]->typ<<endl;
                dane << vectorWrog[i]->x<<endl;
                dane << vectorWrog[i]->y<<endl;
            }
        }
        dane << "Statystki gracza: "<<endl;
        dane << gracz->hp<<endl;
        dane << gracz->pktdokupienia<<endl;
        dane << gracz->fale<<endl;
        dane << gracz->ilosc_wrogow<<endl;
        dane.close();
        cout<<"Gra zapisana"<<endl;
    }
    else cout << "Zapis sie nie powiódł";
    return 1;
}

int Swiat::gamestart(class Gracz *gracz,class Swiat* mapa)
{
    int stan ,win; //pomocnicza i swiadczaca o zwyciestwie ,gdy wszyscy doszli do konca mapy
    int licznik=0,licznik2=1;
    int zabitewieze=0,zabiciwrogowie=0; // pierwsza 0 gdy posiada zycie ,1 gdy nie , druga 1 gdy wszystkie dotarly na koniec mapy
    int stan2=0;//pomocnicze
    int wrogowie=vectorWrog.size(); // pomocnicza przy wypisywaniu
    mapa->wypisz_pole();
    for(int i=0; ; i++)
    {
        system("CLS"); //czyszcze ekran i rozpoczynam operacje
        for (int j=0; j<vectorWrog.size(); j++)
        {
            if ((vectorWrog[j]->x)!=SIZE1-2 && vectorWrog[j]->stan_chodzenia==1)//jeśli przeciwnik nie jest zamrożony i nie jest na koncu mapy
            {
                vectorWrog[j]->chodzenie(mapa); //każdy przeciwnik wykonuje krok
                licznik2=0;
            }
            else if ((vectorWrog[j]->x)==SIZE1-2 && vectorWrog[j]->stanataku==1) //gdy moze atakowac i doszedl na koniec mapy
            {
                gracz->hp-=vectorWrog[j]->dmg;//atakuje gracza
                vectorWrog[j]->stanataku=0; // juz nie zaatakuje

                if(gracz->hp<=0)  //gdy zycie zero
                {
                    licznik=1;/**decyduje o zakończeniu programu, znak ze zycie <=0**/
                    break;
                }
            }
            else if ((vectorWrog[j]->x)==SIZE1-2 && vectorWrog[j]->stanataku==0)//jesli wrog zaatakowal to go usuwam
            {
                delete vectorWrog[j];
                vectorWrog.erase(vectorWrog.begin()+j);
                zabiciwrogowie++;
            }
        }
        if(licznik==1)/**wyjscie z petli patrz powyżej**/
            break;

        for(int c=0; c<vectorWieza.size(); c++)
        {
            int m=0,n=0;
            m=vectorWieza[c]->szukanie1(vectorWieza[c]->x,vectorWieza[c]->y,vectorWrog); //szukam pozycje x najblizszego przeciwnika
            n=vectorWieza[c]->szukanie2(vectorWieza[c]->x,vectorWieza[c]->y,vectorWrog);  // --//-- y --//--
            if(vectorWieza[c]->typ=="Rakieta")
            {
                try
                {
                    Pocisk_rakieta* strzala= new Pocisk_rakieta(vectorWieza[c]->x,vectorWieza[c]->y,"kula",m,n,vectorWieza[c]->dmg);// tworze pocisk dla odp wiezy
                    vectorPocisk.push_back(strzala);
                }
                catch(bad_alloc&) {}
            }
            else if(vectorWieza[c]->typ=="Laser" && i%7==0) //tworze co 7 tur(wolnostrzelna)
            {
                try
                {
                    Pocisk_laser* strzala= new Pocisk_laser(vectorWieza[c]->x,vectorWieza[c]->y,"laser",m,n,vectorWieza[c]->dmg);
                    vectorPocisk.push_back(strzala);
                }
                catch(bad_alloc&) {}
            }
            else if(vectorWieza[c]->typ=="Zamrazacz" && i%7==0) //tworze co 7 tur(wolnostrzelna)
            {
                try
                {
                    Pocisk_zamrozenie* strzala= new Pocisk_zamrozenie(vectorWieza[c]->x,vectorWieza[c]->y,"zamrozenie",m,n,vectorWieza[c]->dmg);
                    vectorPocisk.push_back(strzala);
                }
                catch(bad_alloc&) {}
            }
        }
        for (int j=0; j<vectorPocisk.size(); j++)//procedura strzelania pociskami
        {
            if(vectorPocisk[j]->typ=="kula")//przeszukuje vector za odpowiednim pociskiem
            {
                try
                {
                    if(Pocisk_rakieta* x=dynamic_cast<Pocisk_rakieta*>(vectorPocisk[j]))
                        x->lot(mapa);
                }
                catch(bad_cast&) { cout << " catch!";}
            }
            else if (vectorPocisk[j]->typ=="zamrozenie" )
            {
                try
                {
                    if(Pocisk_zamrozenie* x=dynamic_cast<Pocisk_zamrozenie*>(vectorPocisk[j]))
                    {
                        x->zamrozenie(vectorPocisk[j]->celx,vectorPocisk[j]->cely,j,mapa,i);
                        stan2=1;
                    }
                }
                catch(bad_cast&) { cout << " catch!";}
            }
            else if (vectorPocisk[j]->typ=="laser")
            {
                try
                {
                    if(Pocisk_laser* x=dynamic_cast<Pocisk_laser*>(vectorPocisk[j]))
                    {
                        x->laser(x->celx,x->cely,j,mapa );//trafia odrazu
                        stan=1; //swiadczy ze mozna usunac pocisk
                    }
                }
                catch(bad_cast&) { cout << " catch!"; }
            }

            if (vectorPocisk[j]->x>=SIZE1-2 || vectorPocisk[j]->x<=1 || vectorPocisk[j]->y>=SIZE-1 || vectorPocisk[j]->y<=0 )
            {
                //gdy pocisk zblizy sie do granicy mapy jest niszczony
                mapa->tab[vectorPocisk[j]->x][vectorPocisk[j]->y]=' ';
                delete vectorPocisk[j];
                vectorPocisk.erase(vectorPocisk.begin()+j);
            }
            for (int z=0; z<vectorWrog.size(); z++)
            {
                if (vectorWrog[z]->x==vectorPocisk[j]->x && vectorWrog[z]->y==vectorPocisk[j]->y )
                {
                    //jesli wrog spotka sie z pociskiem traci zycie lub ginie
                    vectorWrog[z]->hp-=vectorPocisk[j]->dmg;
                    mapa->tab[vectorPocisk[j]->x][vectorPocisk[j]->y]=vectorWrog[z]->typ[0];
                    delete vectorPocisk[j];
                    vectorPocisk.erase(vectorPocisk.begin()+j);
                    if(vectorWrog[z]->hp<=0)
                    {
                        mapa->tab[vectorWrog[z]->x][vectorWrog[z]->y]=' ';
                        delete vectorWrog[z];
                        vectorWrog.erase(vectorWrog.begin()+z);
                    }
                }
            }
        }
        for (int z=0; z<vectorPocisk.size(); z++)
        {
            if(vectorPocisk[z]->typ=="laser") //usuwam pocisk laser po oddaniu strzalu
            {
                if (stan==1)
                {
                    delete vectorPocisk[z];
                    vectorPocisk.erase(vectorPocisk.begin()+z);
                    stan=0;
                }
            }
            else if (vectorPocisk[z]->typ=="kula") //jesli pocisk kuli spotka sie z wieżą, wieza traci życie lub ginie
            {
                for (int s=0; s<vectorWieza.size(); s++)
                {
                    if (vectorWieza[s]->x==vectorPocisk[z]->x && vectorWieza[s]->y==vectorPocisk[z]->y ) //tzw rykoszet ,jak trafie swoja wieze tez moze zginać
                    {
                        vectorWieza[s]->hp-=vectorPocisk[z]->dmg;
                        mapa->tab[vectorPocisk[z]->x][vectorPocisk[z]->y]=vectorWieza[s]->typ[0];
                        delete vectorPocisk[z];
                        vectorPocisk.erase(vectorPocisk.begin()+z);
                        if( vectorWieza[s]->hp<=0)
                        {
                            mapa->tab[vectorWieza[s]->x][vectorWieza[s]->y]=' ';
                            delete vectorWieza[s];
                            vectorWieza.erase(vectorWieza.begin()+s);
                            zabitewieze++;
                        }
                    }
                }
            }
            else if (vectorPocisk[z]->typ=="zamrozenie")//usuwam pocisk po oddaniu strzalu
            {
                if(stan2=1)
                {
                    delete vectorPocisk[z];
                    vectorPocisk.erase(vectorPocisk.begin()+z);
                    stan2=0;
                }
            }
        }
        for(int c=0; c<vectorWieza.size(); c++)
        {
            //jesli wrog trafi wieze to otrzyumuje obrazenia lub ginie
            for (int z=0; z<vectorWrog.size(); z++)
            {
                if (vectorWieza[c]->x==vectorWrog[z]->x && vectorWieza[c]->y==vectorWrog[z]->y )
                {
                    vectorWieza[c]->hp-=vectorWrog[z]->dmg;
                    mapa->tab[vectorWrog[z]->x][vectorWrog[z]->y]=vectorWieza[c]->typ[0];
                    delete vectorWrog[z];
                    vectorWrog.erase(vectorWrog.begin()+z);
                    if(vectorWieza[c]->hp<=0)
                    {
                        mapa->tab[vectorWieza[c]->x][vectorWieza[c]->y]=' ';
                        delete vectorWieza[c];
                        vectorWieza.erase(vectorWieza.begin()+c);
                        zabitewieze++;
                    }
                }
            }
        }
        for(int c=0; c<vectorWieza.size(); c++)//wypisuje znowu istniejace wieze na mapie zeby znaki nie byly zasloniete
        {
            mapa->tab[vectorWieza[c]->x][vectorWieza[c]->y]=vectorWieza[c]->typ[0];
        }
        for(int c=0; c<vectorWrog.size(); c++)//wypisuje znowu istniejace wroga na mapie zeby znaki nie byly zasloniete
        {
            mapa->tab[vectorWrog[c]->x][vectorWrog[c]->y]=vectorWrog[c]->typ[0];
        }
        mapa->wypisz_pole();
        Sleep(50);
        if(vectorWrog.empty() && gracz->hp>0) //zwyciestwo
        {
            win=1;
            gracz->fale++;
            break;
        }
    }
    if((!vectorWrog.empty() && gracz->hp<=0)||(vectorWrog.empty() && gracz->hp<=0)) //porazka
    {
        cout<<endl<<"Porazka :( "<<endl;
        win=0;
    }
    if(win==1)
    {
        cout<<endl<<"Wygrales!! :D "<<endl;
    }

    system("pause"); //statystyki gry
    cout<<"Przetrwane fale: "<<gracz->fale<<endl;
    if(vectorWrog.empty())
        cout<<"Przezylo wrogow: "<<zabiciwrogowie<<" z "<<wrogowie<<endl;
    else  cout<<"Przezylo wrogow: "<<vectorWrog.size()+zabiciwrogowie<<" z "<<wrogowie<<endl;
    if (zabitewieze>0)
        cout<<"Stracone Wieze: "<<zabitewieze<<endl;
    vectorPocisk.clear(); //usuwam wrogow pozostalych i wszystkie pociski jesli takie pozostaly
    vectorWrog.clear();
    gracz->statystyki();
    mapa->wypelnienie();
    system("pause");
    return win;
}
