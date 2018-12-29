/************************************************************************
Complex numbers class. cpp file.
Author: Dan Bar-On.
Creation Date: 12.3.14 
Modified at:
Description:
************************************************************************/
#include "complex.h"
using namespace std;

namespace m10{

/*-------------------------------------------------------------------------------------------*/
Complex::Complex(double _real, double _img)
{
	m_real = _real;
	m_img = _img;
}
/*-------------------------------------------------------------------------------------------*/
Complex::Complex(const Complex& _cr)
{
	m_real = _cr.m_real;
	m_img = _cr.m_img;
}
/*-------------------------------------------------------------------------------------------*/
Complex& Complex::operator= (double _real)
{
	m_real = _real;
	m_img = 0;
	return *this;
}
/*-------------------------------------------------------------------------------------------*/
const Complex& Complex::operator+= (const Complex& _rhs)
{	
	m_real += _rhs.m_real;
	m_img += _rhs.m_img;
	return *this;
}
/*-------------------------------------------------------------------------------------------*/
const Complex& Complex::operator-= (const Complex& _rhs)
{
	m_real -= _rhs.m_real;
	m_img -= _rhs.m_img;
	return *this;
}
/*-------------------------------------------------------------------------------------------*/
const Complex& Complex::operator*= (const Complex& _rhs)
{
	m_real = m_real*_rhs.m_real - m_img*_rhs.m_img;
	m_img  = m_real*_rhs.m_img + m_img*_rhs.m_real;

	return *this;
}
/*-------------------------------------------------------------------------------------------*/
const Complex& Complex::operator/= (const Complex& _rhs)
{
	m_real = (m_real*_rhs.m_real + m_img*_rhs.m_img)/(_rhs.m_real*_rhs.m_real + _rhs.m_img*_rhs.m_img);
	m_img  = (m_img*_rhs.m_real - m_real*_rhs.m_img)/(_rhs.m_real*_rhs.m_real + _rhs.m_img*_rhs.m_img);
	
	return *this;
}
/*-------------------------------------------------------------------------------------------*/	
Complex& Complex::operator++ ()		/*pre increment*/
{
	m_real += 1;
	return *this;
}

Complex Complex::operator++ (int)	/*post increment*/
{
	double formerReal = m_real;
	m_real += 1;
	return Complex(formerReal, m_img);
}

Complex& Complex::operator-- ()		//pre decrement
{
	m_real -= 1;
	return *this;
}

Complex Complex::operator-- (int)	//post decrement
{
	double formerReal = m_real;
	m_real -= 1;
	return Complex(formerReal, m_img);
}
/*-------------------------------------------------------------------------------------------*/	
const Complex operator+ (const Complex& _lhs, const Complex& _rhs)
{
	Complex ret(_lhs);
	return ret += _rhs;
}
const Complex operator- (const Complex& _lhs, const Complex& _rhs)
{
	Complex ret(_lhs);
	return ret -= _rhs;
}
const Complex operator* (const Complex& _lhs, const Complex& _rhs)
{
	Complex ret(_lhs);
	return ret *= _rhs;
}
const Complex operator/ (const Complex& _lhs, const Complex& _rhs)
{
	Complex ret(_lhs);
	return ret /= _rhs;
}
/*-------------------------------------------------------------------------------------------*/	
bool operator== (const Complex& _lhs, const Complex& _rhs)
{
	return _lhs.m_real == _rhs.m_real && _lhs.m_img == _rhs.m_img;
}
/*-------------------------------------------------------------------------------------------*/	
bool operator< 	(const Complex& _lhs, const Complex& _rhs)
{
	return _lhs.Abs() < _rhs.Abs();
}
/*-------------------------------------------------------------------------------------------*/	
bool operator> 	(const Complex& _lhs, const Complex& _rhs)
{
	return _lhs.Abs() > _rhs.Abs();
}
/*-------------------------------------------------------------------------------------------*/	
bool operator<= (const Complex& _lhs, const Complex& _rhs)
{
	return _lhs.Abs() <= _rhs.Abs();
}
/*-------------------------------------------------------------------------------------------*/	
bool operator>= (const Complex& _lhs, const Complex& _rhs)
{
	return _lhs.Abs() >= _rhs.Abs();
}
/*-------------------------------------------------------------------------------------------*/	
ostream& operator<< (ostream& _out, const Complex& _cr)
{
	_out << _cr.m_real << " + " << _cr.m_img << 'i';
	return _out;
}

} // end of namespace m10

