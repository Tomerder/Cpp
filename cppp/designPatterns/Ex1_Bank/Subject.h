// Subject.h
//
//	Subject class for Bank Exercise
//	Author: Vladimir Krapp
//	Created on: 23/3/14
//	Last modified:

#ifndef __SUBJECT_H__
#define __SUBJECT_H__

#include <map>

#include "Common.h"

class Observer;

class Subject {
public:

	virtual ~Subject();

    virtual void Attach(Observer* _observer, const Type& _type);
    virtual void Detach(Observer* _observer);

protected:
	// Using generated: Subject();
	virtual void Notify(const Type& _type) const;
	virtual void NotifyAll() const;

    std::multimap<const Type, Observer*> m_observers;
};



#endif //__SUBJECT_H__
