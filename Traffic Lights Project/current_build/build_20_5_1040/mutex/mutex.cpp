// mutex.cpp
// 
// Platform independent mutex class
// Author: Vladimir Krapp
// Created on: 7/4/14
// Last modified:

#include <iostream> // for debug
#include <stdexcept>
#include <pthread.h>

#include <cstdio> // for debugg prints

#include "mutex.h"
#include "utility.h"
#include "timing.h"

using namespace std;

Mutex::Mutex()
{
    int err = pthread_mutex_init(&m_mtx, 0);

    EvalErrAndThrow<MutexException>(err, "Mutex::CTOR error");
}

Mutex::~Mutex() throw ()
{
    int err = pthread_mutex_destroy(&m_mtx);
    if(err)
    {
        // TODO: Log error
    }
}

void Mutex::Lock()
{
    int err = pthread_mutex_lock(&m_mtx);

    EvalErrAndThrow<MutexException>(err, "Mutex::Lock error");
}

bool Mutex::Lock(int _milliseconds)
{
    int err = 0;
    
    if(_milliseconds <= WAIT_INFINITE)
    {
        Time t(_milliseconds  * 1000);
        t += Time::Now();
        err = pthread_mutex_timedlock(&m_mtx, &t);
    }
    else
    {
        err = pthread_mutex_lock(&m_mtx);
    }
    
    
    if(err == ETIMEDOUT)
    {
            return false;
    }

    EvalErrAndThrow<MutexException>(err, "Mutex::Lock error");

    return true;
}

void Mutex::Unlock() 
{
    int err = pthread_mutex_unlock(&m_mtx);

    EvalErrAndThrow<MutexException>(err, "Mutex::nlock error");
}

//===================

Lock::Lock(Mutex& mtx):
    m_mtx(mtx)
{
    m_mtx.Lock();
}

Lock::~Lock()
{
    m_mtx.Unlock();
}
