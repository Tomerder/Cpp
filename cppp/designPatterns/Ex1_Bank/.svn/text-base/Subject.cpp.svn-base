// Subject.cpp
//
//	Subject class functions
//	Author: Vladimir Krapp
//	Created on: 23/3/14
//	Last modified:

#include <iostream>
#include <utility>
#include <map>

#include "Subject.h"
#include "Observer.h"

using namespace std;

Subject::~Subject()
{
    ;
}


void Subject::Attach(Observer* _observer, const Type& _type)
{
    m_observers.insert(make_pair(_type, _observer));
}

void Subject::Detach(Observer* _observer)
{
    multimap<const Type, Observer*>::iterator itr;
    for(itr = m_observers.begin();
        itr != m_observers.end(); 
        ++itr)
    {
        if((*itr).second == _observer)
        {
            m_observers.erase(itr);
            break;
        }
    }
}

void Subject::Notify(const Type& _type) const
{
    multimap<const Type, Observer*>::const_iterator itr;

    for(itr = m_observers.lower_bound(_type);
        itr != m_observers.upper_bound(_type);
        ++itr)
    {
        (itr->second)->Update(this);
    }
}

void Subject::NotifyAll() const
{
    multimap<const Type, Observer*>::const_iterator itr;

    for(itr = m_observers.begin(); itr != m_observers.end(); ++itr)
    {
        (itr->second)->Update(this);
    }
}
