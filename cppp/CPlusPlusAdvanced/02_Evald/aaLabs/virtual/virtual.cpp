/***************************************************************************
    Author: Stav Ofer
    Creation date:  		2013-10-23    
    Last modified date:		2013-10-23
    Description: 	
****************************************************************************/

//#include <stdio.h>
#include <iostream>
using namespace std;


class X
{
public:
	X() { /*m_a = 0; m_b = 0;*/ }
	virtual ~X() {};
	
	void setA(int _a)	{ m_a = _a; }
	void setB(int _b)	{ m_b = _b; }
	
	virtual void print()	{ cout << "a = " << m_a << ", b = " << m_b << endl; }
	
protected:
	int m_a;
	int m_b;
};



class Y: public X
{
public:
	Y() { /*m_c = 0;*/ }
	
	void setC(int _c)	{ m_c = _c; }
	
	void print()	{ cout << "a = " << m_a << ", b = " << m_b << ", c = " << m_c << endl; }
	
// inherited:	setA
//				setB	
	
private:
	int m_c;
};
/*######################################################################*/





Y y;
X& x = y;
X* px = &y;




int main()
{	
	
	y.setA(2);
	x.setB(3);
//	y.setC(4);
	
//	X  dx = static_cast<X>(y);
	X dx = (X)y;
	
	y.print();
	x.print();
	px->print();
	dx.print();
	
	return 0;
}

/*######################################################################*/


