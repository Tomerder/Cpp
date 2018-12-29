/***************************************************************************
    Author: Stav Ofer
    Creation date:  		2013-00-00    
    Last modified date:		2013-00-00
    Description: 	
****************************************************************************/

#include <string>
#include <iostream>
using namespace std;

#include "Polygon.h"
#include "Max.h"

int main()
{
	int a = 3, b = 4;
	int c = Max<int>(a,b);
	cout << c << endl;
	
	int d = ((int&(*)(int&,int&))(0x8048b5d))(b,a);
	cout << d << endl;
	
	string s1("one");
	string s2("two");
	
	string s3 = Max<string>(s1, s2);
	cout << s3 << endl;
	
//	CRectangle r1;
//	CRectangle r2;
//	r1.set_values(3,5);
//	r2.set_values(2,7);
//	CRectangle r3 = Max<CRectangle>(r1, r2);
	
	return 0;
}

