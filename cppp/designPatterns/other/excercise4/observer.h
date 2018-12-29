/***************************************************************************
    Author: Stav Ofer
    Creation date:  		2013-11-03    
    Last modified date:		2013-11-10
    Description: 	observers - ABC
****************************************************************************/

#ifndef __OBSERVER_H__
#define __OBSERVER_H__

#include <vector>

class Subject_t;

// OBSERVER
class Observer_t
{
public:
	virtual	~Observer_t() {}
	
    virtual void Update(Subject_t* _sbj, char* _txt = 0) = 0; // UPDATE function - (pure) virtual
    
protected:
	Observer_t() {}
	
	std::vector<Subject_t*> m_sbj;	// vector of subjects

};

#endif  /* __OBSERVER_H__ */
