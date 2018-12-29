/***************************************************************************
    Author: Stav Ofer
    Creation date:  		2013-10-31    
    Last modified date:		2013-10-31
    Description: 	class Ratio declaration
****************************************************************************/

#ifndef __RATIONAL_H__
#define __RATIONAL_H__

class Ratio;

// global arithmetic operators
inline Ratio operator +(Ratio _a, Ratio _b);
inline Ratio operator -(Ratio _a, Ratio _b);
inline Ratio operator *(Ratio _a, Ratio _b);
inline Ratio operator /(Ratio _a, Ratio _b);

// print
std::ostream& operator << (std::ostream& _os, Ratio& _ratio);

/*######################################################################*/	
class Ratio
{
public:
	explicit Ratio(int _num = 0, int _denom = 1); // CTOR - explicit to prevent ambiguous overload
	// using default DTOR, copy, CTOR, operator =
	
	inline operator double();
	
	// arithmetic assignment operators
	inline Ratio& operator +=(Ratio _o);
	inline Ratio& operator -=(Ratio _o);
	inline Ratio& operator *=(Ratio _o);
	inline Ratio& operator /=(Ratio _o);
	
	inline int GetNumerator() const;
	inline int GetDenominator() const;
	
private:
	int	m_num;
	int m_denom;
	
	Ratio& PlusMinus(Ratio _o, bool _plus);	// sevice function
};
/*######################################################################*/	


/*----------------------------------------------------------------------*/	
//						INLINE OPERATORS & FUNCS
/*----------------------------------------------------------------------*/	

inline Ratio:: operator double()
{
	return (double)m_num/m_denom;
}
/*----------------------------------------------------------------------*/	

inline Ratio& Ratio:: operator +=(Ratio _o)
{
	return PlusMinus(_o, true);
}
/*----------------------------------------------------------------------*/	

inline Ratio& Ratio:: operator -=(Ratio _o)
{
	return PlusMinus(_o, false);
}
/*----------------------------------------------------------------------*/	

inline Ratio& Ratio:: operator *=(Ratio _o)
{
	assert(_o.m_denom != 0);
	
	m_num *= _o.m_num;
	m_denom *= _o.m_denom;
	return *this;
}
/*----------------------------------------------------------------------*/	

inline Ratio& Ratio:: operator /=(Ratio _o)
{
	assert(_o.m_num != 0);
	
	m_num *= _o.m_denom;
	m_denom *= _o.m_num;
	return *this;
}
/*----------------------------------------------------------------------*/	


inline int Ratio:: GetNumerator() const
{
	return m_num;
}
/*----------------------------------------------------------------------*/	

inline int Ratio:: GetDenominator() const
{
	return m_denom;
}
/*----------------------------------------------------------------------*/	


/*----------------------------------------------------------------------*/	
//						INLINE GLOBAL OPERATORS
/*----------------------------------------------------------------------*/	

inline Ratio operator +(Ratio _a, Ratio _b)
{
	return _a+=_b;
}
/*----------------------------------------------------------------------*/	

inline Ratio operator -(Ratio _a, Ratio _b)
{
	return _a-=_b;
}
/*----------------------------------------------------------------------*/	

inline Ratio operator *(Ratio _a, Ratio _b)
{
	return _a*=_b;
}
/*----------------------------------------------------------------------*/	

inline Ratio operator /(Ratio _a, Ratio _b)
{
	return _a/=_b;
}
/*----------------------------------------------------------------------*/	


#endif /* __RATIONAL_H__ */
