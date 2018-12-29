/**************************************************************************************
    Author: Marianna Shvartsman
    Creation date :      
    Last modified date: 
    Description : WaitableQ
***************************************************************************************/
#include <iostream>
#include <functional>
using namespace std;

#include "waitableq.h"
using namespace multithreading_m7;

bool MyLess(const int& _num1, const int& _num2)
{
	return _num1 < _num2;
}

int main()
{
	WaitableQ<int> q(MyLess);
	
	q.Push(7);
	q.Push(8);
	q.IsEmpty();
	int num;
	q.Pop(&num,0);
	cout << "Num is " << num << endl;
	q.Pop(&num,0);
	cout << "Num is " << num << endl;
	system("pause");
	return 0;
}

