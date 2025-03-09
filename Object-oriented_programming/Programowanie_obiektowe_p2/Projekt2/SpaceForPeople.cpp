#include "SpaceForPeople.h"
#include <iostream>

int SpaceForPeople::m_SpaceForPeople_count=0;

ostream& operator<<(ostream &s, SpaceForPeople &e){ //operator wypisania
    e.out(s);
    return s;
}

istream& operator>>(istream &s, SpaceForPeople &e){ //operator wpisania
    e.in(s);
    return s;
}

SpaceForPeople::SpaceForPeople(){
    #ifdef _DEBUG
    cout << "SpaceForPeople()"<< endl;
    #endif
    m_floor=0;
    m_passengers_count=m_passengers.size();
    m_SpaceForPeople_count++;
}

SpaceForPeople::SpaceForPeople(int floor, vector<Human> passengers, SkyScraper building){
    #ifdef _DEBUG
    cout << "SpaceForPeople(int,int,double,Human,SkyScrapper)"<< endl;
    #endif
    m_floor=floor;
    m_passengers_count=passengers.size();
    m_passengers=passengers;
    m_building=building;
    m_SpaceForPeople_count++;
}

SpaceForPeople::SpaceForPeople(int floor){
    #ifdef _DEBUG
    cout << "SpaceForPeople(int)"<< endl;
    #endif
    m_floor=floor;
    m_passengers_count=m_passengers.size();
    m_SpaceForPeople_count++;
}

SpaceForPeople::SpaceForPeople(vector<Human> passengers){
    #ifdef _DEBUG
    cout << "SpaceForPeople(Human)"<< endl;
    #endif
    m_floor=0;
    m_passengers_count=passengers.size();
    m_passengers=passengers;
    m_SpaceForPeople_count++;
}

SpaceForPeople::SpaceForPeople(SkyScraper *building){
    #ifdef _DEBUG
    cout << "SpaceForPeople(SkyScrapper)"<< endl;
    #endif
    m_floor=0;
    m_passengers_count=m_passengers.size();
    m_building=*building;
    m_SpaceForPeople_count++;
}

SpaceForPeople::SpaceForPeople(const SpaceForPeople &e){
    #ifdef _DEBUG
    cout << "SpaceForPeople(SpaceForPeople &e)"<< endl;
    #endif
    m_floor=e.m_floor;
    m_passengers_count=e.m_passengers_count;
    m_building=e.m_building;
    m_SpaceForPeople_count++;
    m_passengers=e.m_passengers;
}
//funckje do zmieniania pól
void SpaceForPeople::changefloor(int floor)
{
    m_floor=floor;
}

void SpaceForPeople::changebuilding(SkyScraper &building)
{
    m_building=building;
}

int SpaceForPeople::howMany()
{
    return m_SpaceForPeople_count;
}

int SpaceForPeople::floor()
{
    return m_floor;
}

int SpaceForPeople::passengersCount()
{
    return m_passengers_count;
}

SkyScraper SpaceForPeople::building()
{
    return m_building;
}

/*SpaceForPeople& SpaceForPeople::operator+(vector<Human> crowd) //grupa pasażerów wsiada
{
    m_passengers=crowd;
    m_passengers_count=crowd.size();
    return *this;
}*/

SpaceForPeople& SpaceForPeople::operator+(Human *new_pass) //pasażer wsiada
{
    m_passengers.push_back(*new_pass);
    m_passengers_count=m_passengers.size();
    return *this;
}

SpaceForPeople& SpaceForPeople::operator-(string name) //pasażer wysiada
{
    vector<Human>::iterator it_passengers;
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
        it_passengers=m_passengers.begin()+i;
        m_passengers.erase(it_passengers);
    }
    m_passengers_count=m_passengers.size();
    return *this;
}

SpaceForPeople& SpaceForPeople::operator--(){ //ostatni pasażer wysiada
    #ifdef _DEBUG
    cout << "--(int)" << endl;
    #endif
    m_passengers.pop_back();
    m_passengers_count=m_passengers.size();
    return *this;
}

SpaceForPeople& SpaceForPeople::operator=(const SpaceForPeople &e){
    if(this==&e)
        return *this;
    m_floor=e.m_floor;
    m_passengers_count=e.m_passengers_count;
    m_passengers=e.m_passengers;
    m_building=e.m_building;
    return *this;
}

Human SpaceForPeople::operator[](int i){
    if(i<0 || i>=m_passengers_count)
    {
        cout << "nie ma tylu pasazerow w windzie" << endl;
        return Human();
    }
    return m_passengers[i];
}

SpaceForPeople::~SpaceForPeople(){ //destruktor
    #ifdef _DEBUG
    cout << "~SpaceForPeople()" <<endl;
    #endif
    m_SpaceForPeople_count--;
    /*if(m_passengers!=nullptr)
    {
        delete[] m_passengers;
    }*/
}
