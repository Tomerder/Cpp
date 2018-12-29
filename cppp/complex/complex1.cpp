/**************************************************************************************
    Author : Tomer Dery
    Creation date :      12.3.14
    Date last modified : 12.3.14
    Description : complex.h 
***************************************************************************************/
#include <cmath>

#include "complex1.h"

using namespace std;

namespace ComplexNamespace{

/*--------------------------------------------------------------------------------*/

#define DEBUG true

#define PRINT_D(MSG)  if (DEBUG) cout << MSG << endl;

/*--------------------------------------------------------------------------------*/

double Complex::Abs() const
{
	return ( sqrt ( (m_real * m_real)  + (m_img * m_img)   )  );
}

/*--------------------------------------------------------------------------------*/

const Complex& Complex::operator+=(const Complex& _comp)
{
	m_real += _comp.m_real;
	m_img += _comp.m_img;
	
	return *this;
}


/*non-member non-friend function  =>   implement + using +=    */
Complex operator+(const Complex& _comp1, const Complex& _comp2)
{
	Complex compToRet(_comp1);
	
	compToRet += _comp2;

	return compToRet;
}

/*--------------------------------------------------------------------------------*/

const Complex& Complex::operator-=(const Complex& _comp)
{
	m_real -= _comp.m_real;
	m_img -= _comp.m_img;
	
	return *this;
}


/*non-member non-friend function  =>   implement - using -=    */
Complex operator-(const Complex& _comp1, const Complex& _comp2)
{
	Complex compToRet(_comp1);
	
	compToRet -= _comp2;

	return compToRet;
}

/*--------------------------------------------------------------------------------*/

/*(a+bi) (c+di) = (ac-bd) + (bc+ad)i.*/
const Complex& Complex::operator*=(const Complex& _comp)
{
	m_real = (m_real * _comp.m_real) - (m_img * _comp.m_img) ;
	m_img = (m_img * _comp.m_real) + (m_real * _comp.m_img);
	
	return *this;
}


/*non-member non-friend function  =>   implement * using *=    */
Complex operator*(const Complex& _comp1, const Complex& _comp2)
{
	Complex compToRet(_comp1);
	
	compToRet *= _comp2;

	return compToRet;
}

/*--------------------------------------------------------------------------------*/

/* real = (ac + bd) / (c*c + d*d)   ,   img = (bc - ad) / (c*c + d*d)   */     
const Complex& Complex::operator/=(const Complex& _comp)
{
	double sumOfSqueres =  ( m_img * m_img ) + ( _comp.m_img * _comp.m_img );

	m_real = ((m_real * _comp.m_real) + (m_img * _comp.m_img))  / sumOfSqueres;
	m_img = ((m_img * _comp.m_real) - (m_real * _comp.m_img))  / sumOfSqueres;
	
	return *this;
}


/*non-member non-friend function  =>   implement / using /=    */
Complex operator/(const Complex& _comp1, const Complex& _comp2)
{
	Complex compToRet(_comp1);
	
	compToRet /= _comp2;

	return compToRet;
}

/*--------------------------------------------------------------------------------*/

const Complex& Complex::operator++()
{
	++m_real;
	return *this;
}

Complex Complex::operator++(int)  /*post*/
{
	Complex compToRet(*this);
	
	++m_real;
	
	return compToRet;
}

const Complex& Complex::operator--()
{
	--m_real;
	return *this;
}

Complex Complex::operator--(int)  /*post*/
{
	Complex compToRet(*this);
	
	--m_real;
	
	return compToRet;
}

/*--------------------------------------------------------------------------------*/

bool Complex::IsEqual(const Complex& _comp) const
{
	return ( m_real == _comp.m_real )  &&  ( m_img == _comp.m_img  );
}

/*--------------------------------------------------------------------------------*/

/*non-member non-friend function*/
bool operator==(const Complex& _comp1, const Complex& _comp2)
{
	return ( _comp1.IsEqual(_comp2)  )  ;
}

/*non-member non-friend function*/
bool operator>=(const Complex& _comp1, const Complex& _comp2)
{
	return ( _comp1.Abs() >= _comp2.Abs() ); 
}

/*non-member non-friend function*/
bool operator<=(const Complex& _comp1, const Complex& _comp2)
{
	return ( _comp1.Abs() <= _comp2.Abs() ); 
}

/*non-member non-friend function*/
bool operator>(const Complex& _comp1, const Complex& _comp2)
{
	return ( _comp1.Abs() > _comp2.Abs() ); 
}

/*non-member non-friend function*/
bool operator<(const Complex& _comp1, const Complex& _comp2)
{
	return ( _comp1.Abs() < _comp2.Abs() ); 
}


/*--------------------------------------------------------------------------------*/
/*non-member non-friend function*/
ostream& operator<< (ostream& _os, const Complex& _comp)
{
	_os << _comp.GetReal() << " + " << _comp.GetImg() << "i";
	return _os;
}

/*--------------------------------------------------------------------------------*/

}    /* closing namespace Complex1 */

