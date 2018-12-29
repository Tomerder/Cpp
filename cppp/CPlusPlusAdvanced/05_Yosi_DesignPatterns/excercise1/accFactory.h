/***************************************************************************
    Author: Stav Ofer
    Creation date:  		2013-11-03    
    Last modified date:		2013-11-05
    Description: 	bank account - implementation factory
****************************************************************************/

#ifndef __ACC_FACTORY_H__
#define __ACC_FACTORY_H__

class AccImpl_t;


class AccFactory_t
{
public:
	static AccImpl_t* CreateAcc(int _accType, int _money, int _period);
	
private:
	~AccFactory_t();
	AccFactory_t();
};


#endif /* __ACC_FACTORY_H__ */
