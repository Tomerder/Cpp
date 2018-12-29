/************************************************************************
Mutex
Author: Dan Bar-On.
Creation Date: 23.04.14 
Modified at:
Description: Mutex and a locker(unlocks in DTOR).
************************************************************************/
#ifndef MUTEX_H
#define MUTEX_H

#ifdef WIN32 
#include <windows.h>
#include "stdafx.h"
#elif UNIX
#include <pthread.h>
#endif

#include "uncopyable.h"

#ifdef WIN32 
class MULTITHREADING_API Mutex: private Uncopyable {	
#elif UNIX
class Mutex: private Uncopyable {
#endif
public:
    Mutex();				//throws BadMutex exception
    ~Mutex();		
    void Lock() const;		//throws BadMutex exception
    void Unlock() const;	//throws BadMutex exception
    bool TryLock() const;   //throws BadMutex exception. Not implemented in windows

	bool Lock(float _timeout); // not implemented

private:
#ifdef WIN32 
	mutable HANDLE m_mutex;
#elif UNIX
	mutable pthread_mutex_t m_mutex;
#endif

};


// use Lock to lock exception safely.

#ifdef WIN32 
class MULTITHREADING_API Lock: private Uncopyable{
#elif UNIX
class Lock: private Uncopyable{
#endif

public:
    inline Lock(Mutex&);
    inline ~Lock();
private:
	Mutex& m_mutex;
};

Lock::Lock(Mutex& _mutex):m_mutex(_mutex)
{
    m_mutex.Lock();
}

Lock::~Lock()
{
	m_mutex.Unlock();
}


#endif // MUTEX_H
