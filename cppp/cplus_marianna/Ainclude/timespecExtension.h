/**************************************************************************************
    Author: Marianna Shvartsman
    Creation date :      2013-11-30
    Last modified date: 2013-11-30 
    Description : TimespecExtansion
***************************************************************************************/
#ifndef __TIMESPECEXTENSION_H__
#define __TIMESPECEXTENSION_H__

#include <ctime>
#include "uncopyable.h"
//Description: Extension functions to work with timespec structure, 
//Reminder:	struct timespec {
//        time_t   tv_sec;        /* seconds */
//        long     tv_nsec;       /* nanoseconds */};


//**************************************************************************************
//		TimeSpecExtention Definition
//**************************************************************************************

namespace multithreading_m7
{

class TimeSpecExtension: private Uncopyable
{
public:
	//function converts milliseconds given in size_t to  timespec
	static void SizeT2TimeSpec(size_t _msec, timespec* _time);
	
	//function converts timespec struct to size_t
	static size_t TimeSpec2SizeT(timespec* _time);
	
	//function gets current time from CLOCK_MONOTONIC clock and puts it to now
	//throw exeption if gettime is faild
	static	 void GetCurrentTime(timespec* _now)throw(char*);
	
	// function return difference between time1 and time2, and put it into _timediff 
	// if time1 < time2 _timediff will have zero filds
	static	void TimeSpecMinus(const  timespec* _time1, const  timespec* _time2,  timespec* _timediff);
	
	// function adds time1 and time2, the result is storaged in _timesum 
	static	void TimeSpecPlus(const  timespec* _time1, const  timespec *_time2,  timespec* _timesum);
	
	//function compare times and returns:
	//if time1 < time2  returns -1
	//if time1 = time2  returns 0
	//if time1 > time2  returns 1
	static int TimeSpecCompare(const  timespec* _time1,const  timespec* _time2);
	
	//function get miliseconds, and calculate the deadline 
	static void Msec2DeadLine(size_t _msec,  timespec* _deadline)throw(char*);
	
	//returns true time interval to deadline is positive, and it's value storaged in _timeToEnd,
	// if deadline expired returns false and _timeToEnd has zero filds
	static bool TimeSpec2DeadLine(const  timespec* _deadline,  timespec* _timeToEnd);
	
private:
	static const long MILLISEC_PER_SECOND = 1000;  
	static const long NANOSEC_PER_SECOND = 1000000000u; //billion
	static const long NANOSEC_PER_MILLISEC = 1000000; // million
};

}//end namespace
#endif// __TIMESPECEXTENSION_H__
