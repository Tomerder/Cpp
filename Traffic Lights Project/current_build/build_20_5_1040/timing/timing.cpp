// timing.cpp
//
//	Timing class implementation
//	Author: Vladimir Krapp
//	Created on: 23/4/14
//	Last modified:

#include "timing.h"

using namespace std;

static const unsigned int NANOSEC_IN_SEC  = 1E9;

Time::Time()
{
    tv_sec = 0;
    tv_nsec = 0;
}



Time::Time(float _sec)
{
	double intpart = 0;
	double fractpart = modf(_sec, &intpart);
    
	tv_sec = static_cast<time_t>(intpart);
	tv_nsec = static_cast<time_t>(fractpart * NANOSEC_IN_SEC);
}

Time&
Time::operator+=(const Time& _rhs)
{
   
    unsigned long tmp;
   
    tmp = tv_nsec + _rhs.tv_nsec;
    if (tmp < NANOSEC_IN_SEC)
    {
        tv_nsec = tmp;
    }
    else
    {
        tv_nsec = tmp - NANOSEC_IN_SEC;
        tv_sec += 1;
    }
    tv_sec = tv_sec + _rhs.tv_sec;

    return *this;
}



Time
Time::Now()
{
    Time t;
    clock_gettime(CLOCK_REALTIME, &t);
    return t;
}




ostream&
operator<<(std::ostream& _os, const Time& _t)
{
    return _os << _t.tv_sec << '\'' << _t.tv_nsec;
}
