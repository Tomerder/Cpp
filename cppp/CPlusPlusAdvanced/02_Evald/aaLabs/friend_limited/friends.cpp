/***************************************************************************
    Author: Stav Ofer
    Creation date:  		2013-10-26    
    Last modified date:		2013-10-26
    Description: 	make function X.Foo available only to class M, without
    				making M a friend
****************************************************************************/

#include <iostream>

#include "friends.h"

using namespace std;


// doesn't have access to X.Foo()
class K
{
public:
	void SetC(X _x) { m_c=5;}// = _x.Foo( /*FooAc()*/ ); }
	
	void Print() { cout << "K: " << m_c << endl; }
private:
	int m_c;
};


/******* MAIN *******/
int main()
{
	X x;
	x.SetA(4);
	x.Print();
	
	M m;
	m.SetB(x);	// works
	m.Print();
	
	x.SetA(5);
	x.Print();
	m.SetB(x);	// works
	m.Print();
	
	K k;
	k.SetC(x);	// shouldn't work
	k.Print();
	
	int a;
	a = x.Foo();	// shouldn't work
	cout << "a: " << a << endl;
	
	return 0;
}

/*######################################################################*/


