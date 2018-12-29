/**************************************************************************************
    Author: Marianna Shvartsman
    Creation date :      2013.10.31
    Last modified date: 2013.10.31
    Description : Ratio declaration
***************************************************************************************/
#ifndef __RATIO_H__
#define __RATIO_H__
#include <iostream>

class Ratio;
std::ostream&	operator<<(std::ostream& _os, Ratio& _ratio);

	inline	Ratio	operator +(Ratio _r1, Ratio _r2);
	inline	Ratio	operator -(Ratio _r1, Ratio _r2);
	inline	Ratio	operator *(Ratio _r1, Ratio _r2);
	inline	Ratio	operator /(Ratio _r1, Ratio _r2)throw(const char*);

class Ratio
{
public:
	
			Ratio	(int _num = 0, int _denom = 1)throw(const char*);
			
	//		genereted cctor & operator=
	
	Ratio&	operator +=(Ratio _o);
	Ratio&	operator -=(Ratio _o);
	Ratio&	operator *=(Ratio _o);
	Ratio&	operator /=(Ratio _o)throw(const char*);
	
//	inline	operator	double();
	inline	double		GetRatio()const;
	inline 	int			GetNumerator()const;
	inline	int			GetDenomirator()const;
	
private:
	int	m_num;
	int	m_denom;
	
	void Reduce();
};


//inline	Ratio::operator double()
//{
//	return m_num/m_denom;
//}


//*******************************************************
//	implementation of inline NOT- mem function 
//*******************************************************
inline	Ratio	operator +(Ratio _r1, Ratio _r2)
{
	return _r1 += _r2;
}

inline	Ratio	operator -(Ratio _r1, Ratio _r2)
{
	return _r1 -= _r2;
}
inline	Ratio	operator *(Ratio _r1, Ratio _r2)
{
	return _r1 *= _r2;
}
inline	Ratio	operator /(Ratio _r1, Ratio _r2)throw(const char*)
{
	return _r1 /= _r2;
}


//*******************************************************
//	implementation of inline mem-functions
//*******************************************************
inline	double		Ratio::GetRatio()const
{
	return m_num/m_denom;
}

inline int	Ratio::GetNumerator()const
{
	return m_num;
}
inline int	Ratio::GetDenomirator()const
{
	return m_denom;
}

#endif 
