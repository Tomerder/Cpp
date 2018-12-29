/***************************************************************************
    Author: Stav Ofer
    Creation date:  		2013-11-03    
    Last modified date:		2013-11-05
    Description: 	bank account - bridge to implementations
****************************************************************************/

#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

#include "observer.h"
#include "subject.h"
#include "account.h"
#include "accImpl.h"
#include "accFactory.h"

// DTOR
Account_t:: ~Account_t() 
{
	delete m_account;		// delete implementation created by Factory
	m_account=0;
}
//-----------------------------------------------

// CTOR - using factory
Account_t:: Account_t(int _accType, int _money, int _period, Subject_t* _bnk)
{
	m_account = AccFactory_t::CreateAcc(_accType, _money, _period);
	
	m_sbj = static_cast<Subject_t*>(_bnk);
	m_sbj->Attach(this);	
}
//-----------------------------------------------



// member functions - redirections to implementation

// get updates from bank (virtual)
void Account_t:: Update(Subject_t* _bnk, char* _txt)
{
	if( m_sbj == _bnk )
	{
		m_account->Update(_txt);
	}
}
//-----------------------------------------------

void Account_t:: AddMoney(int _money)
{
	return m_account->AddMoney(_money);
}
//-----------------------------------------------
int Account_t:: TakeMoney(int _money)
{
	return m_account->TakeMoney(_money);
}
//-----------------------------------------------
int Account_t:: GetBalance() const
{
	return m_account->GetBalance();
}
//-----------------------------------------------
int Account_t:: GetPeriod() const
{
	return m_account->GetPeriod();
}
//-----------------------------------------------
