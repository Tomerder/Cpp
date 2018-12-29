/***************************************************************************
    Author: Stav Ofer
    Creation date:  		2013-10-31    
    Last modified date:		2013-11-03
    Description: 	class Ratio testing
****************************************************************************/

#include <iostream>
using namespace std;

#include "rational.h"


int main()
{
	Ratio a(5,7);
	
	Ratio b;
	
	Ratio c(a+b);
	
	cout << "a = " << a << ", b = " << b << ", c = " << c << endl;
	
//	-- don't pass compilation with current code ---
//	
//	int i = a;
//	
//	c = i;
//	
//	cout << "i = " << i << ", c = " << c << endl;
	
	double d = a*2;
	double e = 2*a;
	
	cout << "d = " << d << ", e = " << e << endl;
	
	Ratio f(8,-3);
	
	Ratio g = a+f;
	Ratio h = a-f;
	Ratio j = a*f;
	Ratio k = a/f;
	
	cout << "g = " << g << ", h = " << h << ", j = " << j << ", k = " << k << endl;
	
	
	return 0;
}
