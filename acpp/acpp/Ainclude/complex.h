/************************************************************************
Complex numbers class. h file.
Author: Dan Bar-On.
Creation Date: 12.3.14 
Modified at:
Description:
************************************************************************/
#ifndef __Complex_H__
#define __Complex_H__

#include <stdlib.h>
#include <iostream> 
#include <cmath> 

using namespace std;

namespace m10{

class Complex {
public:
	Complex(double _real = 0, double _img = 0);			//CTOR from 2 doubles.

	Complex(const Complex& _cr);						//copy CTOR
	Complex& operator= (double _real);	//Assignment operator(from Complex& - take the compiler generated)

	const Complex& operator+= (const Complex& _rhs);
	const Complex& operator-= (const Complex& _rhs);
	const Complex& operator*= (const Complex& _rhs);
	const Complex& operator/= (const Complex& _rhs);

	friend bool operator== (const Complex& _lhs, const Complex& _rhs);

	inline size_t Abs() const;
	
	Complex& operator++ ();		//pre increment
	Complex operator++ (int);	//post increment
	Complex& operator-- ();		//pre decrement
	Complex operator-- (int);	//post decrement
	
	friend ostream& operator<< (ostream& _out, const Complex& _cr);
private:
	double m_real, m_img;

};

const Complex operator+ (const Complex& _lhs, const Complex& _rhs);
const Complex operator- (const Complex& _lhs, const Complex& _rhs);
const Complex operator* (const Complex& _lhs, const Complex& _rhs);
const Complex operator/ (const Complex& _lhs, const Complex& _rhs);

bool operator< 	(const Complex& _lhs, const Complex& _rhs);
bool operator> 	(const Complex& _lhs, const Complex& _rhs);
bool operator<= (const Complex& _lhs, const Complex& _rhs);
bool operator>= (const Complex& _lhs, const Complex& _rhs);

/*-------------------------------------------------------------------------------------------*/	
inline size_t Complex::Abs() const
{
	return sqrt(m_real*m_real + m_img*m_img);
}
/*-------------------------------------------------------------------------------------------*/	


} // end of namespace m10
#endif	// #ifndef __Complex_H__

