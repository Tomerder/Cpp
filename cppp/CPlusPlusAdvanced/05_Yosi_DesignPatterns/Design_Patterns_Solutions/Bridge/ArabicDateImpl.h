#ifndef ARABICDATEIMPL_H
#define ARABICDATEIMPL_H

#include "DateImpl.h"


class ArabicDateImpl : public DateImpl {
public:
	ArabicDateImpl( int day, int month) 
		: DateImpl( day, month ) {/*..*/ }

	virtual void tell() { 
	   cout << "Arabic Date is :" << d <<"/" << m << endl; 
	}
};


#endif
