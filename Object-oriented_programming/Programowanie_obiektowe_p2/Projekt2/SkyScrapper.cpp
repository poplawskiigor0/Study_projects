#include "SkyScraper.h"
#include <iostream>

/*ostream& operator<<(ostream &s, SkyScraper &sc){
    return s << "WIEZOWIEC:"
             << "\nliczba pieter: " << sc.m_floors
             << "\nadres: " << sc.m_adress<<endl;
}*/ //do ładnego wypisywania na terminal (niekompatybilne z odczytem z pliku)

ostream& operator<<(ostream &s, SkyScraper &sc){
    return s << sc.m_floors << " "
             << sc.m_adress<<endl;
}

istream& operator>>(istream &s, SkyScraper &sc){
    string fullname;
    s >> sc.m_floors;
    getline(s,sc.m_adress);
    return s;
}

SkyScraper::SkyScraper()
{
    #ifdef _DEBUG
    cout << "SkyScrapper()" << endl;
    #endif
    m_floors=20;
    m_adress="Shanghai Tower";
}

SkyScraper::SkyScraper(int floors){
    #ifdef _DEBUG
    cout << "SkyScrapper(int)" << endl;
    #endif
    m_floors=floors;
    m_adress="Shanghai Tower";
}

SkyScraper::SkyScraper(string adress){
    #ifdef _DEBUG
    cout << "SkyScrapper(string)" << endl;
    #endif
    m_floors=20;
    m_adress=adress;
}

SkyScraper::SkyScraper(int floors, string adress){
    #ifdef _DEBUG
    cout << "SkyScrapper(int,string)" << endl;
    #endif
    m_floors=floors;
    m_adress=adress;
}

SkyScraper::SkyScraper(const SkyScraper &s){
    #ifdef _DEBUG
    cout << "Human(Human &e)"<< endl;
    #endif
    m_floors=s.m_floors;
    m_adress=s.m_adress;
}

int SkyScraper::floors()
{
    return m_floors;
}

SkyScraper::~SkyScraper(){
    #ifdef _DEBUG
    cout << "~SkyScrapper()" << endl;
    #endif
}
