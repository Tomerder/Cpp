#include <iostream>
#include <string>

#include "lab.h"

using namespace std;

int lab2(void)
{
	cout << "lab2 int : " << foo<int>(10) << endl;

	cout << "lab2 float : " << foo<float>(20) << endl;

	cout << "lab2 short : " << foo<short>(30) << endl;

	return 0;
} 
