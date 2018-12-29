#ifndef HEBREWDATEIMPL_H
#define HEBREWDATEIMPL_H

#include "DateImpl.h"

class HebrewDateImpl : public DateImpl {
public:
	HebrewDateImpl( int day, int month) 
		: DateImpl( day, month ) {/*..*/ }

	virtual void tell() { 
	   cout << "Hebrew Date is :" << d <<"/" << m << endl; 
	}
};

#endif
