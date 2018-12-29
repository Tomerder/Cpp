#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

#include "Date.h"
#include "DateImpl.h"
#include "DateFactory.h"

Date::~Date()  {
	delete m_Date;				// delete implementation creted by Factory
	m_Date=0;
}

Date::Date(const string& Impl, int day, int month ) {
	m_Date = DateFactory::CreateDate(Impl, day, month);	
	// Use factory to creater Date over any implemetations
	// If new implementations will be added the Date class willn't be changed !!!
	// the only change will be in Factory
}

void Date::tell() {				// just rederection to implementation class
	m_Date->tell(); 
}

int Date::getDay() const {		// just rederection to implementation class
	return m_Date->getDay();
}

int Date::getMonth() const {	// just rederection to implementation class
	return m_Date->getMonth();
}
