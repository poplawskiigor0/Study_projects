#ifndef CLEANINGPLATFORM_H
#define CLEANINGPLATFORM_H

#include "elevator.h"
#include "Human.h"
#include "SkyScraper.h"

class CleaningPlatform: public Elevator{
public:
    //operacje na plikach
    friend ostream& operator<<(ostream &s, CleaningPlatform &e);
    friend istream& operator>>(istream &s, CleaningPlatform &e);
    void out(ostream &s);
    void in(istream &s);

    //konstruktory
    CleaningPlatform();
    CleaningPlatform(int, double, double, SmartBox<Human>, SkyScraper);
    CleaningPlatform(int);
    CleaningPlatform(double);
    CleaningPlatform(SmartBox<Human>);
    CleaningPlatform(SkyScraper *);
    CleaningPlatform(const CleaningPlatform &);

    //zmiany
    void changeStaffWeight(double);

    //funkcje
    int howMany();
    void Clean();
    CleaningPlatform& operator=(const CleaningPlatform &e);
    bool operator==(const CleaningPlatform &e);
    operator double();

    //destruktor
    ~CleaningPlatform();

private:
    double m_staff_weight;
    static int m_CleaningPlatform_count;
};

#endif // CLEANINGPLATFORM_H
