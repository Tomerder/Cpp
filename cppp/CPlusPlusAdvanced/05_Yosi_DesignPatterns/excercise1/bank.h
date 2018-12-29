/***************************************************************************
    Author: Stav Ofer
    Creation date:  		2013-11-03    
    Last modified date:		2013-11-05
    Description: 	Bank - a singleton, & subject to observers
****************************************************************************/

#ifndef __BANK_H__
#define __BANK_H__


#include "subject.h"


class Bank_t : public Subject_t
{
public:
	
	// CTOR is private
	// no copy
	// use generated DTOR
	
	static Bank_t& GetBank();
	
	void Bonus();
	void CallMeeting();
//	void Invest();
	
	// inherited
	
//	virtual void Attach(Observer_t*);	// func for observers to call
//	virtual void Detach(Observer_t*);
    
private:
	static Bank_t m_bnk; 		// "actual" bank
//	static size_t m_investments = 0;
	
	void Notify(void* _params, char* _txt = 0);
	
	// inherited
//	vector<Observer_t*> m_observers; // list of observers (who called Attach)
	
	
	Bank_t();					// PRIVATE!
	Bank_t(const Bank_t&);		// no copy 
	void operator=(Bank_t&);	// no assignment	
};


#endif  /* __BANK_H__ */
