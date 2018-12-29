#include <iostream>
#include <string>

#include "lab.h"

using namespace std;

/*specialize*/
template<>
int foo<int>(int a)
{
	return a+5;
}

int lab1(void)
{

	cout << "lab1 int : " << foo<int>(10) << endl;

	cout << "lab1 float : " << foo<float>(20) << endl;

	cout << "lab1 short : " << foo<short>(30) << endl;

	return 0;
} 
