// Memento.h
//
//	Base classes for implementing the Memento Design Pattern
//	Author: Vladimir Krapp
//	Created on: 24/3/14
//	Last modified:

#ifndef __MEMENTO_H__
#define __MEMENTO_H__
#include <vector>


class Originator;

struct MementoState
{};

class Memento
{
    public:
        virtual ~Memento(){};
 
    protected:
        Memento(){};

    private: 
        // This should be repeated in every derived Originator/Memento 
        // pair, as friendship is not inherited
        friend class Originator;


//    private:
//        State* m_state;
};


class Originator // Abstract Interface
{
    public:
       virtual ~Originator() = 0;

       
       // Originator has "Memento factory" methods - mementos are specific 
       // to a class and can't be constructed directly without it.
       virtual Memento* GetMemento() = 0;
       virtual bool     RestoreState(const Memento* _mem) = 0;

};


class Logger // Caretaker
{
    public:
        virtual ~Logger() = 0;

        virtual bool StoreMemento(Memento* _mem) = 0;
        virtual Memento* RetrieveMemento() = 0;

    private:
        std::vector<Memento*> m_mementos;
};

#endif //__MEMENTO_H__
