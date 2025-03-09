#include <iostream>
#include <fstream>
#include <limits>
#include "elevator.h"
#include "Room.h"
#include "CleaningPlatform.h"

using namespace std;

void addPeople(SpaceForPeople* nplace, Human* nhuman)
{
    int hnumber, hf=nplace->floor();
    double hweight;
    string hproffesion, hname, ifhum;
    cout << "Czy chcesz dodac ludzi do tego miejsca(t/n)?" <<endl;
    cin >> ifhum;
    while(ifhum!="t" && ifhum!="n")
    {
        cout << "Podaj poprawna odpowiedz(t/n)" <<endl;
        cin >> ifhum;
    }
    if(ifhum=="t")
    {
        cout << "Ilu ludzi chcesz dodac?" << endl;
        cin >> hnumber;
        while(cin.fail() || hnumber<1)
        {
            cout << "Podaj liczbe ludzi" << endl;
            cin.clear();
            cin.ignore(numeric_limits<int>::max(),'\n');
            cin >> hnumber;
        }
        for(int i=0; i<hnumber; i++)
        {
            cout << "Podaj wage, imie i profesje"<<endl;
            cin >> hweight;
            cin >> hname;
            cin >> hproffesion;
            while(cin.fail() || hweight<3 || hweight>1000)
            {
                cin.clear();
                cin.ignore(numeric_limits<int>::max(),'\n');
                cout << "Podaj normalna wage, imie i profesje"<<endl;
                cin >> hweight;
                cin >> hname;
                cin >> hproffesion;
            }
            nhuman->changeFloor(hf);
            nhuman->changeWeight(hweight);
            nhuman->changeName(hname);
            nhuman->changeProffesion(hproffesion);
            *nplace+nhuman;
        }
    }
}

