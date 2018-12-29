/**************************************************************************************
    Author: Marianna Shvartsman
    Creation date :      
    Last modified date: 
    Description : 
***************************************************************************************/
#include <iostream>
using namespace std;

#include "../../Ainclude/rational.h"

int main()
{
	Ratio a(24,36);
	try
	{
		Ratio zero(1,0);
	}
	catch(const char* _s)
	{
		cout << _s;
	}
	
	cout << "a = " << a  << endl;
	Ratio b;
	cout << "b = " << b  << endl;
	Ratio c(a+b);
	cout << "c = " << c << endl;
	int i = 5;
//	int i = a;
//	cout << "i = " << i  << endl;	
	c = i;
	cout << "c = " << c	<<  endl;
//	double d = a*2;
//	cout << "d = " << d	 << endl;
	Ratio temp;
	try
	{
		temp = a/i;
	}
	catch(const char* _s)
	{
		cout << _s;
	}
	
	cout << "a/i = " << temp << endl;
	temp = a-b;
	cout << "a-b = " << temp << endl;
	
	return 0;
}

