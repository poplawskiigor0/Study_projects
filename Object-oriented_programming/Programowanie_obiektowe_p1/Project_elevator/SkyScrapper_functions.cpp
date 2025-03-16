#include "SkyScraper.h"
#include <iostream>

ostream& operator<<(ostream &s, SkyScraper &sc){
    return s << "WIEZOWIEC:"
             << "\nliczba pieter: " << sc.m_floors
             << "\nadres: " << sc.m_adress<<endl;
}

SkyScraper::SkyScraper()
{
    #ifdef _DEBUG
    cout << "SkyScrapper()" << endl;
    #endif
    m_floors=20;
    m_adress="-";
}

SkyScraper::SkyScraper(int floors){
    #ifdef _DEBUG
    cout << "SkyScrapper(int)" << endl;
    #endif
    m_floors=floors;
    m_adress="-";
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

SkyScraper::~SkyScraper(){
    #ifdef _DEBUG
    cout << "~SkyScrapper()" << endl;
    #endif
}
