/***************************************************************************
    Author: Stav Ofer
    Creation date:  		2013-10-29    
    Last modified date:		2013-10-29
    Description: 	
****************************************************************************/

#include <iostream>
using namespace std;

class A;
class B;


class A
{
public:
	A(int _one, int _two) { m_one = _one; m_two = _two; };
	operator B();
	int GetA() const { return m_two; }
	void Print() const { cout << "A: " << m_one << ", " << m_two << endl; }
	
private:
	int m_one;
	int m_two;
};
/*######################################################################*/

class B
{
public:
	B(int _b) { m_b = _b; }
	B(A _a);
	int GetB() const { return m_b; }
	void Print() const { cout << "B: " << m_b << endl; }
	
private:
	int m_b;
};
/*######################################################################*/


A:: operator B()
{
	return B(m_one);
}
/*######################################################################*/

B:: B(A _a)
{
	m_b = _a.GetA();
}
/*######################################################################*/


int main()
{
	A a(1,2);
	
	a.Print();
	
	B b = a;
//	B b(a);
	
	b.Print();
	
	return 0;
}

/*######################################################################*/


