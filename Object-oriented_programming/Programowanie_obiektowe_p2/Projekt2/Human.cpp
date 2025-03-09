#ifndef HUMAN_FUN
#define HUMAN_FUN
#include "Human.h"
#include <iostream>

/*ostream& operator<<(ostream &s, Human &h){
    return s << "PASAZER:"
             << "\nimie: " << h.m_name
             << "\nwaga: " << h.m_weight
             << "\nprofesja: " << h.m_proffesion<<endl;
             //<< "\njest na pietrze: " << h.m_hfloor<<endl;
}*/ //do ładnego wypisywania na terminal (niekompatybilne z odczytem z pliku)

ostream& operator<<(ostream &s, Human &h){
    return s << h.m_name << " "
             << h.m_weight << " "
             << h.m_proffesion;
             //<< "\njest na pietrze: " << h.m_hfloor<<endl;
}

istream& operator>>(istream &s, Human &h){
    string bin;
    s >> h.m_name >> h.m_weight >> h.m_proffesion >> bin;
    while(bin!="/")
    {
        h.m_proffesion=h.m_proffesion+" "+bin;
        s >> bin;
    }
    return s;
}

    Human::Human(){
        #ifdef _DEBUG
        cout << "Human()" << endl;
        #endif
        m_hfloor=0;
        m_weight=60;
        m_name="-";
        m_proffesion="-";
    }

    Human::Human(int hfloor, double weight, string name, string proffesion){
        #ifdef _DEBUG
        cout << "Human(double, string, string, string)" << endl;
        #endif
        m_hfloor=hfloor;
        m_weight=weight;
        m_name=name;
        m_proffesion=proffesion;
    }

    Human::Human(double weight, string name, string proffesion){
        #ifdef _DEBUG
        cout << "Human(double, string, string, string)" << endl;
        #endif
        m_hfloor=0;
        m_weight=weight;
        m_name=name;
        m_proffesion=proffesion;
    }

    Human::Human(double weight){
        #ifdef _DEBUG
        cout << "Human(double)" << endl;
        #endif
        m_hfloor=0;
        m_weight=weight;
        m_name="-";
        m_proffesion="-";
    }

    Human::Human(string name){
        #ifdef _DEBUG
        cout << "Human(string)" << endl;
        #endif
        m_hfloor=0;
        m_weight=60;
        m_name=name;
        m_proffesion="-";
    }

    Human::Human(string name, string proffesion){
        #ifdef _DEBUG
        cout << "Human(string,string)" << endl;
        #endif
        m_hfloor=0;
        m_weight=60;
        m_name=name;
        m_proffesion=proffesion;
    }

    Human::Human(const Human &h){
        #ifdef _DEBUG
        cout << "Human(Human &h)"<< endl;
        #endif
        m_weight=h.m_weight;
        m_hfloor=h.m_hfloor;
        m_name=h.m_name;
        m_proffesion=h.m_proffesion;
    }

    void Human::changeFloor(int hfloor)
    {
        m_hfloor=hfloor;
    }

    void Human::changeWeight(double weight)
    {
        m_weight=weight;
    }

    void Human::changeName(string name)
    {
        m_name=name;
    }

    void Human::changeProffesion(string proffesion)
    {
        m_proffesion=proffesion;
    }

    Human::~Human()
    {
        #ifdef _DEBUG
        cout << "~Human()" << endl;
        #endif
    }

#endif
