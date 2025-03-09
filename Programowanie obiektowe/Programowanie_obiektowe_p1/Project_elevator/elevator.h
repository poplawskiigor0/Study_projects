#ifndef ELEVATOR_H
#define ELEVATOR_H

#include "Human.h"
#include "SkyScraper.h"

class Elevator{
public:
    friend ostream& operator<<(ostream &s, Elevator &e);

    Elevator();

    Elevator(int, int, double, Human *, SkyScraper);

    Elevator(int);

    Elevator(int,int);

    Elevator(double);

    Elevator(Human *, int);

    Elevator(SkyScraper *);

    void change(int);

    void change(double);

    void change(SkyScraper&);

    int HowMany();

    void GetIn(Human *, int);

    Elevator& operator+(Human *);

    Elevator& operator-(string name);

    void operator^(int);

    Elevator& operator--();

    Elevator& operator=(const Elevator &e);

    operator double();

    Human operator[](int);

    Elevator(const Elevator &);

    ~Elevator();

//private:
    int m_floor;
    int m_passengers_count;
    double m_lift_cap;
    Human *m_passengers;
    SkyScraper m_building;
    static int m_elevator_count;
};

#endif // ELEVATOR_H
