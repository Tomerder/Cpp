#include <iostream>
#include <string>

#include "globaliniter.h"
#include "globals.h"

using namespace std;

class X
{
	public:
	X():b(4){}

	int b;
};


int main()
{	
	g_int1 = 3;
	
	cout << "I am g_int1: " << g_int1 << endl;

	return 0;
}



