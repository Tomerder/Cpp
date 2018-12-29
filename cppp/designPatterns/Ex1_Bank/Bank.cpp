// Bank.cpp
//
//	Implementation of the Bank API
//	Author: Vladimir Krapp
//	Created on: 23/3/14
//	Last modified:

#include <iostream>
#include <algorithm>

#include "Bank.h"

using namespace std;
 
Bank Bank::m_bank;


Bank::~Bank()
{;}


Bank::Bank()
{;}


Bank& Bank::getBank() 
{
    return m_bank;
}


Account* Bank::CreateAccount(Type _type)
{
    Account* acc = Account::Create(_type, this);

    if(!acc)
    {
        return 0;
    }

    m_accounts.insert(acc);

    return acc;
}

void Bank::DeleteAccount(Account* _acc)
{
    set<Account*>::iterator itr = m_accounts.find(_acc);

    if(itr == m_accounts.end())
    {
        cout << "No such account" << endl;
        return;
    }


    Account::Destroy(_acc);
}

void Bank::OpSavings()
{
    Notify(TYPE_SAVING);
}

void Bank::OpFamily()
{
    Notify(TYPE_FAMILY);
}

void Bank::OpStock()
{
    Notify(TYPE_STOCK);
}
