//    timing.h
//
//
//    Author: Vladimir Krapp
//    Created on: 2014-04-09
//    Last modified:

#ifndef __TIMING_H__
#define __TIMING_H__

#include <iostream> // for operator<<
#include <cmath>    // for modf (CTOR from float)

#ifdef WINDOWS

#elif UNIX
#include <unistd.h> // for timespec, clock_gettime etc
#endif

//====================================================================


class Time 
#ifdef WINDOWS

#elif UNIX
	: public timespec
#endif

{
public:

    // create Time object set to zero
    Time();

    // create Time object from float representing seconds
    Time(float _sec);

    // using generated Copy CTOR

    // using generated Assignment op

    // Increment Time object by the value of _rhs
    Time& operator+=(const Time& _rhs);

    // NOT IMPLEMENTED
    // Decrement value of Time object from _rhs
    Time& operator-=(const Time& _rhs);

    // return a Time object set to the current epoch time
    static Time Now();


private:

    // Output a representation of Time to stream
    friend std::ostream& operator<<(std::ostream& _os, const Time& _t);

};

std::ostream& operator<<(std::ostream& _os, const Time& _t);


#endif // __TIMING_H__
