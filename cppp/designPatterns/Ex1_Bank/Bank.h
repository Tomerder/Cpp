// Bank.h
//
//	Singleton Bank class
//
//	Author: Vladimir Krapp
//	Created on: 23/3/14
//	Last modified:

#ifndef __BANK_H__
#define __BANK_H__

#include <vector>
#include <set>

#include "Account.h"
#include "Common.h"
#include "Subject.h"

class Bank : public Subject 
{

public: 
	static Bank& getBank(); 

    Account* CreateAccount(Type _type);
    void     DeleteAccount(Account* _acc);

    void OpSavings();
    void OpFamily();
    void OpStock();


private: 
	static Bank m_bank;

    std::set<Account*> m_accounts;

private: 
	Bank();                             // PRIVATE 
	~Bank();                            // PRIVATE
	Bank(const Bank&);                  // no  copy 
	void operator=(const Bank&);		// no copy 

}; 




#endif //__BANK_H__
