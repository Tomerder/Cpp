// Observer.h
//
//	Observer for Bank exercise
//	Author: Vladimir Krapp
//	Created on: 23/3/14
//	Last modified:

#ifndef __OBSERVER_H__
#define __OBSERVER_H__


class Subject;

class Observer {
public:
	virtual			~Observer();
    virtual void	Update(const Subject* ChngSubject) = 0;
protected:
	Observer();
    
	Subject* m_sbj;

private:
    Observer(const Observer&);              // No copy!
    Observer& operator=(const Observer&);   // No copy!
};




#endif //__OBSERVER_H__
