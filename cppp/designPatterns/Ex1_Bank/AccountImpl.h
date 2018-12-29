// AccountImpl.h
//
//	Account Implementation class for Bank exercise
//	Author: Vladimir Krapp
//	Created on: 23/3/14
//	Last modified:

#include "Common.h"
#include "Observer.h"

#ifndef __ACCOUNT_IMPL_H__
#define __ACCOUNT_IMPL_H__


class AccountImpl{ 
public: 
    
    static AccountImpl* Create(const Type& _type);       // Factory Method
    static void     Destroy(AccountImpl* _acc);          // Factory Method

    virtual void UpdateImpl() = 0;

protected:
		AccountImpl();	    // CTOR 
        virtual ~AccountImpl();		 		        // DTOR

private:

        AccountImpl(const AccountImpl&);            // no copy!
        AccountImpl& operator=(const AccountImpl&); // no copy!

        // Data members
}; 






#endif //__ACCOUNT_IMPL_H__