int main()
{
    bool go=true;
    int choice, plus, next, floor, wc, count=0, doubletest, fail;
    double sw, lc;
    bool roomdel=0, cpdel=0, elevdel=0, humandel=0;
    string name1, name2, check, ifhum, func;
    ofstream file1;
    ifstream file2;
    vector<SpaceForPeople*> spis;
    Elevator* nelev;
    CleaningPlatform* ncp;
    Room* nroom;
    Human* nhuman;
    while(go)
    {
        cout << "Co chcialbys zrobic?\n"
             << "1- pokaz wszystkie przestrzenie z ludzmi\n"
             << "2- dodaj przestrzen\n"
             << "3- usun przestrzen\n"
             << "4- odczytaj z pliku\n"
             << "5- zpisz wektor przestrzeni do pliku\n"
             << "6- uzyj funkcji double na wybranym elemencie\n"
             << "7- zakoncz program" << endl;
        cin >> choice;
        switch(choice)
        {
        case 1:
            if(spis.size()==0) cout << "Nie ma zadnych obiektow" <<endl;
            for(int i=0; i<spis.size(); i++)
            {
                cout << *(spis[i])<<endl;
            }
        break;

        case 2:
            cout << "Co dodac?\n"
                 << "1- pokoj\n"
                 << "2- winde\n"
                 << "3- platforme do mycia okien" <<endl;
            cin >> plus;
            switch(plus)
            {
            case 1:
                cout << "Podaj pietro, liczbe okien i funckje pokoju" <<endl;
                cin >> floor;
                cin >> wc;
                cin >> func;
                nroom=new Room;
                roomdel=true;
                nhuman=new Human;
                humandel=true;
                while(cin.fail() || floor<1 || floor>20 || wc<0 || wc>100)
                {
                    cin.clear();
                    cin.ignore(numeric_limits<int>::max(),'\n');
                    cout << "Podaj poprawnie pietro(1-20), liczbe okien(1-100) i funckje pokoju" <<endl;
                    cin >> floor;
                    cin >> wc;
                    cin >> func;
                }
                nroom->changefloor(floor);
                nroom->changeWindowsCount(wc);
                nroom->changeFunction(func);
                addPeople(nroom,nhuman);
                spis.push_back(nroom);
                count++;
            break;

            case 2:
                cout << "Podaj pietro i limit obciazenia" <<endl;
                cin >> floor;
                cin >> lc;
                nelev=new Elevator;
                elevdel=true;
                nhuman=new Human;
                humandel=true;
                while(cin.fail() || floor<1 || floor>20 || lc<100)
                {
                    cin.clear();
                    cin.ignore(numeric_limits<int>::max(),'\n');
                    cout << "Podaj poprawnie pietro(1-20) i limit obciazenia(100+)" <<endl;
                    cin >> floor;
                    cin >> lc;
                }
                nelev->changefloor(floor);
                nelev->changeLiftCap(lc);
                addPeople(nelev,nhuman);
                spis.push_back(nelev);
                count++;
            break;

            case 3:
                cout << "Podaj pietro, limit obciazenia i wage sprzetu myjacego(woda plyny)" <<endl;
                cin >> floor;
                cin >> lc;
                cin >> sw;
                ncp=new CleaningPlatform;
                cpdel=true;
                nhuman=new Human;
                humandel=true;
                while(cin.fail() || floor<1 || floor>20 || lc<100 || sw<0)
                {
                    cin.clear();
                    cin.ignore(numeric_limits<int>::max(),'\n');
                    cout << "Podaj poprawnie pietro(1-20) ,limit obciazenia(100+) i wage sprzetu myjacego(woda plyny)" <<endl;
                    cin >> floor;
                    cin >> lc;
                    cin >> sw;
                }
                ncp->changefloor(floor);
                ncp->changeLiftCap(lc);
                ncp->changeStaffWeight(sw);
                addPeople(ncp,nhuman);
                spis.push_back(ncp);
                count++;
            break;

            default:
                cout << "Nie wprowadzono zadnej poprawnej opcji"<< endl;
                if(cin.fail())
                {
                    cin.clear();
                    cin.ignore(numeric_limits<int>::max(),'\n');
                }
            break;
            }

        break;

        case 3:
            cout << "podaj numer elementu do usuniecia" << endl;
            int minus;
            cin >> minus;
            try{
            if(cin.fail() || (spis.size()<minus || minus==0))
            {
                throw "Nie ma takiego elementu";
            }
            spis.erase(spis.begin()+minus-1);
            }catch(char const *s)
            {
                cout << s <<endl;
                cin.clear();
                cin.ignore(numeric_limits<int>::max(),'\n');
            }
        break;

        case 4:
            next=0;
            fail=0;
            cout << "Z ktorego pliku odczytac?" << endl;
            cin >> name2;
            file2.open(name2+".txt");
            if(file2.fail())
            {
                cout << "Blad otwierania pliku" <<endl;
                file2.clear();
            }else spis.clear();
            while(!file2.eof())
            {
                check="";
                file2 >> check;
                if(check=="ELEVATOR")
                {
                    nelev=new Elevator;
                    elevdel=true;
                    spis.push_back(nelev);
                    file2 >> *(spis[next]);
                    next++;
                }else if(check=="CLEANINGPLATFORM")
                {
                    ncp= new CleaningPlatform;
                    cpdel=true;
                    spis.push_back(ncp);
                    file2 >> *(spis[next]);
                    next++;
                }else if(check=="ROOM")
                {
                    nroom=new Room;
                    roomdel=true;
                    spis.push_back(nroom);
                    file2 >> *(spis[next]);
                    next++;
                }else if(check=="")
                {
                    continue;
                }else{
                    getline(file2,check);
                    cout << "Blad w linii "<< fail+1 << " obiekt z niej nie zostal zczytany" << endl;
                }
                fail++;
            }
            file2.close();
        break;

        case 5:
            cout << "Nazwij plik" <<endl;
            cin >> name1;
            file1.open(name1+".txt");
            for(int i=0; i<spis.size(); i++)
            file1 << *(spis[i]);
            file1.close();
        break;

        case 6:
            cout << "Podaj element do uzycia funkcji: " <<endl;
            cin >> doubletest;
            try{
            if(cin.fail() || (spis.size()<doubletest || doubletest==0))
            {
                throw "Nie ma takiego elementu";
            }
            cout << (double) *(spis[doubletest-1]) <<endl;
            }catch(char const *s)
            {
                cout << s <<endl;
                cin.clear();
                cin.ignore(numeric_limits<int>::max(),'\n');
            }
        break;

        case 7:
            go=false;
        break;

        default:
            cout << "Nie wprowadzono zadnej poprawnej opcji" << endl;
            if(cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<int>::max(),'\n');
            }
        break;
        }
    }
    if(cpdel) delete ncp;
    if(roomdel) delete nroom;
    if(elevdel) delete nelev;
    if(humandel) delete nhuman;
    return 0;
}



