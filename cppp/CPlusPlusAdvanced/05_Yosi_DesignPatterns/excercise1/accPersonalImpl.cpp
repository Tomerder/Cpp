/***************************************************************************
    Author: Stav Ofer
    Creation date:  		2013-11-03    
    Last modified date:		2013-11-05
    Description: 	personal account
****************************************************************************/

#include <vector>

#include "bank.h"
#include "accImpl.h"
#include "accPersonalImpl.h"

// CTOR
AccPersonalImpl_t:: AccPersonalImpl_t(int _money, int _period) :
	AccImpl_t(_money, _period)
{}


// get updates from bank (virtual)
void AccPersonalImpl_t:: Update(char* _txt)
{
	 AccImpl_t:: Update(_txt);
}
//-------------------------------------------------------------------------

