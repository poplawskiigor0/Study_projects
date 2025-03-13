#include <iostream>
#include <fstream>
#include <limits>
#include <typeinfo>
#include "elevator.h"
#include "Room.h"
#include "CleaningPlatform.h"

using namespace std;

//KLASA ABTSRAKCYJNA (POPRZEDNI MAIN)
void addPeople(SpaceForPeople* nplace, Human* nhuman)
{
    bool fineh=false;
    int hnumber, hf=nplace->floor();
    double hweight;
    string hproffesion, hname, ifhum;
    while(!fineh)
        {
            try{
            cout << "Czy chcesz dodac ludzi do tego miejsca(t/n)" <<endl;
            cin >> ifhum;
            if(ifhum!="t" && ifhum!="n")
                throw "Bledna odpowiedz";
            fineh=true;
            }catch(const char* s)
                 {
                  cout << s <<endl;
                 }
        }
    fineh=false;
    if(ifhum=="t")
    {
        while(!fineh)
        {
            try {
                cout << "Ilu ludzi chcesz dodac?" << endl;
                cin >> hnumber;
                if(cin.fail()) throw "Nie podano liczby";
                if(hnumber<1) throw "Liczba mniejsza od 1";
                fineh=true;
            } catch (const char* s)
            {
                cout << s << endl;
                cin.clear();
                cin.ignore(numeric_limits<int>::max(),'\n');
            }
        }
        fineh=false;
        for(int i=0; i<hnumber; i++)
        {
            while(!fineh)
            {
                try {
                    cout << "Podaj wage, imie i profesje" << endl;
                    cin >> hweight;
                    cin >> hname;
                    cin >> hproffesion;
                    if(cin.fail()) throw "Podaj odpowiednie wartosci liczbowe";
                    if(hweight<3 || hweight>1000) throw "Podaj realna wage czlowieka";
                    fineh=true;
                } catch (const char* s)
                {
                    cout << s <<endl;
                    cin.clear();
                    cin.ignore(numeric_limits<int>::max(),'\n');
                }
            }
            fineh=false;
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
    int choice, plus, next, floor, wc, count=0, swap1, swap2, fail;
    double sw, lc;
    bool roomdel=0, cpdel=0, elevdel=0, humandel=0;
    string name1, name2, check, ifhum, func;
    ofstream file1;
    ifstream file2;
    SmartBox<SpaceForPeople*> spis;
    Elevator* nelev;
    CleaningPlatform* ncp;
    Room* nroom;
    Human* nhuman;
    while(go)
    {
        cout << "Co chcialbys zrobic?\n"
             << "1- pokaz zawartosc kontenera\n"
             << "2- dodaj przestrzen\n"
             << "3- usun przestrzen\n"
             << "4- odczytaj z pliku\n"
             << "5- zpisz do pliku\n"
             << "6- zamien kolejnosc wybranych elementow\n"
             << "7- zakoncz program" << endl;
        cin >> choice;
        switch(choice)
        {
        case 1:
            spis.show();
        break;

        case 2:
            cout << "Co dodac?\n"
                 << "1- pokoj\n"
                 << "2- winde\n"
                 << "3- platforme do mycia okien" <<endl;
            cin >> plus;
            try{switch(plus)
            {
            case 1:
                bool fine;
                fine=false;
                nroom=new Room;
                elevdel=true;
                nhuman=new Human;
                humandel=true;
                while(!fine)
                    try{
                cout << "Podaj pietro, liczbe okien i funckje pokoju" <<endl;
                cin >> floor;
                cin >> wc;
                cin >> func;
                if(cin.fail()) throw "Podaj poprawne wartosci liczbowe";
                if(floor<1 || floor>20) throw "Podaj pietro w zakresie 1-20";
                if(wc<0 || wc>100) throw "Podaj realna liczbe okien";
                fine=true;
                }
                catch(const char* s)
                {
                    cin.clear();
                    cin.ignore(numeric_limits<int>::max(),'\n');
                    cout << s <<endl;
                }
                nroom->changefloor(floor);
                nroom->changeWindowsCount(wc);
                nroom->changeFunction(func);
                addPeople(nroom,nhuman);
                spis.addLast(nroom);
                count++;
            break;

            case 2:
                bool fine2;
                fine2=false;
                nelev=new Elevator;
                elevdel=true;
                nhuman=new Human;
                humandel=true;
                while(!fine2)
                {
                try{
                    cout << "Podaj pietro i limit obciazenia" <<endl;
                    cin >> floor;
                    cin >> lc;
                    if(cin.fail()) throw "Podaj poprawne wartosci liczbowe";
                    if(floor<1 || floor>20) throw "Podaj pietro w zakresie 1-20";
                    if(lc<100) throw "Podaj sensowny udzwig";
                    fine2=true;
                    }
                    catch(const char* s){
                        cin.clear();
                        cin.ignore(numeric_limits<int>::max(),'\n');
                        cout << s <<endl;
                    }
                }
                nelev->changefloor(floor);
                nelev->changeLiftCap(lc);
                addPeople(nelev,nhuman);
                spis.addLast(nelev);
                count++;
            break;

            case 3:
                bool fine3;
                fine3=false;
                ncp=new CleaningPlatform;
                cpdel=true;
                nhuman=new Human;
                humandel=true;
                while(!fine3)
                {
                    try{
                    cout << "Podaj pietro, limit obciazenia i wage sprzetu myjacego(woda plyny)" <<endl;
                    cin >> floor;
                    cin >> lc;
                    cin >> sw;
                    if(cin.fail()) throw "Podaj poprawne wartosci liczbowe";
                    if(floor<1 || floor>20) throw "Podaj pietro w zakresie 1-20";
                    if(lc<100) throw "Podaj sensowny udzwig";
                    if(sw<0) throw "Nie podawaj wartosci mniejszej od 0";
                    fine3=true;
                    }
                    catch(char const* s)
                    {
                        cin.clear();
                        cin.ignore(numeric_limits<int>::max(),'\n');
                        cout << s <<endl;
                    }
                }
                ncp->changefloor(floor);
                ncp->changeLiftCap(lc);
                ncp->changeStaffWeight(sw);
                addPeople(ncp,nhuman);
                spis.addLast(ncp);
                count++;
            break;

            default:
                if(cin.fail())
                {
                    throw "Nie wprowadzono zadnej poprawnej opcji";
                }
            break;
            }
            }catch(const char* s)
            {
                cout << s << endl;
                cin.clear();
                cin.ignore(numeric_limits<int>::max(),'\n');
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
            spis.deletePart(minus);
            }catch(char const *s)
            {
                cout << s <<endl;
                cin.clear();
                cin.ignore(numeric_limits<int>::max(),'\n');
            }
        break;

        case 4:
            spis.getabstract<Elevator,CleaningPlatform,Room>();
        break;

        case 5:
            spis.saveabstract();
        break;

        case 6:
            cout << "Podaj element do zamiany: " <<endl;
            cin >> swap1;
            cin >> swap2;
            try{
            if(cin.fail() || (spis.size()<swap1 || swap1<=0) || (spis.size()<swap2 || swap2<=0))
            {
                throw "Nie ma takich elementow";
            }
            spis.switchParts(swap1, swap2);
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
            try{
            cout << "Nie wprowadzono zadnej poprawnej opcji" << endl;
            if(cin.fail())
            {
                throw "Blad";
            }
               }catch(const char *)
            {
                cin.clear();
                cin.ignore(numeric_limits<int>::max(),'\n');
            }

        break;
        }
    }
    if(cpdel) delete ncp;
    if(humandel) delete nhuman;
    if(roomdel) delete nroom;
    if(elevdel) delete nelev;
}

//STRINGI
/*int main()
{
    bool go=true;
    int choice, swap1, swap2;
    string add;
    ofstream file1;
    ifstream file2;
    SmartBox<string>  strings1, strings2, strings3;
    strings2.addLast("tak");
    strings2.addLast("nie");
    strings2.addLast("moze");
    strings2.addLast("kot");
    strings3.addLast("chlop");
    strings3.addLast("morze");
    strings3.addLast("dom");
    strings3.addLast("but");
    while(go)
    {
        cout << "Co chcialbys zrobic?\n"
             << "1- pokaz zawartosc kontenera\n"
             << "2- dodaj element do kontenera\n"
             << "3- usun przestrzen\n"
             << "4- odczytaj z pliku\n"
             << "5- zpisz do pliku\n"
             << "6- zamien kolejnosc wybranych elementow\n"
             << "7- przyrownaj kontener do sumy dwoch innych\n"
             << "8- zakoncz program" << endl;
        cin >> choice;
        switch(choice)
        {
        case 1:
            strings1.show();
        break;

        case 2:
            cout << "Podaj element: " <<endl;
            cin >> add;
            try{
            if(cin.fail())
            {
                throw "Blad wprowadzenia";
            }
            strings1.addLast(add);
            }catch(char const *s)
            {
                cout << s <<endl;
                cin.clear();
                cin.ignore(numeric_limits<int>::max(),'\n');
            }
        break;

        case 3:
            cout << "podaj numer elementu do usuniecia" << endl;
            int minus;
            cin >> minus;
            try{
            if(cin.fail() || (strings1.size()<minus || minus==0))
            {
                throw "Nie ma takiego elementu";
            }
            strings1.deletePart(minus);
            }catch(char const *s)
            {
                cout << s <<endl;
                cin.clear();
                cin.ignore(numeric_limits<int>::max(),'\n');
            }
        break;

        case 4:
            strings1.get<string>();
        break;

        case 5:
            strings1.save();
        break;

        case 6:
            cout << "Podaj element do zamiany: " <<endl;
            cin >> swap1;
            cin >> swap2;
            try{
            if(cin.fail() || (strings1.size()<swap1 || swap1<=0) || (strings1.size()<swap2 || swap2<=0))
            {
                throw "Nie ma takich elementow";
            }
            strings1.switchParts(swap1, swap2);
            }catch(char const *s)
            {
                cout << s <<endl;
                cin.clear();
                cin.ignore(numeric_limits<int>::max(),'\n');
            }
        break;

        case 7:
            strings1=strings3+strings2;
        break;

        case 8:
            go=false;
        break;

        default:
            try{
            cout << "Nie wprowadzono zadnej poprawnej opcji" << endl;
            if(cin.fail())
            {
                throw "Blad";
            }
               }catch(const char *)
            {
                cin.clear();
                cin.ignore(numeric_limits<int>::max(),'\n');
            }

        break;
        }
    }
    return 0;
}*/


//WSKAZNIKI INTOW
/*int main()
{
    bool go=true;
    int choice, swap1, swap2;
    int* add;
    int *add2 = new int;
    int *add3 = new int;
    *add2=2;
    *add3=3;
    ofstream file1;
    ifstream file2;
    SmartBox<int*>  int1, int2, int3;
    int2.addLast(add2);
    int3.addLast(add3);
    while(go)
    {
        cout << "Co chcialbys zrobic?\n"
             << "1- pokaz zawartosc kontenera\n"
             << "2- dodaj element do kontenera\n"
             << "3- usun przestrzen\n"
             << "4- odczytaj z pliku\n"
             << "5- zpisz do pliku\n"
             << "6- zamien kolejnosc wybranych elementow\n"
             << "7- przyrownaj kontener do sumy dwoch innych\n"
             << "8- zakoncz program" << endl;
        cin >> choice;
        switch(choice)
        {
        case 1:
            int1.show();
        break;

        case 2:
            add= new int;
            cout << "Podaj element: " <<endl;
            cin >> *add;
            try{
            if(cin.fail())
            {
                throw "Blad wprowadzenia";
            }
            int1.addLast(add);
            }catch(char const *s)
            {
                cout << s <<endl;
                cin.clear();
                cin.ignore(numeric_limits<int>::max(),'\n');
            }
        break;

        case 3:
            cout << "podaj numer elementu do usuniecia" << endl;
            int minus;
            cin >> minus;
            try{
            if(cin.fail() || (int1.size()<minus || minus==0))
            {
                throw "Nie ma takiego elementu";
            }
            int1.deletePart(minus);
            }catch(char const *s)
            {
                cout << s <<endl;
                cin.clear();
                cin.ignore(numeric_limits<int>::max(),'\n');
            }
        break;

        case 4:
            int1.get<int>();
        break;

        case 5:
            int1.save();
        break;

        case 6:
            cout << "Podaj element do zamiany: " <<endl;
            cin >> swap1;
            cin >> swap2;
            try{
            if(cin.fail() || (int1.size()<swap1 || swap1<=0) || (int1.size()<swap2 || swap2<=0))
            {
                throw "Nie ma takich elementow";
            }
            int1.switchParts(swap1, swap2);
            }catch(char const *s)
            {
                cout << s <<endl;
                cin.clear();
                cin.ignore(numeric_limits<int>::max(),'\n');
            }
        break;

        case 7:
            int1=int3+int2;
        break;

        case 8:
            go=false;
        break;

        default:
            try{
            cout << "Nie wprowadzono zadnej poprawnej opcji" << endl;
            if(cin.fail())
            {
                throw "Blad";
            }
               }catch(const char *)
            {
                cin.clear();
                cin.ignore(numeric_limits<int>::max(),'\n');
            }

        break;
        }
    }
    return 0;
}*/

//WINDA
/*int main()
{
    bool go=true;
    int choice, swap1, swap2;
    string add;
    ofstream file1;
    ifstream file2;
    Elevator elev2,elev3,newelev;
    SmartBox<Elevator>  ele1, ele2, ele3;
    Human jan(80,"Jan","Kucharz");
    Human anna(50,"Anna","Prawnik");
    elev2+&jan;
    elev3+&anna;
    ele2.addLast(elev2);
    ele3.addLast(elev3);
    while(go)
    {
        cout << "Co chcialbys zrobic?\n"
             << "1- pokaz zawartosc kontenera\n"
             << "2- dodaj element do kontenera\n"
             << "3- usun przestrzen\n"
             << "4- odczytaj z pliku\n"
             << "5- zpisz do pliku\n"
             << "6- zamien kolejnosc wybranych elementow\n"
             << "7- przyrownaj kontener do sumy dwoch innych\n"
             << "8- zakoncz program" << endl;
        cin >> choice;
        switch(choice)
        {
        case 1:
            ele1.show();
        break;

        case 2:
            ele1.addLast(newelev);
        break;

        case 3:
            cout << "podaj numer elementu do usuniecia" << endl;
            int minus;
            cin >> minus;
            try{
            if(cin.fail() || (ele1.size()<minus || minus==0))
            {
                throw "Nie ma takiego elementu";
            }
            ele1.deletePart(minus);
            }catch(char const *s)
            {
                cout << s <<endl;
                cin.clear();
                cin.ignore(numeric_limits<int>::max(),'\n');
            }
        break;

        case 4:
            ele1.get<Elevator>();
        break;

        case 5:
            ele1.save();
        break;

        case 6:
            cout << "Podaj element do zamiany: " <<endl;
            cin >> swap1;
            cin >> swap2;
            try{
            if(cin.fail() || (ele1.size()<swap1 || swap1<=0) || (ele1.size()<swap2 || swap2<=0))
            {
                throw "Nie ma takich elementow";
            }
            ele1.switchParts(swap1, swap2);
            }catch(char const *s)
            {
                cout << s <<endl;
                cin.clear();
                cin.ignore(numeric_limits<int>::max(),'\n');
            }
        break;

        case 7:
            ele1=ele2+ele3;
        break;

        case 8:
            go=false;
        break;

        default:
            try{
            cout << "Nie wprowadzono zadnej poprawnej opcji" << endl;
            if(cin.fail())
            {
                throw "Blad";
            }
               }catch(const char *)
            {
                cin.clear();
                cin.ignore(numeric_limits<int>::max(),'\n');
            }

        break;
        }
    }
    return 0;
}*/



