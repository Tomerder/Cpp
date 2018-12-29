/**************************************************************************************
    Author: Marianna Shvartsman
    Creation date :      2013-11-23
    Last modified date: 2013-11-23
    Description : threadPoolBarbaricTest
***************************************************************************************/
#include <iostream>
#ifdef __LINUX
#include <unistd.h>
#endif
#include "threadpool.h"
using namespace multithreading_m7;


void Sleepfunc(size_t _timeout)
{
#ifdef __LINUX
	sleep(_timeout);
#else
	Sleep(_timeout);
#endif
}


class Test1 : public Task 
{
	virtual void	Do(){ cout << "Test 1" << endl;}
};

class Test2 : public Task 
{
	virtual void	Do(){ cout << "Test 2" << endl;}
};

class Test3 : public Task 
{
	virtual void	Do(){ Sleepfunc(2); cout << "Test 3" << endl;}
};


class Test4 : public Task 
{
	virtual void	Do(){ cout << "Test 4" << endl;}
};

class Test5 : public Task 
{
	virtual void	Do(){ Sleepfunc(3); cout << "Test 5" << endl;}
};

class Test6 : public Task 
{
	virtual void	Do(){ cout << "Test 6" << endl;}
};


int main()
{
	ThreadPool pool(1);
//	ThreadPool::Priority level = ThreadPool::Priority.HIGH;
	
	
	shared_ptr<Task> test1(new Test1);
	pool.Add(test1,ThreadPool::LOW);

	shared_ptr<Task> test2(new Test2);
	pool.Add(test2,ThreadPool::LOW);
	
//	pool.ChangeNumThreads(4);

//	sleep(5);		
	shared_ptr<Task> test3(new Test3);
	pool.Add(test3,ThreadPool::LOW);
	
	shared_ptr<Task> test4(new Test4);
	pool.Add(test4,ThreadPool::MEDIUM);
	
	shared_ptr<Task> test5(new Test5);
	pool.Add(test5,ThreadPool::HIGH);

	Sleepfunc(5);
	
	cout << " Num of threads ends gracefully is " << pool.Stop(1000,true) << endl;
	
	Sleepfunc(5);	
//	shared_ptr<Task> test6(new Test6);
//	pool.Add(test6,ThreadPool::MEDIUM);
//	
//	sleep(2);
//	
//	pool.ChangeNumThreads(2);
//	

	system("pause");
	
	return 0;
}

