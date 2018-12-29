/***************************************************************************
    Author: Stav Ofer
    Creation date:  		2013-11-03    
    Last modified date:		2013-11-05
    Description: 	bank account - bridge to implementations
****************************************************************************/

#ifndef __ACCOUNT_H__
#define __ACCOUNT_H__

#include "observer.h"

class AccImpl_t;
class Subject_t;

// types of accounts
enum AccType
{
	PERSONAL,
	FAMILY,
	STOCK
};


class Account_t : public Observer_t
{
public:
	 ~Account_t();
	 Account_t(int _accType, int _money, int _period, Subject_t* _bnk);
	
	void AddMoney(int _money);
	int TakeMoney(int _money);
	
	int GetBalance() const;
	int GetPeriod() const;
	
	virtual void Update(Subject_t* _bnk, char* _txt = 0);
	
protected:
	AccImpl_t*  m_account;
	
	//Subject_t* m_sbj;	// ptr to subject - inherited
};

#endif /* __ACCOUNT_H__ */
