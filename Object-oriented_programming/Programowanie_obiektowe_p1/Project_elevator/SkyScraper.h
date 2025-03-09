#ifndef SKYSCRAPER_H
#define SKYSCRAPER_H

#include <string>
using namespace std;

class SkyScraper{
public:
    friend ostream& operator<<(ostream &s, SkyScraper &e);

    SkyScraper();

    SkyScraper(int);

    SkyScraper(string);

    SkyScraper(int, string);

    SkyScraper(const SkyScraper &);

    ~SkyScraper();

//private:
    int m_floors=20;
    string m_adress="WTC"; //name "WTC" to get easter egg <3
};

#endif // SKYSCRAPER_H
