/***************************************************************************
    Author: Stav Ofer
    Creation date:  		2013-11-05    
    Last modified date:		2013-11-05
    Description: 	family account
****************************************************************************/

#ifndef __ACC_FAMILY_IMPL_H__
#define __ACC_FAMILY_IMPL_H__

#include "accImpl.h"

class AccFamilyImpl_t : public AccImpl_t
{
public:
	AccFamilyImpl_t(int _money, int _period);

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


#endif /* __ACC_FAMILY_IMPL_H__ */
