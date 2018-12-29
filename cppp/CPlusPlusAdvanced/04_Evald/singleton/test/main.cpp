/***************************************************************************
    Author: Stav Ofer
    Creation date:  		2013-11-14    
    Last modified date:		2013-11-14
    Description: 	test for singleton template
****************************************************************************/

#include <iostream>

#include "singleton.h"
using namespace std;
using namespace m7;

// test class for singleton
class X
{
public:
	// using generated DTOR
	
	int GetData() const { return m_data; }
	void SetData(int _num) { m_data = _num; }
	
private:
	int m_data;
	
	X() : m_data(0) {}	// private CTOR
	
	// no copy
	X(const X&);
	X& operator=(const X&);
	
	friend class Singleton<X>; // can call CTOR
};


//=======================================================================//
//								MAIN
//=======================================================================//
int main()
{
	X& obj1 = Singleton<X>::Instance();
	cout << obj1.GetData() << endl;
	
	obj1.SetData(1);
	cout << obj1.GetData() << endl;
	
	X& obj2 = Singleton<X>::Instance();
	cout << obj2.GetData() << endl;
	
	obj2.SetData(2);
	cout << obj1.GetData() << endl;
	
	return 0;
}
//=======================================================================//

