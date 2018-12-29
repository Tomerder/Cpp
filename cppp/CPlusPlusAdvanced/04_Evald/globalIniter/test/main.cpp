/***************************************************************************
	Author: Stav Ofer
	Creation date:  		2013-11-14
	Last modified date:		2013-11-15
	Description: 	global initializer test.
					The global variable g_x is declared in global.h and defined
					in global.cpp				
***************************************************************************/

#include <iostream>

#include "globalIniter.h"
#include "global.h"
#include "x.h"

using namespace std;
using namespace m7;

// set g_x's data to _n
void Foo(int _n)
{
	g_x.SetData(_n);
}


int main()
{
	cout << g_x.GetData() << endl;
	
	g_x.SetData(1);
	cout << g_x.GetData() << endl;
	
	Foo(5);
	cout << g_x.GetData() << endl;
	
	return 0;
}



