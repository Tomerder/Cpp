/************************************************************************
Time
Author: Dan Bar-On.
Creation Date: 23.04.14 
Modified at:
Description: Handles some time handling functions.
************************************************************************/
#ifndef TIME_H
#define TIME_H

#include <time.h>	//struct timespec

class Time
{
public:

    Time(float _time = 0); // returns interval
    ~Time();

    void AddNowToGetAbsTime();
    operator struct timespec*();
    bool operator<(const Time&) const;

private:
    struct timespec m_time;
    //generated copy ctor and op=

    static const size_t GIGA = (1000000000L);
};

#endif // TIME_H
