#ifndef KNOT_H
#define KNOT_H
#include<iostream>
#include <type_traits>

template<class T>
class Knot{
public:
    Knot() {}
    Knot(T czesc) {czesc=m_element;}

    //dostep
    Knot* next() {return m_next;}
    Knot* prev() {return m_prev;}
    T element() {return m_element;}
    ~Knot() {
    if(m_next) m_next->m_prev=m_prev;
    if(m_prev) m_prev->m_next=m_next;
    }
private:
    T m_element;
    Knot* m_next;
    Knot* m_prev;
    template <typename U>
    friend class SmartBox;
};

#endif // KNOT_H
