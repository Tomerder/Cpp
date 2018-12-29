#ifndef DATE_H
#define DATE_H

#include <string>
using namespace std;

class DateImpl;

class Date {
public:
				 ~Date();
				 Date(const string& Impl, int day, int month );
	virtual void tell();

	int getDay() const;
	int getMonth() const;
protected:
	DateImpl*  m_Date;
};

#endif
