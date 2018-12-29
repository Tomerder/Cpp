/**************************************************************************************
    Author: Marianna Shvartsman
    Creation date :      2013-11-30
    Last modified date: 2013-12-1
    Description : TimeSpecExtension Implementation
***************************************************************************************/
#include "timespecExtension.h"
using namespace multithreading_m7;

//*************************************************************************************************
//		SizeTtoTimeSpec:
//						function converts milliseconds given in size_t to  timespec
//*************************************************************************************************

void TimeSpecExtension::SizeT2TimeSpec(size_t _msec,  timespec* _time)
{
	_time->tv_sec = _msec / MILLISEC_PER_SECOND;
	_time->tv_nsec = (_msec%MILLISEC_PER_SECOND)*NANOSEC_PER_MILLISEC;
	
}

//*************************************************************************************************
//		SizeTtoTimeSpec:
//						function converts timespec struct to size_t
//*************************************************************************************************
size_t TimeSpecExtension::TimeSpec2SizeT(timespec* _time)
{
	return _time->tv_sec * MILLISEC_PER_SECOND + _time->tv_nsec/NANOSEC_PER_MILLISEC;
}

//*************************************************************************************************
//		GetCurrentTime:
//						function gets current time from CLOCK_MONOTONIC clock 
//						throw exeption if gettime is faild
//*************************************************************************************************
void TimeSpecExtension::GetCurrentTime( timespec* _now)throw(char*)
{
	//gettime from CLOCK_MONOTONIC 
    if (clock_gettime(CLOCK_MONOTONIC, _now))
    {
    	throw "Clock gettime is faild";
    }
	
}


//*************************************************************************************************
//		TimeSpecMinus:
//					 function return difference between time1 and time2, and storage the result in _timediff 
// 					if time1 < time2 _timediff will have zero filds
//*************************************************************************************************
void TimeSpecExtension::TimeSpecMinus(const  timespec* _time1, const  timespec* _time2,  timespec* _timediff)
{
	//time1 <= time2  ?
   if ((_time1->tv_sec < _time2->tv_sec) ||
    ((_time1->tv_sec == _time2->tv_sec) && (_time1->tv_nsec <= _time2->tv_nsec))) 
    {		
        _timediff->tv_sec = 0;
        _timediff->tv_nsec = 0;
    }
    else //time1 > time2
    {						
        _timediff->tv_sec = _time1->tv_sec - _time2->tv_sec ;
        if (_time1->tv_nsec < _time2->tv_nsec)
        {
       		_timediff->tv_nsec = _time1->tv_nsec + NANOSEC_PER_SECOND - _time2->tv_nsec ;
            --_timediff->tv_sec;				/* Borrow a second. */
        }
        else
        {
            _timediff->tv_nsec = _time1->tv_nsec - _time2->tv_nsec ;
        }
    }
	
}

//*************************************************************************************************
//		TimeSpecPlus:
//					function adds time1 and time2, the result is storaged in _timesum 
//*************************************************************************************************
void TimeSpecExtension::TimeSpecPlus(const  timespec* _time1, const  timespec *_time2,  timespec* _timesum)
{
	_timesum->tv_sec = _time1->tv_sec + _time2->tv_sec;
	_timesum->tv_nsec = _time1->tv_nsec + _time2->tv_nsec;
	
	if (_timesum->tv_nsec > NANOSEC_PER_SECOND)
	{
		_timesum->tv_nsec /= NANOSEC_PER_SECOND;
		++_timesum->tv_sec;
	}
	
}

//*************************************************************************************************
//		TimeSpecCompare:
//						function compare times and returns:
//						if time1 < time2  returns -1
//						if time1 = time2  returns 0
//						if time1 > time2  returns 1
//*************************************************************************************************
	
int TimeSpecExtension::TimeSpecCompare(const  timespec* _time1, const  timespec* _time2)
{
	if (_time1->tv_sec > _time2->tv_sec)
	{
		return 1;
	}
	
	if (_time1->tv_sec < _time2->tv_sec)
	{
		return -1;
	}
	else //time1->tv_sec == time2->tv_sec
	{
		if (_time1->tv_nsec > _time2->tv_nsec)
		{
			return 1;
		}
		
		if(_time1->tv_nsec < _time2->tv_nsec)
		{
			return -1;
		}
		else //time1->tv_nsec == time2->tv_nsec
		{
			return 0;
		}
	}
	
}	

//*************************************************************************************************
//		Msec2DeadLine:	
//						function get miliseconds, and calculate the deadline 
//*************************************************************************************************


void TimeSpecExtension::Msec2DeadLine(size_t _msec,  timespec* _deadline)throw(char*)
{
	 timespec now;
	 timespec interval;
	GetCurrentTime(&now);
	//convert time from size_t to timespec
	SizeT2TimeSpec(_msec,&interval);
 	//calculate deadline
	TimeSpecPlus(&now,&interval,_deadline);
	
}


//*************************************************************************************************
//		TimeSpec2DeadLine:	
//						//returns true time interval to deadline is positive, and it's value storaged in _timeToEnd,
//						// if deadline expired returns false and _timeToEnd has zero filds
//*************************************************************************************************
bool TimeSpecExtension::TimeSpec2DeadLine(const  timespec* _deadline,  timespec* _timeToEnd)
{
	 timespec now;
	GetCurrentTime(&now);
	
	TimeSpecMinus(_deadline, &now, _timeToEnd);
	
	if ((0 == (_timeToEnd->tv_sec)) and (0 == (_timeToEnd->tv_nsec)))
	{
		return false; //timeout expired
	}
	
	return true;
}
