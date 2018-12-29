/***************************************************************************
    Author: Stav Ofer
    Creation date:  		2013-00-00    
    Last modified date:		2013-00-00
    Description: 	
****************************************************************************/

//#include <cstdio>
#include <exception>      // std::set_terminate
#include <cstdlib>        // std::abort
#include <iostream>
using namespace std;


int foo()
{
	throw "thrown";
}


void myTerm()
{
	cout << "terminated" << endl;
	abort();
}

void myExit()
{
	cout << "exited" << endl;
}

int main()
{
	set_terminate(myTerm);	
	atexit(myExit);
	
	foo();
	
//	try {
//		foo();
//	}
//	catch(const char* ex) {
//		cout << ex << endl;
//	}
//	
	return 0;
}

