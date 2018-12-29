/***************************************************************************
    Author: Stav Ofer
    Creation date:  		2013-11-03    
    Last modified date:		2013-11-05
    Description: 	bank account - implementations
****************************************************************************/

#include <iostream>
using namespace std;

#include "accImpl.h"


// CTOR
AccImpl_t:: AccImpl_t(int _money, int _period)
{
	m_money = _money;
	m_period = _period;
}
//-----------------------------------------------
// DTOR
AccImpl_t:: ~AccImpl_t()
{}
//-----------------------------------------------


// member functions


void AccImpl_t:: Update(char* _txt)
{
	if(_txt)
	{
		cout << _txt << endl;
	}
}
//-----------------------------------------------

void AccImpl_t:: AddMoney(int _money)
{
	m_money += _money;
}
//-----------------------------------------------

int AccImpl_t:: TakeMoney(int _money)
{
	int temp = m_money;
	m_money = (_money >= m_money) ? m_money-_money : 0;
	return (temp - m_money);
}
//-----------------------------------------------

int AccImpl_t:: GetBalance() const
{
	return m_money;
}
//-----------------------------------------------

int AccImpl_t:: GetPeriod() const
{
	return m_period;
}
//-----------------------------------------------

