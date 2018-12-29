/***************************************************************************
    Author: Stav Ofer
    Creation date:  		2013-11-05    
    Last modified date:		2013-11-05
    Description: 	family account
****************************************************************************/

#include <vector>

#include "bank.h"
#include "accImpl.h"
#include "accFamilyImpl.h"

// CTOR
AccFamilyImpl_t:: AccFamilyImpl_t(int _money, int _period) :
	AccImpl_t(_money, _period)
{}


// get updates from bank (virtual)
void AccFamilyImpl_t:: Update(char* _txt)
{
	AccImpl_t:: Update(_txt);
}
//-------------------------------------------------------------------------

