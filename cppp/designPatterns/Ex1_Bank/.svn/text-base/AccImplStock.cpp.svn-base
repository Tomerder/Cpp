// AccImplStock.cpp
//
//	AccImplStock class functions
//	Author: Vladimir Krapp
//	Created on: 23/3/14
//	Last modified:

#include <iostream>

#include "AccImplStock.h"

using namespace std;

bool AccImplStock::s_nextActOnUpdate = 1;

AccImplStock::AccImplStock()
    :AccountImpl()
{
    m_actOnUpdate = s_nextActOnUpdate;
    s_nextActOnUpdate = !s_nextActOnUpdate;
}

AccImplStock::~AccImplStock() 
{
    ;
}  

void AccImplStock::UpdateImpl()
{
    if(m_actOnUpdate)
    {
       cout << "Bank invested in stock account";
    }
}
