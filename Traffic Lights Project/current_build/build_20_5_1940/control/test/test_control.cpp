// control.cpp
//
//	What's this?
//	Author: Vladimir Krapp
//	Created on:
//	Last modified:

#include <CppUTest/TestHarness.h>
#include <CppUTest/CommandLineTestRunner.h>

#include <iostream>
#include "control.h"

using namespace std;

TEST_GROUP(tg)
{
};

TEST(tg, test_name)
{
    
}


int main(int argc, char** argv)
{
    return CommandLineTestRunner::RunAllTests(argc, argv);
}
