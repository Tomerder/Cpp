/***************************************************************************
    Author: Stav Ofer
    Creation date:  		2013-11-03    
    Last modified date:		2013-11-05
    Description: 	Bank - a singleton, & subject to observers
****************************************************************************/

#include <typeinfo>
#include <vector>
#include <algorithm>
#include <iostream>

#include "subject.h"
#include "observer.h"
#include "bank.h"

#include "account.h"
#include "accPersonalImpl.h"
#include "accFamilyImpl.h"

using namespace std;


void BonusFam500(Observer_t* _obs);

// static data member
Bank_t Bank_t::m_bnk;


//-------------------------------------------------------------------------
// CTOR
Bank_t:: Bank_t()
{}
//-------------------------------------------------------------------------

// get ref. to bank
Bank_t& Bank_t:: GetBank()
{
	return m_bnk;
}
//-------------------------------------------------------------------------

// Notify - only to type passed as _params, unless _params==0
void Bank_t:: Notify(void* _params, char* _txt)
{
	for (size_t i = 0; i < m_observers.size(); i++)
	{
		if( _params && ( typeid(*m_observers[i]).name() == (char*)_params ) )
		{
			m_observers[i]->Update(this, _txt); // call Update func. in observers
		}
	}
}
//-------------------------------------------------------------------------


void Bank_t:: Bonus()
{
	for_each( m_observers.begin(), m_observers.end(), BonusFam500);
	Notify( (void*)(typeid(AccFamilyImpl_t).name()), "500 nis were added to your account");
}
//-------------------------------------------------------------------------

void Bank_t:: CallMeeting()
{
	Notify( (void*)(typeid(AccPersonalImpl_t).name()), "Come to the bank for a meeting");
}
//-------------------------------------------------------------------------


//void Bank_t:: Invest()
//{
//	
//	
//	// Notify
//}
//-------------------------------------------------------------------------


void BonusFam500(Observer_t* _obs)
{
	if( typeid(*_obs) == typeid(AccFamilyImpl_t) )
	{
		(static_cast<Account_t*>(_obs))->AddMoney(500);
	}
}
//-------------------------------------------------------------------------

