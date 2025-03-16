#ifndef HUMAN_H
#define HUMAN_H

#include <string>
using namespace std;

struct list;

class Human{
public:
    //strumienie
    friend ostream& operator<<(ostream &s, Human &h);
    friend istream& operator>>(istream &s, Human &h);

    //konstruktory
    Human();
    Human(int, double, string, string);
    Human(double, string, string);
    Human(int);
    Human(double);
    Human(string);
    Human(string, string);
    Human(const Human &);
    bool operator==(const Human &);

    //funkcja
    void changeFloor(int);
    void changeWeight(double);
    void changeName(string);
    void changeProffesion(string);

    //destruktor
    ~Human();

//private:
    double m_weight;
    int m_hfloor;
    string m_name;
    string m_proffesion;
};

#endif // HUMAN_H
