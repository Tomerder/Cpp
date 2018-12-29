// testSemaphore.cpp
//
//
//    Author: Vladimir Krapp
//    Created on: 2014-04-08
//    Last modified:

#include <iostream>

#include "semaphore_m10.h"
#include "test_class.h"


using namespace std;
//using namespace m10;


class SemTest : public TestCase
{
public:

    void SemThreadCreateDestroy()
    {
        Semaphore s(1);
    }

    void SemProcessCreateDestroy()
    {
        Semaphore s(1, Semaphore::PROCESS);
    }

    void SemUpDown()
    {
        Semaphore s(1);
        s.Down();
        s.Up();
    }

    SemTest():TestCase("Semaphore test")
    {
        SemThreadCreateDestroy();
        SemProcessCreateDestroy();
        SemUpDown();
    }
};



int main()
{
    SemTest run;
    return 0;
}
