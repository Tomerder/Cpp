/***************************************************************************
    Author: Stav Ofer
    Creation date:  		2013-11-03    
    Last modified date:		2013-11-05
    Description: 	bank account - implementation factory
****************************************************************************/

#include <iostream>

#include "account.h"
#include "accImpl.h"
#include "accPersonalImpl.h"
#include "accFamilyImpl.h"
//#include "accStockImpl.h"
#include "accFactory.h"


AccFactory_t:: AccFactory_t()
{}
//-----------------------------------------------

AccFactory_t:: ~AccFactory_t()
{}
//-----------------------------------------------


AccImpl_t* AccFactory_t:: CreateAcc(int _accType, int _money, int _period)
{
	AccImpl_t* ptrAcc = 0;
	
	switch(_accType)
	{
	case PERSONAL:
		ptrAcc = new AccPersonalImpl_t (_money, _period);
		break;
	
	case FAMILY:
		ptrAcc = new AccFamilyImpl_t (_money, _period);
		break;
		
//	case STOCK:
//		ptrAcc = new AccStockImpl_t (_money, _period);
//		break;
	
	default:
		break;
	}
	return ptrAcc;
}
//-----------------------------------------------

