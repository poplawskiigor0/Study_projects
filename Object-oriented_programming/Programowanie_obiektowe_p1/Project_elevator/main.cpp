#include <iostream>
#include "elevator.h"

using namespace std;

Elevator global;


int main()
{
    {
    cout << "Istnieje juz jedna winda globalna" <<endl;
    cout << "Liczba wind: " << global.HowMany() <<endl;

    cout << "\nDeklaruje trojke ludzi na 6 pietrze" << endl;
    Human zbyszek(6,70,"Zbyszek","Ogrodnik");
    Human anna(6,70,"Anna","Urzednik");
    Human jan(6,700,"Jan","Krytyk kulinarny");

    cout << zbyszek << anna << jan <<endl;

    cout << "\nTworze nowa winde" <<endl;
    Elevator winda;
    cout << "Liczba wind: " << winda.HowMany() <<endl;

    cout << "\nludzi w windzie jest " << winda.m_passengers_count << endl;
    cout <<"winda jest na pietrze " << winda.m_floor << endl;

    cout << "\nWinda jedzie na 6 pietro..." <<endl;
    winda^6;
    cout <<"winda jest na pietrze " << winda.m_floor << endl;

    cout << "\nTrojka ludzi wsiada do windy" <<endl;
    winda+&zbyszek+&anna+&jan;

    cout << "\nWinda probuje jechac na 2 pietro..." <<endl;
    winda^2;

    cout << "\nWinda nie jedzie wiec sprawdzamy jej obciazenie" <<endl;
    cout << "Obciazenie windy: " << (double) winda << "%" << endl;
    cout << "Nastepnie profesje ostatniego pasazera" <<endl;
    cout << winda[2].m_proffesion << endl;
    cout << "Krytyk kulinarny... wyrzucamy go z windy" <<endl;
    winda-"Jan";

    cout << "\nWinda jedze na 2 pietro" <<endl;
    winda^2;
    cout <<"winda jest na pietrze " << winda.m_floor << endl;

    cout << "Liczba wind: " << winda.HowMany() <<endl;
    cout << "Przypisujemy wlasnosci starej windy do windy globalnej\n" << endl;
    global=winda;

    cout << "\nZe starej windy wychodzi Anna" <<endl;
    --winda;

    cout << "\nTworzymy nowa winde konstruktorem kopiujacym stara winde" <<endl;
    Elevator winda2(winda);

    cout << "\nZe starej windy wychodzi Zbyszek" <<endl;
    --winda;

    cout << "\nSprawdzamy parametry wind" <<endl;

    cout << "\nPierwsza winda" <<endl;
    cout << winda << endl;

    cout << "\nDruga winda" <<endl;
    cout << global << endl;

    cout << "\nTrzecia winda" <<endl;
    cout << winda2<< endl;
    }
    cout << "Po wyjsciu z klamerek zostala tylko winda globalna sprawdzmy wiec" <<endl;
    cout << "Liczba wind: " << global.HowMany() <<endl;
    return 0;
}


