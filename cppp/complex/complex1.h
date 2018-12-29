/**************************************************************************************
    Author : Tomer Dery
    Creation date :      12.3.14
    Date last modified : 12.3.14
    Description : complex.h 
***************************************************************************************/
#ifndef __COMPLEX_H__
#define __COMPLEX_H__

#include <iostream>

/*--------------------------------------------------------------------------------*/

namespace ComplexNamespace{

using namespace std;

class Complex{

private: 
	double m_real;
	double m_img;	

public: 	
	Complex(double _real = 0, double _img = 0) : m_real(_real) , m_img(_img) {}   
	
	double GetReal() const  { return m_real; }
	double GetImg() const   { return m_img; }
	
	double Abs() const;
	
	const Complex& operator+=(const Complex& _comp);
	const Complex& operator-=(const Complex& _comp);
	const Complex& operator*=(const Complex& _comp);
	const Complex& operator/=(const Complex& _comp);
	
	const Complex& operator++();/*++comp*/
	Complex operator++(int);  	/*comp++*/
	
	const Complex& operator--();/*--comp*/
	Complex operator--(int);  	/*comp--*/
	
	bool IsEqual(const Complex& _comp) const;
};

/*non-member non-friend functions*/
Complex operator+(const Complex& _comp1, const Complex& _comp2);
Complex operator-(const Complex& _comp1, const Complex& _comp2);
Complex operator*(const Complex& _comp1, const Complex& _comp2);
Complex operator/(const Complex& _comp1, const Complex& _comp2);

bool operator==(const Complex& _comp1, const Complex& _comp2);
bool operator>=(const Complex& _comp1, const Complex& _comp2);
bool operator<=(const Complex& _comp1, const Complex& _comp2);
bool operator>(const Complex& _comp1, const Complex& _comp2);
bool operator<(const Complex& _comp1, const Complex& _comp2);


ostream& operator<< (ostream& stream, const Complex& _comp);
		
}   /* closing namespace Complex */
	
	
#endif /*__COMPLEX_H__*/


