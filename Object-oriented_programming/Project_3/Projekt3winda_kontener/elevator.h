#ifndef ELEVATOR_H
#define ELEVATOR_H

#include "SpaceForPeople.h"
#include "Human.h"
#include "SkyScraper.h"

class Elevator: public SpaceForPeople{
public:
    //operacje na plikach
    friend ostream& operator<<(ostream &s, Elevator &e);
    friend istream& operator>>(istream &s, Elevator &e); 
    void out(ostream &s);
    void in(istream &s);

    //konstruktory
    Elevator();
    Elevator(int, double, SmartBox<Human>, SkyScraper);
    Elevator(int);
    Elevator(double);
    Elevator(SmartBox<Human>);
    Elevator(SkyScraper *);
    Elevator(const Elevator &);

    //zmiany
    void changeLiftCap(double);

    //funkcje klasy
    int howMany();
    void operator^(int);
    Elevator& operator=(const Elevator &e);
    bool operator==(const Elevator &e);
    operator double();

    //destruktor
    ~Elevator();

protected:
    double m_lift_cap;
private:
    static int m_elevator_count;
};

#endif // ELEVATOR_H
