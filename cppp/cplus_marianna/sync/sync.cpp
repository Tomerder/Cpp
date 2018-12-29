/**************************************************************************************
    Author: Marianna Shvartsman
    Creation date :      2013-11-18
    Last modified date: 2013-11-18
    Description : Sync Unit  LINUX Implementation 
***************************************************************************************/
#include <iostream>
using namespace std;
#include <ctime>
#include <errno.h>

#include "sync.h"

#ifdef __LINUX 
#include "timespecExtension.h"
#endif

using namespace multithreading_m7;


//--------------------------------------------------------
//			CTOR CondVar
//--------------------------------------------------------
CondVar::CondVar()throw(char*)
{
#ifdef __LINUX
	// Set the clock to be CLOCK_MONOTONIC
    pthread_condattr_t attr;
    if (0 != pthread_condattr_init(&attr))
    {
    	throw "CondVariable attrebute initialization faild";
    }
    if ( 0 != pthread_condattr_setclock(&attr, CLOCK_MONOTONIC))
    {
    	throw "CondVariable attrebute setclock faild";
    }

	if ( 0 != pthread_cond_init(&m_cond,&attr))
    {
    	throw "CondVariable initialization faild";
    }
#else
	InitializeConditionVariable(&m_cond);
#endif
	
}
//--------------------------------------------------------
//			DTOR CondVar
//--------------------------------------------------------
CondVar::~CondVar()throw(char*)
{
#ifdef __LINUX
	if ( 0 != 	pthread_cond_destroy(&m_cond))
    {
    	throw "CondVariable destroy faild";
    }
#endif

}

//--------------------------------------------------------
//			Wait
//--------------------------------------------------------			
bool	CondVar::Wait(Mutex* _mutex,size_t _timeout)throw(char*)
{
#ifdef __LINUX
	if (_timeout == TIMEOUT_FOREVER)
	{
		return !pthread_cond_wait(&m_cond, &_mutex->m_mutex);
		
	}
	else
	{
		timespec deadline;
		TimeSpecExtension::Msec2DeadLine(_timeout,&deadline);
		int err = pthread_cond_timedwait(&m_cond, &_mutex->m_mutex, &deadline);
    	if (err == ETIMEDOUT)
        	return false;
        if(err != 0)
        {
        	throw "CondVariable wait faild";
        }
    }

#else
	if( 0 == SleepConditionVariableCS (&m_cond, &_mutex->m_lock, _timeout))
	{
		if (GetLastError() == ERROR_TIMEOUT)
		{
				return false;
		}
		else
		{
			throw "CondVariable wait faild"; 
		}
	}

#endif

	return true; 
}

//--------------------------------------------------------
//			NotifyOne
//--------------------------------------------------------
void	CondVar::NotifyOne()throw(char*)
{
#ifdef __LINUX
	if ( 0 != 	pthread_cond_signal(&m_cond))
    {
    	throw "CondVariable NotifyOne faild";
    }
#else
	WakeConditionVariable(&m_cond);
#endif

}

//--------------------------------------------------------
//			NotifyAll
//--------------------------------------------------------
void	CondVar::NotifyAll()throw(char*)
{
#ifdef __LINUX
	if ( 0 != 	pthread_cond_broadcast(&m_cond))
    {
    	throw "CondVariable broadcast faild";
    }
#else
	WakeAllConditionVariable(&m_cond);
#endif
}

//--------------------------------------------------------
//			CTOR Mutex:  mutex init
//--------------------------------------------------------
Mutex::Mutex()throw(char*)
{
#ifdef __LINUX
	if ( 0 != pthread_mutex_init(&m_mutex,0))
    {
    	throw "Mutex init faild";
    }
#else
	InitializeCriticalSection(&m_lock);
#endif

}

//--------------------------------------------------------
//			DTOR Mutex: mutex destroy
//--------------------------------------------------------
Mutex::~Mutex()throw(char*)
{
#ifdef __LINUX
	if ( 0 != 	pthread_mutex_destroy(&m_mutex))
    {
    	throw "Mutex destroy faild";
    }
#else
	DeleteCriticalSection(&m_lock);
#endif
}


//--------------------------------------------------------
//			Mutex timed lock
//--------------------------------------------------------		
bool	Mutex::Lock(size_t _timeout)throw(char*)
{
#ifdef __LINUX
	if (_timeout == TIMEOUT_FOREVER)
	{
		pthread_mutex_lock(&m_mutex);
		
	}
	else
	{
		timespec deadline;
		TimeSpecExtension::Msec2DeadLine(_timeout,&deadline);
	
		int err = pthread_mutex_timedlock(&m_mutex, &deadline);
	
		if (err == ETIMEDOUT)
		{
			return false;
		}
		if(err != 0)
        {
        	throw "Mutex lock faild";
        }
    }
#else
	EnterCriticalSection(&m_lock);
#endif

	return true; 
}

//--------------------------------------------------------
//			Mutex unlock
//--------------------------------------------------------
void	Mutex::Unlock()throw(char*)
{
#ifdef __LINUX
	if ( 0 != pthread_mutex_unlock(&m_mutex))
    {
    	throw "Mutex lock faild";
    }	
#else
	LeaveCriticalSection(&m_lock);
#endif
}

