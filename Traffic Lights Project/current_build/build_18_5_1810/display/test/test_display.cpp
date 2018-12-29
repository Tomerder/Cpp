// display.cpp
//
//	What's this?
//	Author: Vladimir Krapp
//	Created on:
//	Last modified:

#include <CppUTest/TestHarness.h>
#include <CppUTest/CommandLineTestRunner.h>

#include <iostream>
#include "display.h"

using namespace std;

TEST_GROUP(tg)
{
};

TEST(tg, test_name)
{
    Display::SetUp();   
    Display::Demo();
    Display::ShutDown();   
}


int main(int argc, char** argv)
{
	Display::SetUp();  
	Display::DrawRoads();
	getch();
	Display::ShutDown(); 
	
	

   // return CommandLineTestRunner::RunAllTests(argc, argv);
	return 0;
}
