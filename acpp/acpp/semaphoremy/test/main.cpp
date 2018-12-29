#include <iostream>
#include "semaphoremy.h"

using namespace std;

int main ()
{
	Semaphore sem;

	sem.Up();
	cout << "up test\n";
	
	sem.Down();
	cout << "down test\n";

	return 0;
}


