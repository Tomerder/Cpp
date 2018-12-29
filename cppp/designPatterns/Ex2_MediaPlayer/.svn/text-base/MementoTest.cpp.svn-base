// Memento.h
//
//	Base classes for implementing the Memento Design Pattern
//	Author: Vladimir Krapp
//	Created on: 24/3/14
//	Last modified:

#ifndef __MEMENTO_H__
#define __MEMENTO_H__

#include <iostream>
#include <vector>

using namespace std;

class Originator;

class Memento
{
    friend class Originator;

    public:
        virtual ~Memento(){;};
    private:
        explicit Memento(int _s):m_state(_s){;};
        int m_state;
};

class Originator
{
    public:

       int GetState(){return m_state;}
       void SetState(int _s){m_state = _s;}

       virtual Memento* GetMemento(){return new Memento(m_state++);} 
       virtual void RestoreState(const Memento* _mem){m_state = _mem->m_state;} 

       int m_state;
};

class Logger // Caretaker
{
    void PushMemento(Memento* _mem);
    Memento* PopMemento();

    private:
        std::vector<Memento*> m_log;
};

int main()
{

    return 0;
}




#endif //__MEMENTO_H__
