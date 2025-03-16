#include "CleaningPlatform.h"
#include <iostream>

int CleaningPlatform::m_CleaningPlatform_count=0;

/*ostream& operator<<(ostream &s, CleaningPlatform &e){ //operator wypisania
    s << "PLATFORMA:"
      << "\nmaskymalny udzwig: " << e.m_lift_cap
      << "\nciezar wody i sprzetu: " << e.m_staff_weight
      << "\nwinda jest na pietrze: " << e.m_floor
      << "\nliczba ludzi: " << e.m_passengers_count << "\n";
    for(int i=0; i<e.m_passengers_count; i++)
    {
        s << "\n" << e.m_passengers[i];
    }
      s << "\n" << e.m_building;
    return s;
}*/ //do ładnego wypisywania na terminal (niekompatybilne z odczytem z pliku)

ostream& operator<<(ostream &s, CleaningPlatform &e){ //operator wypisania
    s << e.m_lift_cap << " "
      << e.m_staff_weight << " "
      << e.m_floor << " "
      << e.m_passengers_count << " | ";
    for(int i=0; i<e.m_passengers_count; i++)
    {
        s << e.m_passengers[i] << " / ";
    }
      s << " | " << e.m_building;
    return s;
}

istream& operator>>(istream &s, CleaningPlatform &e){ //operator wpisania
    char bin;
    Human temp;
    s >> e.m_lift_cap >> e.m_staff_weight >> e.m_floor >> e.m_passengers_count >> bin;
    for(int i=0; i<e.m_passengers_count; i++)
    {
        s >> temp;
        e.m_passengers.push_back(temp);
    }
    s >> bin >> e.m_building;
    return s;
}

void CleaningPlatform:: out(ostream &s){
    s << "CLEANINGPLATFORM" << " "
      << m_lift_cap << " "
      << m_staff_weight << " "
      << m_floor << " "
      << m_passengers_count << " | ";
    for(int i=0; i<m_passengers_count; i++)
    {
        s << m_passengers[i] << " / ";
    }
      s << " | " << m_building;
}

void CleaningPlatform:: in(istream &s){
    char bin;
    Human temp;
    s >> m_lift_cap >> m_staff_weight >> m_floor >> m_passengers_count >> bin;
    for(int i=0; i<m_passengers_count; i++)
    {
        s >> temp;
        m_passengers.push_back(temp);
    }
    s >> bin >> m_building;
}

//konstruktory

CleaningPlatform::CleaningPlatform(){
    #ifdef _DEBUG
    cout << "CleaningPlatform()"<< endl;
    #endif
    m_lift_cap=500;
    m_staff_weight=100;
    m_passengers_count=0;
    m_CleaningPlatform_count++;
}

CleaningPlatform::CleaningPlatform(int floor, double lift_cap, double staff_weight, vector<Human> passengers, SkyScraper building){
    #ifdef _DEBUG
    cout << "CleaningPlatform(int,int,double,Human,SkyScrapper)"<< endl;
    #endif
    m_floor=floor;
    m_passengers_count=passengers.size();
    m_lift_cap=lift_cap;
    m_staff_weight=staff_weight;
    m_passengers=passengers;
    m_building=building;
    m_CleaningPlatform_count++;
}

CleaningPlatform::CleaningPlatform(int floor){
    #ifdef _DEBUG
    cout << "CleaningPlatform(int)"<< endl;
    #endif
    m_lift_cap=500;
    m_staff_weight=100;
    m_CleaningPlatform_count++;
}

CleaningPlatform::CleaningPlatform(double staff_weight){
    #ifdef _DEBUG
    cout << "CleaningPlatform(double)"<< endl;
    #endif
    m_floor=0;
    m_passengers_count=0;
    m_lift_cap=500;
    m_staff_weight=staff_weight;
    m_CleaningPlatform_count++;
}

CleaningPlatform::CleaningPlatform(vector<Human>){
    #ifdef _DEBUG
    cout << "CleaningPlatform(Human)"<< endl;
    #endif
    m_lift_cap=500;
    m_staff_weight=100;
    m_CleaningPlatform_count++;
}

CleaningPlatform::CleaningPlatform(SkyScraper *building){
    #ifdef _DEBUG
    cout << "CleaningPlatform(SkyScrapper)"<< endl;
    #endif
    m_lift_cap=500;
    m_staff_weight=100;
    m_CleaningPlatform_count++;
}

CleaningPlatform::CleaningPlatform(const CleaningPlatform &e){
    #ifdef _DEBUG
    cout << "CleaningPlatform(CleaningPlatform &e)"<< endl;
    #endif
    m_floor=e.m_floor;
    m_passengers_count=e.m_passengers_count;
    m_lift_cap=e.m_lift_cap;
    m_staff_weight=e.m_staff_weight;
    m_building=e.m_building;
    m_CleaningPlatform_count++;
    m_passengers=e.m_passengers;
}
//funckje do zmieniania pól

void CleaningPlatform::changeStaffWeight(double staff_weight)
{
    m_staff_weight=staff_weight;
}

//liczenie obiektów
int CleaningPlatform::howMany()
{
    return m_CleaningPlatform_count;
}

CleaningPlatform& CleaningPlatform::operator=(const CleaningPlatform &e){
    if(this==&e)
        return *this;
    m_floor=e.m_floor;
    m_passengers_count=e.m_passengers_count;
    m_lift_cap=e.m_lift_cap;
    m_staff_weight=e.m_staff_weight;
    m_passengers=e.m_passengers;
    m_building=e.m_building;
    return *this;
}

CleaningPlatform::operator double(){ //liczenie procentowego obciążenia windy
    double add=0;
    cout << "Obciazenie platformy w %: ";
    for(int i=0; i<m_passengers_count; i++)
        add+=m_passengers[i].m_weight;
    add=add+m_staff_weight;
    return (add/m_lift_cap)*100;
}

CleaningPlatform::~CleaningPlatform(){ //destruktor
    #ifdef _DEBUG
    cout << "~CleaningPlatform()" <<endl;
    #endif
    m_CleaningPlatform_count--;
}
