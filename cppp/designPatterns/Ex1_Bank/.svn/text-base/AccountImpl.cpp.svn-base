// AccountImpl.cpp
//
//	Account Implementation functions 
//	Author: Vladimir Krapp
//	Created on: 23/3/14
//	Last modified:

#include "AccountImpl.h"

#include "AccImplSaving.h"
#include "AccImplFamily.h"
#include "AccImplStock.h"

AccountImpl::AccountImpl()
{;} 

AccountImpl::~AccountImpl()
{;} 

AccountImpl* AccountImpl::Create(const Type& _type)
{
    AccountImpl* acc = 0;

    if(_type == TYPE_SAVING)
    {
        acc = new AccImplSaving();
    }
    else if(_type == TYPE_FAMILY)
    {
        acc = new AccImplFamily();
    }
    else if(_type == TYPE_STOCK)
    {
        acc = new AccImplStock();
    }

    return acc;
}

void AccountImpl::Destroy(AccountImpl* _acc)
{
    delete _acc;
}






