// state_machine.cpp
//
//	What's this?
//	Author: Vladimir Krapp
//	Created on:
//	Last modified:

#include <CppUTest/TestHarness.h>
#include <CppUTest/CommandLineTestRunner.h>

#include <iostream>
#include "state_machine.h"

using namespace std;

TEST_GROUP(tg)
{
};

TEST(tg, test_name)
{
   	StateMatrix stateM(2,3);
	
	stateM.TickHappened();

	cout << stateM.GetCurrentState() << endl;

	stateM.ReportEvent(1);

	cout << stateM.GetCurrentState() << endl;

 
}


int main(int argc, char** argv)
{
    return CommandLineTestRunner::RunAllTests(argc, argv);
}
