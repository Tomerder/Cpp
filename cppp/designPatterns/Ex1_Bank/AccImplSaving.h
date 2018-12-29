// AccImplSaving.h
//
//	Savings accout class
//	Author: Vladimir Krapp
//	Created on: 23/3/14
//	Last modified:

#ifndef __SAVING_ACCOUNT_IMPL_H__
#define __SAVING_ACCOUNT_IMPL_H__

#include "AccountImpl.h"

class AccImplSaving : public AccountImpl
{
    friend class AccountImpl;

    public:
        virtual void UpdateImpl();

    private:
        AccImplSaving();
        ~AccImplSaving();   
};

#endif //__SAVING_ACCOUNT_IMPL_H__
