#ifndef ROOM_H
#define ROOM_H

#include "SpaceForPeople.h"
#include "Human.h"
#include "SkyScraper.h"

class Room: public SpaceForPeople{
public:
    //operacje na plikach
    friend ostream& operator<<(ostream &s, Room &r);
    friend istream& operator>>(istream &s, Room &e);
    void out(ostream &s);
    void in(istream &s);

    //konstruktory
    Room();
    Room(int, int, bool, string, SmartBox<Human>, SkyScraper); //pietro, liczba ludzi, liczba okien,
    Room(int, int, string); //pietro, liczba okien, funkcja pomieszczenia
    Room(SmartBox<Human>);
    Room(SkyScraper *);
    Room(const Room &);

    //funkcje zmiany
    void changeFunction(string);
    void changeWindowsCount(int);

    //funkcje
    int howMany();
    Room& operator=(const Room &e);
    bool operator==(const Room &e);
    operator double();

    //detsruktor
    ~Room();

protected:
    int m_window_count;
    bool m_window_clear;
    string m_function;
    static int m_Room_count;
};

#endif // ROOM_H
