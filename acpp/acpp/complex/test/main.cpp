/************************************************************************
Complex numbers class. test file.
Author: Dan Bar-On.
Creation Date: 12.3.14 
Modified at:
Description:
************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>  
#include <string> 

#include "complex.h"

#define EPSILON 0.00001
using namespace std;
using namespace m10;


bool Compare(Complex _c1, Complex _c2)
{
	stringstream str1, str2;
	
	str1 << _c1;
	str2 << _c2;
	return str1.str() == str2.str();
}



int main()
{
	// Unit test
	// Case 1: Ctor, deafault parameters
	Complex c1(1.5, 2.5);
	Complex c2;
	cout << c1 << "  " <<c2 << " Creation test: pass" << endl;

	// Case 2: Check operator==
	Complex c3(1.5, 2.5);
	if (c1 == c3)
	{
		cout << "Check operator== pass" << endl;
	}

	// Case 3: Check copy CTOR
	Complex c4(1.5, 2.5);
	Complex c5(1.5, 2.5);
	if (c4 == c5)
	{
		cout << "copy CTOR test: pass" << endl;
	}

	// Case 4: Check operator+=
	Complex c6(1.5, 2.5);
	Complex c7(1.5, 2.5);	
	Complex c8(3,5);
	c6 += c7;
	
	if (Compare(c6, c8) )
	{
		cout << "operator += test: pass" << endl;
	}

	// Case 5: Check operator+=
	Complex c9(1.5, 3.5);
	Complex c10(5.5, 2.5);	
	Complex c11(-4,1);
	c9 -= c10;
	
	if (Compare(c9, c11) )
	{
		cout << "operator -= test: pass" << endl;
	}

	// Case 6: Check operator*=
	Complex c12(2.5, 3.5);
	Complex c13(2, 1);	
	Complex c14(1.5,8.5);
	c12 *= c13;
	
	if (Compare(c12, c14) )
	{
		cout << "operator *= test: pass" << endl;
	}

	// Case 6: Check operator/=
	Complex c15(2.5, 3.5);
	Complex c16(2, 1);	
	Complex c17(1.7, 1.06);
	c15 /= c16;
	
	if (Compare(c15, c17) )
	{
		cout << "operator /= test: pass" << endl;
	}

	// Case 7: assignment operator
	Complex c18 = 7; 
	Complex c19(7, 0);	
	Complex c20(7,1);
	Complex c21(4, 4);
	c21 = c20;	

	if (Compare(c18, c19) && Compare(c20, c21))
	{
		cout << "operator= test: pass" << endl;
	}




	return 0;
}

/*
	Complex(double _real = 0, double _img = 0);			//CTOR from 2 doubles.

	Complex(const Complex& _cr);						//copy CTOR
	Complex& operator= (double _real);	//Assignment operator(from Complex& - take the compiler generated)

	const Complex& operator+= (const Complex& _rhs);
	const Complex& operator-= (const Complex& _rhs);
	const Complex& operator*= (const Complex& _rhs);
	const Complex& operator/= (const Complex& _rhs);

	friend bool operator== (const Complex& _lhs, const Complex& _rhs);

	size_t Abs() const;
	
	Complex& operator++ ();		
	Complex operator++ (int);	
	
	inline friend ostream& operator<< (ostream& _out, const Complex& _cr);
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


*/
