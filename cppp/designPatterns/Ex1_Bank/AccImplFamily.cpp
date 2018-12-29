// AccImplFamily.cpp
//
//	AccImplFamily class functions
//	Author: Vladimir Krapp
//	Created on: 23/3/14
//	Last modified:

#include <iostream>

#include "AccImplFamily.h"

using namespace std;

AccImplFamily::AccImplFamily()
    :AccountImpl()
{
    ;
}

AccImplFamily::~AccImplFamily() 
{
    ;
}  

void AccImplFamily::UpdateImpl()
{
    cout << "Congratulations, you got 500 moneyz!";
}
