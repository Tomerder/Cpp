// Account.h
//
//	Account class for Bank exercise.
//  Inherits from Observer.
//  
//	Author: Vladimir Krapp
//	Created on: 23/3/14
//	Last modified:

#include <iostream>

#include "AccountImpl.h"
#include "Common.h"
#include "Observer.h"

#ifndef __ACCOUNT_H__
#define __ACCOUNT_H__

class Account: public Observer 
{ 

public: 
        static Account* Create(const Type& _type, Subject* _bank);
        static void     Destroy(Account* _acc);

        virtual void Update(const Subject* _bank);	

        friend std::ostream& operator<<(std::ostream& _os, Account* _acc);

protected:
        AccountImpl* m_impl;

private:

		Account(const Type& _type, Subject* _bank);
        virtual ~Account();

        Account(const Account&);            // no copy!
        Account& operator=(const Account&); // no copy!

        const int          m_id;
        const Type        m_type;

        static int   s_idNext;
}; 






#endif //__ACCOUNT_H__
