// AccImplStock.h
//
//	Stock accout class
//	Author: Vladimir Krapp
//	Created on: 23/3/14
//	Last modified:

#ifndef __STOCK_ACCOUNT_IMPL_H__
#define __STOCK_ACCOUNT_IMPL_H__

#include "AccountImpl.h"

class AccImplStock : public AccountImpl
{
    friend class AccountImpl;

    public:
        virtual void UpdateImpl();

    private:
        AccImplStock();
        ~AccImplStock();   

        bool m_actOnUpdate;

        static bool s_nextActOnUpdate;
};

#endif //__STOCK_ACCOUNT_IMPL_H__
