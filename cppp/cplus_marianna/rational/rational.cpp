/**************************************************************************************
    Author: Marianna Shvartsman
    Creation date : 	2013.10.31     
    Last modified date: 2013.10.31
    Description : rational implementation
***************************************************************************************/
#include <cassert>
#include <iostream>
#include <string>
using namespace std;

#include "../Ainclude/rational.h"


//*****************************************************
//		CTOR
//*****************************************************
Ratio::Ratio	(int _num, int _denom)throw(const char*)
{
	if(0 == _denom)
	{
		throw "Division of zero forbidden\n";
	}
	m_num	= _num;
	m_denom = _denom; 
		
	Reduce();
}

//*****************************************************
//		operator+=
//*****************************************************			
Ratio&	Ratio::operator +=(Ratio _o)
{
	m_denom = m_denom * _o.m_denom;
	m_num	= m_num* _o.m_denom + _o.m_num	* m_denom;
	
	Reduce();
	return *this;
}

//*****************************************************
//		operator-=
//*****************************************************
Ratio&	Ratio::operator -=(Ratio _o)
{
	m_denom = m_denom * _o.m_denom;
	m_num	= m_num * _o.m_denom - _o.m_num	* m_denom;
	
	Reduce();	
	return *this;
}

//*****************************************************
//		operator*=
//*****************************************************
Ratio&	Ratio::operator *=(Ratio _o)
{
	m_num	*= _o.m_num;
	m_denom *= _o.m_denom;

	Reduce();	
	return *this;
}

//*****************************************************
//		operator/=
//*****************************************************
Ratio&	Ratio::operator /=(Ratio _o)throw(const char*)
{
	if(0 == _o.m_num)
	{
		throw	"Division of zero forbidden\n";;
	}
	
	m_num	*=	_o.m_denom;
	m_denom *=	_o.m_num;
	
	Reduce();
	return *this;
}

//*****************************************************
//		Greatest Common Divisor
//*****************************************************
void Ratio::Reduce()
{
	int num = m_num;
	int	denom = m_denom;
	int res; 
	while (denom != 0)
	{
		res = num % denom;
		num = denom;
		denom = res;
	}
	
	m_num /= num;
	m_denom /= num;
	
}	
//*****************************************************
//			operator<<	
//*****************************************************
ostream&	operator<<(ostream& _os, Ratio& _ratio)
{
	return _os << _ratio.GetNumerator() << "/" << _ratio.GetDenomirator();
}
