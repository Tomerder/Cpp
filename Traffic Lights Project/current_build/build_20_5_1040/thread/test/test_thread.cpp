// testThread.cpp
//
//
//    Author: Vladimir Krapp
//    Created on: 2014-04-08
//    Last modified:

#include <iostream>
#include <stdexcept>
#include "thread.h"
#include "test_class.h"



#include <cstdlib>
#include <cstdio>

#ifdef WINDOWS 
#include <Windows.h>
#include <memory>
#define Sleep(T) Sleep(T * 1000) // Sleep(T) instructs thread to sleep for T seconds
#elif UNIX
#include <pthread.h>
#include <unistd.h>
#include <tr1/memory>
#include <sys/time.h>
#include <cxxabi.h>
#define Sleep(T) sleep(T) // Sleep(T) instructs thread to sleep for T seconds
using namespace std::tr1;
#endif

using namespace m10;
using namespace m10::run;

using namespace std;
//
void* Dummy(void* _args)
{
    std::cout << "Hi" << '\n';
    return 0;
}

void* DummyLoop(void* _args)
{
//    char c = '1';
//    char e = '\n';
    for (int i = 0; i < 3; ++i)
    {
//        write(1, &c, 1);
//        write(1, &e, 1);
//        c++;
        cout << i << '\n';
//        fprintf(stdout, "%d\n", i);
        Sleep(1);
    }
    return 0;
}

void* DummySleep(void* _args)
{
    Sleep(10);
    return 0;
}

class FuncObj: public Runnable
{

};
//
FunctionWrapper<Dummy> fw(0);
//
int I = 10;
FunctionWrapper<DummyLoop> fwl(&I);

FunctionWrapper<DummySleep> fws(0);

void testJoinableJoins()
{
    Thread th(&fwl, false);
    th.Join();
}

void testDetached()
{
    Thread th(&fwl, true);
}

int testTimedJoinTimeout()
{
    Thread th(&fwl);
    return (th.Join(50));

}

int testTimedJoinZeroTimeout()
{
    Thread th(&fwl);
    return (th.Join(0));

}

void testTimedJoin()
{
    Thread th(&fw);
    th.Join(10);
}

void testCancell()
{
    shared_ptr<Thread> thp(new Thread(&fwl));

#ifdef WINDOWS
    thp->Cancel();
#elif UNIX
	try{
    thp->Cancel();
	}
     catch(abi::__forced_unwind&)
    {
	throw;
    }
#endif
   cout << "Cancelled!!!" << '\n';

    try{
    thp->Join();
    }
    catch(...)
    {
        cout << "Exception trying to join!!!" << '\n';
    }

}


int main()
{

	Thread t(&fw);
	Sleep(1);

    testDetached();

    //testCancell();

	testTimedJoin();
	
	if(testTimedJoinTimeout())
    {
        cout << "Got error from timed join, expected" << '\n';
    }
	 
    if(testTimedJoinZeroTimeout())
    {
        cout << "Got error from timed join, zero timeout, expected" << '\n';
    }

    testJoinableJoins();

    testJoinableJoins();


    cout << "sleeping 5 sec." << endl;
    Sleep(5);
    return 0;
}
