/***************************************************************************
    Author: Stav Ofer
    Creation date:  		2013-11-03    
    Last modified date:		2013-11-05
    Description: 	bank account - implementations
****************************************************************************/

#ifndef __ACC_IMPL_H__
#define __ACC_IMPL_H__

class Subject_t;

class AccImpl_t
{
public:
	AccImpl_t(int _money, int _period);
	virtual ~AccImpl_t();
	
			void AddMoney(int _money);
	virtual int TakeMoney(int _money);
	
			int GetBalance() const;
			int GetPeriod() const;
	
	virtual void Update(char* _txt = 0);
	
protected:
	int m_money;
	int m_period;	// years
};


#endif /* __ACC_IMPL_H__ */
