/***************************************************************************
    Author: Stav Ofer
    Creation date:  		2013-00-00    
    Last modified date:		2013-00-00
    Description: 	
****************************************************************************/

#include <cstdio>
#include <iostream>
using namespace std;


namespace one
{
	int a;
	float b;
};

namespace two
{
	int b;
	float a;
};


int main()
{
//	one::a=1;
//	two::a = 2;
	
	using namespace one;
	using namespace two;
	
	a = 1;
	
	cout << one::a << " " << two::a << endl;
	
	return 0;
}

