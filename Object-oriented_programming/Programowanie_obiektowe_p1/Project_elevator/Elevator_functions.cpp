#include "elevator.h"
#include <iostream>

int Elevator::m_elevator_count=0;

ostream& operator<<(ostream &s, Elevator &e){ //operator wypisania
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
}

//konstruktory

Elevator::Elevator(){
    #ifdef _DEBUG
    cout << "Elevator()"<< endl;
    #endif
    m_floor=0;
    m_passengers_count=0;
    m_lift_cap=800;
    m_passengers=nullptr;
    //m_building=0;
    m_elevator_count++;
}

Elevator::Elevator(int floor, int passengers_count, double lift_cap, Human *passengers, SkyScraper building){
    #ifdef _DEBUG
    cout << "Elevator(int,int,double,Human,SkyScrapper)"<< endl;
    #endif
    m_floor=floor;
    m_passengers_count=passengers_count;
    m_lift_cap=lift_cap;
    m_passengers=passengers;
    m_building=building;
    m_elevator_count++;
}

Elevator::Elevator(int passengers_count){
    #ifdef _DEBUG
    cout << "Elevator(int)"<< endl;
    #endif
    m_floor=0;
    m_passengers_count=passengers_count;
    m_lift_cap=800;
    m_passengers=new Human[passengers_count];
    //m_building=0;
    m_elevator_count++;
}

Elevator::Elevator(int floor,int passengers_count){
    #ifdef _DEBUG
    cout << "Elevator(int,int)"<< endl;
    #endif
    m_floor=floor;
    m_passengers_count=passengers_count;
    m_lift_cap=800;
    m_passengers= new Human[passengers_count];
    //m_building=0;
    m_elevator_count++;
}

Elevator::Elevator(double lift_cap){
    #ifdef _DEBUG
    cout << "Elevator(double)"<< endl;
    #endif
    m_floor=0;
    m_passengers_count=0;
    m_lift_cap=lift_cap;
    m_passengers=nullptr;
    //m_building=0;
    m_elevator_count++;
}

Elevator::Elevator(Human *passengers,int count){
    #ifdef _DEBUG
    cout << "Elevator(Human)"<< endl;
    #endif
    int add=0;
    Human *temp=passengers;
    m_floor=0;
    m_passengers_count=count;
    m_lift_cap=800;
    m_passengers=passengers;
    //m_building;
    m_elevator_count++;
}

Elevator::Elevator(SkyScraper *building){
    #ifdef _DEBUG
    cout << "Elevator(SkyScrapper)"<< endl;
    #endif
    m_floor=0;
    m_passengers_count=0;
    m_lift_cap=800;
    m_passengers=nullptr;
    m_building=*building;
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
    if (e.m_passengers!= nullptr)
    {
        m_passengers = new Human[m_passengers_count];
        for (int i = 0; i < m_passengers_count; ++i)
            m_passengers[i] = e.m_passengers[i];
    } else
        m_passengers = nullptr;
}
//funckje do zmieniania pól
void Elevator::change(int floor)
{
    m_floor=floor;
}

void Elevator::change(double lift_cap)
{
    m_lift_cap=lift_cap;
}

void Elevator::change(SkyScraper &building)
{
    m_building=building;
}

int Elevator::HowMany()
{
    return m_elevator_count;
}

void Elevator::GetIn(Human *new_pass, int crowd) //grupa pasażerów wsiada do windy
{
    Human *temp= new Human[m_passengers_count+crowd];
    int i=0;
    for(; i<m_passengers_count; i++)
        temp[i]=m_passengers[i];
    int j=0;
    for(; j<crowd; j++,i++)
        temp[i]=new_pass[j];
    delete[] m_passengers;
    m_passengers=temp;
    m_passengers_count=m_passengers_count+crowd;
}

Elevator& Elevator::operator+(Human *new_pass) //pasażer wsiada do windy
{
    if(this->m_floor==new_pass->m_hfloor)
    {
        Human *temp= new Human[m_passengers_count+1];
        int i=0;
        for(; i<m_passengers_count; i++)
            temp[i]=m_passengers[i];
        temp[i]=*new_pass;
        delete[] m_passengers;
        m_passengers=temp;
        m_passengers_count=m_passengers_count+1;
        //if((double) *this>=100)
            //this->Fall();
        return *this;
    }else
    {
        cout << "Nie to pietro" <<endl;
        return *this;
    }
}

Elevator& Elevator::operator-(string name) //pasażer wi=ysiada z windy
{
    int i=0;
    while(name!=this->m_passengers[i].m_name)
    {
            i++;
    }
    if(i==m_passengers_count)
    {
        cout << "Nie ma takiego pasazera" << endl;
    }else
    {
        Human *temp= new Human[m_passengers_count-1];
        int j=0;
        for(; j<i; j++)
            temp[j]=m_passengers[j];

        for(j=i+1; j<m_passengers_count; j++)
            temp[j-1]=m_passengers[j];

        delete[] m_passengers;
        m_passengers=temp;
        m_passengers_count=m_passengers_count-1;
    }
    return *this;
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

Elevator& Elevator::operator--(){ //ostatni pasażer wysiada
    #ifdef _DEBUG
    cout << "--(int)" << endl;
    #endif
    Human *temp= new Human[m_passengers_count-1];
    for(int i=0; i<m_passengers_count-1; i++)
        temp[i]=m_passengers[i];
    delete[] m_passengers;
    m_passengers=temp;
    m_passengers_count=m_passengers_count-1;
    return *this;
}

Elevator& Elevator::operator=(const Elevator &e){
    if(this==&e)
        return *this;
    m_floor=e.m_floor;
    m_passengers_count=e.m_passengers_count;
    m_lift_cap=e.m_lift_cap;
    if(m_passengers)
        delete[] m_passengers;
    if(e.m_passengers)
    {
        m_passengers= new Human[e.m_passengers_count];
        for(int i=0; i<m_passengers_count; i++)
            m_passengers[i]=e.m_passengers[i];
    }else
        m_passengers=nullptr;
    m_building=e.m_building;
    return *this;
}

Elevator::operator double(){ //liczenie procentowego obciążenia windy
    double add=0;
    for(int i=0; i<m_passengers_count; i++)
        add+=m_passengers[i].m_weight;
    return (add/m_lift_cap)*100;
}

Human Elevator::operator[](int i){
    if(i<0 || i>=m_passengers_count)
    {
        cout << "nie ma tylu pasazerow w windzie" << endl;
        return Human();
    }
    return m_passengers[i];
}

Elevator::~Elevator(){ //destruktor
    #ifdef _DEBUG
    cout << "~Elevator()" <<endl;
    #endif
    m_elevator_count--;
    if(m_passengers!=nullptr)
    {
        delete[] m_passengers;
    }
}
