#ifndef HUMAN_H
#define HUMAN_H

#include <string>
using namespace std;

struct list;

class Human{
public:
    friend ostream& operator<<(ostream &s, Human &h);

    Human();

    Human(int, double, string, string);

    Human(int);

    Human(double);

    Human(string);

    Human(string, string);

    Human(const Human &);

    ~Human();

//private:
    double m_weight;
    int m_hfloor;
    string m_name;
    string m_proffesion;
};

#endif // HUMAN_H
