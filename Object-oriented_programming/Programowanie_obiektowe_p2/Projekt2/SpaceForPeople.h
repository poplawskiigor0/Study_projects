#ifndef SPACEFORPEOPLE_H
#define SPACEFORPEOPLE_H
#include "Human.h"
#include <vector>
#include "SkyScraper.h"

class SpaceForPeople{
public:
    //operacje na plikach
    friend ostream& operator<<(ostream &s, SpaceForPeople &e);
    friend istream& operator>>(istream &s, SpaceForPeople &e);
    virtual void out(ostream &s)=0;
    virtual void in(istream &s)=0;

    //konstruktory
    SpaceForPeople();
    SpaceForPeople(int, vector<Human>, SkyScraper);
    SpaceForPeople(int);
    SpaceForPeople(vector<Human>);
    SpaceForPeople(SkyScraper *);
    SpaceForPeople(const SpaceForPeople &);

    //zmiany
    void changefloor(int);
    void changebuilding(SkyScraper&);

    //dostep do pol
    int floor();
    int passengersCount();
    SkyScraper building();

    //funckje
    virtual int howMany()=0;
    SpaceForPeople& operator+(vector<Human>);
    SpaceForPeople& operator+(Human *);
    SpaceForPeople& operator-(string);
    SpaceForPeople& operator--();
    SpaceForPeople& operator=(const SpaceForPeople &e);
    virtual operator double()=0;
    Human operator[](int);

    //destruktor
    virtual ~SpaceForPeople()=0;

protected:
    int m_floor;
    int m_passengers_count;
    vector<Human> m_passengers;
    SkyScraper m_building;
    static int m_SpaceForPeople_count;
};

#endif // SPACEFORPEOPLE_H

