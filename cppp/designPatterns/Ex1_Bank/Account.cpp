// Account.cpp
//
//	Account functions implementation
//	Author: Vladimir Krapp
//	Created on: 23/3/14
//	Last modified:

#include <iostream>

#include "Account.h"
#include "Subject.h"

using namespace std;

int Account::s_idNext = 0;

Account* Account::Create(const Type& _type, Subject* _bank)
{
    AccountImpl* impl = AccountImpl::Create(_type);
    if(!impl)
    {
        return 0;
    }
    Account* acc = new Account(_type, _bank);
    acc->m_impl = impl;
    return acc;
}

void Account::Destroy(Account* _acc)
{
    if (_acc && _acc->m_impl)
    {
        delete _acc;
    }
}

Account::Account(const Type& _type, Subject* _bank)
    :Observer(),  m_id(s_idNext), m_type(_type)
{
    ++s_idNext;
    m_sbj = _bank;
    m_sbj->Attach(this, _type);
}

Account::~Account()
{
    m_sbj->Detach(this);
    AccountImpl::Destroy(m_impl);

    m_impl = 0;
}

void Account::Update(const Subject* _bank)
{
    if(_bank == m_sbj)
    {
        cout << "Notified account:" << this << ", Action: ";
        m_impl->UpdateImpl();
        cout << endl;
    } 
}


ostream& operator<<(ostream& _os, Account* _acc)
{
    return _os << "Account Type: " << _acc->m_type << ", ID: " << _acc->m_id;
}
