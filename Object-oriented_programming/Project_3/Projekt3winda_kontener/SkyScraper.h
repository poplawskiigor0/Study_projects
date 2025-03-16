#ifndef SKYSCRAPER_H
#define SKYSCRAPER_H

#include <string>
using namespace std;

class SkyScraper{
public:
    //strumienie
    friend ostream& operator<<(ostream &s, SkyScraper &e);
    friend istream& operator>>(istream &s, SkyScraper &e);

    //konstruktory
    SkyScraper();
    SkyScraper(int);
    SkyScraper(string);
    SkyScraper(int, string);
    SkyScraper(const SkyScraper &);

    //dostep
    int floors();
    bool operator==(const SkyScraper& sc);

    //destruktor
    ~SkyScraper();

private:
    int m_floors=20;
    string m_adress;
};

#endif // SKYSCRAPER_H
