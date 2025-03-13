#ifndef SMARTBOX_H
#define SMARTBOX_H
#include<string>
#include <fstream>
#include <type_traits>
#include <typeinfo>
#include <sstream>
#include "Knot.h"

template<class T>
class SmartBox{
public:
    //konstruktory
    SmartBox(){}

    //indeks
    T& operator[](int number)
    {
        Knot<T>* temp;
        temp=m_head;
        for(int i=0; i<number; i++) temp=temp->m_next;
        return temp->m_element;
    };

    //romziar
    int size()
    {
        return m_lenght;
    };

    //dodawanie
    void addLast(T add)
    {
        m_lenght++;
        if(!m_head)
        {
            m_head=newpart();
            m_head->m_element=add;
            m_tail=m_head;
        }else
        {
            m_tail->m_next=newpart();
            m_tail->m_next->m_prev=m_tail;
            m_tail=m_tail->m_next;
            m_tail->m_element=add;
        }
    };

    //usuwanie
    void deletePart(int number)
    {
        if(number==m_lenght && m_lenght==1)
        {
            deleteOnly();
            return;
        }
        if(number==m_lenght)
        {
            deleteLast();
            return;
        }
        if(number==1)
        {
            deleteFirst();
            return;
        }
        m_lenght--;
        Knot<T> *temp;
        temp=m_head;
        for(int i=1; i<number; i++) temp=temp->m_next;
        delete temp;
    };

    //usun jedyny
    void deleteOnly()
    {
        Knot<T>* temp;
        temp=m_tail;
        m_tail=m_tail->m_prev;
        m_head=m_head->next();
        m_lenght--;
        delete temp;
    }

    //usun ostatni
    void deleteLast()
    {
        Knot<T>* temp;
        temp=m_tail;
        m_tail=m_tail->m_prev;
        m_lenght--;
        delete temp;
    }

    //usun pierwszy
    void deleteFirst()
    {
        Knot<T>* temp;
        temp=m_head;
        m_head=m_head->m_next;
        m_lenght--;
        delete temp;
    }

    //zmiana elementow
    void switchParts(int n1, int n2)
    {
        Knot<T> *p1, *p2;
        p1=m_head;
        p2=m_head;
        T temp;
        for(int i=1; i<n1; i++) p1=p1->m_next;
        for(int i=1; i<n2; i++) p2=p2->m_next;
        temp=p1->m_element;
        p1->m_element=p2->m_element;
        p2->m_element=temp;
    };

    //nowy czlon
    Knot<T>* newpart()
    {
        Knot<T> *ptr = new Knot<T>;
        ptr->m_next=nullptr;
        ptr->m_prev=nullptr;
        return ptr;
    };

    //przypisanie
    SmartBox& operator=(const SmartBox& sb)
    {
        Knot<T> *temp;
        m_lenght=sb.m_lenght;
        if(sb.m_lenght==0)
        {
            this->clear();
            return *this;
        }
        if(m_lenght==0)
        {
            m_head=nullptr;
            m_tail=nullptr;
        }else
        {
            m_head=newpart();
            m_tail=m_head;
            temp=sb.m_head;
            m_head->m_element=sb.m_head->m_element;
            for(int i=1; i<m_lenght; i++)
                {
                    m_tail->m_next= newpart();
                    m_tail->m_next->m_prev=m_tail;
                    m_tail=m_tail->m_next;
                    temp=temp->m_next;
                    m_tail->m_element=temp->m_element;
                }
        }
        return *this;
    }

    //porownanie
    bool operator==(const SmartBox& sb)
    {
        Knot<T> *tmp1, *tmp2;
        T temp;
        tmp1=m_head;
        tmp2=sb.m_head;
        if(m_lenght!=sb.m_lenght) return false;
        for(int i=0; i<m_lenght; i++)
        {
            if(tmp1->m_element!=tmp2->m_element) return false;
            tmp1=tmp1->m_next;
            tmp2=tmp2->m_next;
        }
        return true;
    }

    void show()
    {
        std:: cout << "KONTENER:" << std::endl;
        if(size()==0) std::cout << "Nie ma zadnych obiektow" <<std::endl;
        for(int i=0; i<size(); i++)
        {
            if constexpr (std::is_pointer<T>::value) std::cout << *((*this)[i])<<std::endl;
            else std::cout << (*this)[i]<< std::endl;
        }
    }

