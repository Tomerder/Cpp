#ifndef DATEIMPL_H
#define DATEIMPL_H

#include <iostream>
#include <iomanip>
#include <string>


class DateImpl {
public:
	DateImpl( int day, int month ) { d = day;  m = month; }

	virtual void	tell() = 0;
	int				getDay() const		{ return d;}
	int				getMonth() const	{ return m;}
protected:
   int d, m;
};

#endif
