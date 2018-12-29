/**************************************************************************************
    Author: Marianna Shvartsman
    Creation date : 2013-11-20       
    Last modified date: 2013-11-20 
    Description : class Thread test
***************************************************************************************/
#include <iostream>
using namespace std;


#include "thread.h"
using namespace multithreading_m7;
typedef void(*F)(void);

void Test()
{
	static int count = 0;
	cout << "Test thread " << ++count << endl;
}

int main()
{
	Thread<F> thr1(Test);
	Thread<F> thr2(Test);
	
	thr1.Wait(1000);
	thr2.Wait(1000);

	system("pause");
	return 0;
}


