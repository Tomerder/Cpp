#include <time.h>

#include "mytime.h"

Time::Time(float _time)
{
	m_time.tv_sec = (time_t)_time;
	m_time.tv_nsec = (long)((_time - (float)m_time.tv_sec)*(float)GIGA);
}

Time::~Time()
{}

Time::operator struct timespec*()
{
    return &m_time;
}

void Time::AddNowToGetAbsTime()
{
    struct timespec now;
    clock_gettime(CLOCK_REALTIME, &now);

   	long nanoSum = now.tv_nsec + m_time.tv_nsec;
    m_time.tv_sec = nanoSum / GIGA + now.tv_sec + m_time.tv_sec;
	m_time.tv_nsec = nanoSum % (long)GIGA;
}

bool Time::operator<(const Time& _rhs) const
{
	if (m_time.tv_sec < _rhs.m_time.tv_sec ||
		( m_time.tv_sec == _rhs.m_time.tv_sec && m_time.tv_nsec < _rhs.m_time.tv_nsec))
	{
		return true;
	}
	return false;
}




