/***************************************************************************
    Author: Stav Ofer
    Creation date:  		2013-00-00    
    Last modified date:		2013-00-00
    Description: 	
****************************************************************************/

#include <cstdio>
#include <iostream>
using namespace std;


void foo(int i)
{
	cout << i << endl;
}


int main()
{
	foo(3);
	printf("foo: %p\n", (void*)&foo);
	
	((int(*)(int))(0x804869c))(10);
	
	return 0;
}

