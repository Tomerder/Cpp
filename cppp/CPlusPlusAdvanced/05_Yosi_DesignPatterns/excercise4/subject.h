/***************************************************************************
    Author: Stav Ofer
    Creation date:  		2013-11-03    
    Last modified date:		2013-11-05
    Description: 	subject to observers - ABC
****************************************************************************/

#ifndef __SUBJECT_H__
#define __SUBJECT_H__

class Observer_t;

// SUBJECT
class Subject_t
{
public:
	virtual ~Subject_t() {}

    virtual void Attach(Observer_t*);	// func for observers to call
    virtual void Detach(Observer_t*);

protected:
	Subject_t() {}
	virtual void Notify(void* _params, char* _txt=0);	// NOTIFY
	
    std::vector<Observer_t*> m_observers; // list of observers (who called Attach)
};

#endif  /* __SUBJECT_H__ */