    //zapis
    void save()
    {
        std::ofstream file1;
        std::string name1;
        std::cout << "Nazwij plik" <<std::endl;
        std::cin >> name1;
        file1.open(name1+".txt");
        for(int i=0; i<m_lenght; i++)
        {
            if constexpr (std::is_pointer<T>::value) file1 << *((*this)[i]) <<std::endl;
            else file1 << ((*this)[i]) <<std::endl;
        }
        file1.close();
    }

    void saveabstract()
    {
        std::ofstream file1;
        std::string name1;
        std::cout << "Nazwij plik" <<std::endl;
        std::cin >> name1;
        file1.open(name1+".txt");
        for(int i=0; i<m_lenght; i++)
        {
            file1 << typeid(*(*this)[i]).name() << " " << *(*this)[i] << std::endl;
        }
        file1.close();
    }

    //wyczysc
    void clear()
    {
        Knot<T> *temp;
        while(m_head)
        {
            temp=m_head;
            m_head=m_head->m_next;
            delete temp;
        }
        m_lenght=0;
    }

    //odczyt
    template<typename U>
    void get()
    {
        std::string line;
        std::ifstream file2;
        std::string name2 , check="";
        std::cout << "Z ktorego pliku odczytac?" << std::endl;
        std::cin >> name2;
        file2.open(name2+".txt");
        try{
        if(file2.fail())
        {
            throw "Blad otwierania pliku";
        }else this->clear();
        Knot<T>* temp2;
        while (std::getline(file2, line))
        {
            std::istringstream iss(line);
            T temp;
            if constexpr (std::is_pointer<T>::value){
                temp = new U;
                this->addLast(temp);
            }else{
                this->addLast(temp);
            }
            if (m_lenght == 1){
                temp2 = m_head;
            }else
            {
                temp2 = temp2->m_next;
            }
            if constexpr (std::is_pointer<T>::value){
                iss >> *temp2->m_element;
            }else
            {
                iss >> temp2->m_element;
            }
        }
        }catch(const char* s)
        {
            std::cout << s << std::endl;
            file2.clear();
        }

        file2.close();
    }

    //doczyt abstrakcyjna
    template<typename A, typename B, typename C>
    void getabstract()
    {
        A *nelev;
        B *ncp;
        C *nroom;
        std::ifstream file2;
        std::string name2, check;
        int next=0;
        std::cout << "Z ktorego pliku odczytac?" << std::endl;
        std::cin >> name2;
        file2.open(name2+".txt");
        try{
        if(file2.fail()) throw "Blad otwierania pliku";
        this->clear();
        while(!file2.eof())
        {
            check="";
            file2 >> check;
            if(check=="8Elevator")
            {
                nelev=new A;
                this->addLast(nelev);
                file2 >> *((*this)[next]);
                next++;
            }else if(check=="16CleaningPlatform")
            {
                ncp= new B;
                this->addLast(ncp);
                file2 >> *((*this)[next]);
                next++;
            }else if(check=="4Room")
            {
                nroom=new C;
                this->addLast(nroom);
                file2 >> *((*this)[next]);
                next++;
            }else if(check=="")
            {
                continue;
            }else{
                getline(file2,check);
            }
        }
        }catch(const char* s)
        {
            std::cout << s <<std::endl;
            file2.clear();
        }
        file2.close();

    }


    //dodanie kontenerow
    SmartBox operator+(const SmartBox& sb)
    {
        SmartBox newsb;
        Knot<T>* temp1=this->m_head;
        Knot<T>* temp2=sb.m_head;
        while(temp1)
        {
            newsb.addLast(temp1->m_element);
            temp1=temp1->m_next;
        }
        while(temp2)
        {
            newsb.addLast(temp2->m_element);
            temp2=temp2->m_next;
        }
        return newsb;
    }

    //destruktory
    ~SmartBox()
    {
        Knot<T> *temp;
        while(m_head)
        {
            temp=m_head;
            m_head=m_head->m_next;
            delete temp;
        }
    };
private:
    Knot<T>* m_head=nullptr;
    Knot<T>* m_tail=nullptr;
    int m_lenght=0;
};

#endif // SMARTBOX_H
