#include "Room.h"
#include <iostream>

int Room::m_Room_count=0;

/*ostream& operator<<(ostream &s, Room &e){ //operator wypisania
    s << "POKOJ:"
      << "\nliczba okien: " << e.m_window_count
      << "\nstatus okien: ";
      if(e.m_window_clear)
          s << "umyte";
      else
          s << "nieumyte";
      s << "\npokoj jest na pietrze: " << e.m_floor
      << "\nliczba ludzi: " << e.m_passengers_count << "\n";
    for(int i=0; i<e.m_passengers_count; i++)
    {
        s << "\n" << e.m_passengers[i];
    }
      s << "\n" << e.m_building;
    return s;
}*/ //do ładnego wypisywania na terminal (niekompatybilne z odczytem z pliku)

ostream& operator<<(ostream &s, Room &e){ //operator wypisania
    s << e.m_window_count << " "
      << e.m_window_clear << " "
      << e.m_function << " "
      << e.m_floor << " "
      << e.m_passengers_count << " | ";
    for(int i=0; i<e.m_passengers_count; i++)
    {
        s << e.m_passengers[i] << " / ";
    }
      s << " | " << e.m_building;
    return s;
}

istream& operator>>(istream &s, Room &e){ //operator wypisania
    char bin;
    Human temp;
    s >> e.m_window_count >> e.m_window_clear >> e.m_function >> e.m_floor >> e.m_passengers_count >> bin;
    for(int i=0; i<e.m_passengers_count; i++)
    {
        s >> temp;
        e.m_passengers.push_back(temp);
    }
    s >> bin >> e.m_building;
    return s;
}

void Room:: out(ostream &s){
    s << "ROOM" << " "
      << m_window_count << " "
      << m_window_clear << " "
      << m_function << " "
      << m_floor << " "
      << m_passengers_count << " | ";
    for(int i=0; i<m_passengers_count; i++)
    {
        s << m_passengers[i] << " / ";
    }
      s << " | " << m_building;
}

void Room:: in(istream &s){
    char bin;
    Human temp;
    s >> m_window_count >> m_window_clear >> m_function >> m_floor >> m_passengers_count >> bin;
    for(int i=0; i<m_passengers_count; i++)
    {
        s >> temp;
        m_passengers.push_back(temp);
    }
    s >> bin >> m_building;
}

//konstruktory

Room::Room(){
    #ifdef _DEBUG
    cout << "Room()"<< endl;
    #endif
    m_window_count=1;
    m_window_clear=false;
    m_function="Biuro";
    m_Room_count++;
}

Room::Room(int floor, int windows_count, bool clear, string function, vector<Human> passengers, SkyScraper building){
    #ifdef _DEBUG
    cout << "Room(int,int,double,Human,SkyScrapper)"<< endl;
    #endif
    m_floor=floor;
    m_passengers_count=passengers.size();
    m_window_count=windows_count;
    m_window_clear=clear;
    m_function=function;
    m_passengers=passengers;
    m_building=building;
    m_Room_count++;
}

Room::Room(int floor, int windows_count, string function){
    #ifdef _DEBUG
    cout << "Room(int)"<< endl;
    #endif
    m_floor=floor;
    m_passengers_count=0;
    m_window_count=windows_count;
    m_window_clear=false;
    m_function=function;
    m_Room_count++;
}

Room::Room(vector<Human>){
    #ifdef _DEBUG
    cout << "Room(Human)"<< endl;
    #endif
    m_window_count=1;
    m_window_clear=false;
    m_function="Biuro";
    m_Room_count++;
}

Room::Room(SkyScraper *building){
    #ifdef _DEBUG
    cout << "Room(SkyScrapper)"<< endl;
    #endif
    m_window_count=1;
    m_window_clear=false;
    m_function="Biuro";
    m_Room_count++;
}

Room::Room(const Room &e){
    #ifdef _DEBUG
    cout << "Room(Room &e)"<< endl;
    #endif
    m_floor=e.m_floor;
    m_passengers_count=e.m_passengers_count;
    m_window_count=e.m_window_count;
    m_window_clear=e.m_window_clear;
    m_function=e.m_function;
    m_building=e.m_building;
    m_Room_count++;
    m_passengers=e.m_passengers;
}

void Room::changeFunction(string function){
    m_function=function;
}

void Room::changeWindowsCount(int windows_count){
    m_window_count=windows_count;
}

int Room::howMany()
{
    return m_Room_count;
}

Room& Room::operator=(const Room &e){
    if(this==&e)
        return *this;
    m_floor=e.m_floor;
    m_passengers_count=e.m_passengers_count;
    m_window_count=e.m_window_count;
    m_window_clear=e.m_window_clear;
    m_function=e.m_function;
    m_passengers=e.m_passengers;
    m_building=e.m_building;
    return *this;
}

Room::operator double(){ //ile mamy okien
    cout << "Liczba okien w pokoju: ";
    return m_window_count;
}

Room::~Room(){ //destruktor
    #ifdef _DEBUG
    cout << "~Room()" <<endl;
    #endif
    m_Room_count--;
}
