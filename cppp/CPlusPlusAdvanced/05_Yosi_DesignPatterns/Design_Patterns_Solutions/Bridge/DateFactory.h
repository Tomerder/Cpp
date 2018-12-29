#ifndef DATEFACTORY_H
#define DATEFACTORY_H

#include <string>
#include "Date.h"
#include "HebrewDateImpl.h"		
#include "ArabicDateImpl.h"		

using namespace std;

class DateFactory {
public:
	static DateImpl* CreateDate(const string& Impl, int day, int month ) {
		DateImpl* ptrDate = 0;
  		if (Impl == "Hebrew")   
			ptrDate = new HebrewDateImpl( day, month );
  		if (Impl == "Arabic") 
			ptrDate = new ArabicDateImpl( day, month );
		return ptrDate;
	};
private:
	~DateFactory();
	DateFactory();
};

#endif
