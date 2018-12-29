/***************************************************************************
    Author: Stav Ofer
    Creation date:  		2013-11-03    
    Last modified date:		2013-11-05
    Description: 	personal account
****************************************************************************/

#ifndef __ACC_PERSONAL_IMPL_H__
#define __ACC_PERSONAL_IMPL_H__

#include "accImpl.h"


class AccPersonalImpl_t : public AccImpl_t
{
public:
	AccPersonalImpl_t(int _money, int _period);

	virtual void Update(char* _txt);
	
	// inherited	
//			void AddMoney(int _money);
//	virtual int TakeMoney(int _money);
//	
//			int GetBalance() const;
//			int GetPeriod() const;
	
protected:
	
	// inherited
	
//	int m_money;
//	int m_period;	// years
};


#endif /* __ACC_PERSONAL_IMPL_H__ */
