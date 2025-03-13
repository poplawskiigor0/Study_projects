#include "elevator.h"
#include <iostream>

int Elevator::m_elevator_count=0;

/*ostream& operator<<(ostream &s, Elevator &e){ //operator wypisania
    s << "WINDA:"
      << "\nmaskymalny udzwig: " << e.m_lift_cap
      << "\nwinda jest na pietrze: " << e.m_floor
      << "\nliczba ludzi: " << e.m_passengers_count << "\n";
    for(int i=0; i<e.m_passengers_count; i++)
    {
        s << "\n" << e.m_passengers[i];
    }
      s << "\n" << e.m_building;
    return s;
}*/ //do ładnego wypisywania na terminal (niekompatybilne z odczytem z pliku)

ostream& operator<<(ostream &s, Elevator &e){ //operator wypisania
    s << e.m_lift_cap << " "
      << e.m_floor << " "
      << e.m_passengers_count << " | ";
    for(int i=0; i<e.m_passengers_count; i++)
    {
        s << e.m_passengers[i] << " / ";
    }
      s << " | " << e.m_building;
    return s;
}

istream& operator>>(istream &s, Elevator &e){ //operator wpisania
    char bin;
    Human temp;
    s >> e.m_lift_cap >> e.m_floor >> e.m_passengers_count >> bin;
    for(int i=0; i<e.m_passengers_count; i++)
    {
        s >> temp;
        e.m_passengers.addLast(temp);
    }
    s >> bin >> e.m_building;
    return s;
}

void Elevator:: out(ostream &s){
    s //<< "ELEVATOR" << " "
      << m_lift_cap << " "
      << m_floor << " "
      << m_passengers_count << " | ";
    for(int i=0; i<m_passengers_count; i++)
    {
        s << m_passengers[i] << " / ";
    }
      s << " | " << m_building;
}

void Elevator:: in(istream &s){
    char bin;
    Human temp;
    s >> m_lift_cap >> m_floor >> m_passengers_count >> bin;
    for(int i=0; i<m_passengers_count; i++)
    {
        s >> temp;
        m_passengers.addLast(temp);
    }
    s >> bin >> m_building;
}

//konstruktory

Elevator::Elevator(){
    #ifdef _DEBUG
    cout << "Elevator()"<< endl;
    #endif
    m_lift_cap=800;
    m_elevator_count++;
}

Elevator::Elevator(int floor, double lift_cap, SmartBox<Human> passengers, SkyScraper building){
    #ifdef _DEBUG
    cout << "Elevator(int,int,double,Human,SkyScrapper)"<< endl;
    #endif
    m_floor=floor;
    m_passengers_count=passengers.size();
    m_lift_cap=lift_cap;
    m_passengers=passengers;
    m_building=building;
    m_elevator_count++;
}

Elevator::Elevator(int floor){
    #ifdef _DEBUG
    cout << "Elevator(int)"<< endl;
    #endif
    m_lift_cap=800;
    m_elevator_count++;
}

Elevator::Elevator(double lift_cap){
    #ifdef _DEBUG
    cout << "Elevator(double)"<< endl;
    #endif
    m_floor=0;
    m_passengers_count=0;
    m_lift_cap=lift_cap;
    m_elevator_count++;
}

Elevator::Elevator(SmartBox<Human> crowd){
    #ifdef _DEBUG
    cout << "Elevator(Human)"<< endl;
    #endif
    m_lift_cap=800;
    m_elevator_count++;
}

Elevator::Elevator(SkyScraper *building){
    #ifdef _DEBUG
    cout << "Elevator(SkyScrapper)"<< endl;
    #endif
    m_lift_cap=800;
    m_elevator_count++;
}

Elevator::Elevator(const Elevator &e){
    #ifdef _DEBUG
    cout << "Elevator(Elevator &e)"<< endl;
    #endif
    m_floor=e.m_floor;
    m_passengers_count=e.m_passengers_count;
    m_lift_cap=e.m_lift_cap;
    m_building=e.m_building;
    m_elevator_count++;
    m_passengers=e.m_passengers;
}
//funckje do zmieniania pól

void Elevator::changeLiftCap(double lift_cap)
{
    m_lift_cap=lift_cap;
}

int Elevator::howMany()
{
    return m_elevator_count;
}

void Elevator::operator^(int endfloor){ //winda jedzie na piętro
    #ifdef _DEBUG
    cout << "^(int)" << endl;
    #endif
    int mass=0;
    for(int i=0; i<m_passengers_count; i++)
    {
        mass=mass+this->m_passengers[i].m_weight;
    }
    if((endfloor<=20 && endfloor>0) && mass<=800)
    {
        while(m_floor>endfloor)
        {
              m_floor--;
        }
        while(m_floor<endfloor)
        {
              m_floor++;
              for(int i=0; i<m_passengers_count; i++)
              {
                  m_passengers[i].changeFloor(m_floor);
              }
        }
    }
    else if(mass>800)
    {
        cout << "Za duzo ludzi" << endl;
    }else
    {
        cout << "Nie ma takiego pietra" << endl;
    }
}

Elevator& Elevator::operator=(const Elevator &e){
    if(this==&e)
        return *this;
    m_floor=e.m_floor;
    m_passengers_count=e.m_passengers_count;
    m_lift_cap=e.m_lift_cap;
    m_passengers=e.m_passengers;
    m_building=e.m_building;
    return *this;
}

bool Elevator::operator==(const Elevator &e){
    if(this==&e)
        return true;
    if(m_lift_cap==e.m_lift_cap) return true;
    return false;
}

Elevator::operator double(){ //liczenie procentowego obciążenia windy
    double add=0;
    cout << "Obciazenie windy w %: ";
    for(int i=0; i<m_passengers_count; i++)
        add+=m_passengers[i].m_weight;
    return (add/m_lift_cap)*100;
}

Elevator::~Elevator(){ //destruktor
    #ifdef _DEBUG
    cout << "~Elevator()" <<endl;
    #endif
    m_elevator_count--;
}
