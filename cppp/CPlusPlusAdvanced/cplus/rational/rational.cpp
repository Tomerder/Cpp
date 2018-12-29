/***************************************************************************
    Author: Stav Ofer
    Creation date:  		2013-10-31    
    Last modified date:		2013-10-31
    Description: 	class Ratio implementation
****************************************************************************/

#include <iostream>
#include <cassert>

#include "rational.h"


// CTOR - def. values are (0,1)
Ratio:: Ratio(int _num, int _denom)
{
	assert(_denom != 0);
	
	m_num = _num;
	m_denom = _denom;
}
/*----------------------------------------------------------------------*/	

// print
std::ostream& operator << (std::ostream& _os, Ratio& _ratio)
{
	return _os << _ratio.GetNumerator() << "/" << _ratio.GetDenominator();
}
/*----------------------------------------------------------------------*/	

// sevice function
Ratio& Ratio:: PlusMinus(Ratio _o, bool _plus)
{
	int sign = (_plus) ? 1 : -1;
	
	assert(_o.m_denom != 0);
	
	m_num *= _o.m_denom;
	m_num += _o.m_num*m_denom*sign;
	m_denom *= _o.m_denom;
	return *this;
}
/*----------------------------------------------------------------------*/	
