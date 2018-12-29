#include <pthread.h>
#include <stdexcept>
#include <string>
#include <cerrno>
#include "myexceptions.h"
#include "mutex.h"

Mutex::Mutex()
{
	CHECK_AND_THROW_DIF(pthread_mutex_init(&m_mutex, 0), 0 ,"Mutex CTOR", BadMutex);
}

Mutex::~Mutex()
{
	pthread_mutex_destroy(&m_mutex);
}

void Mutex::Lock() const
{
	CHECK_AND_THROW_DIF(pthread_mutex_lock (&m_mutex), 0 ,"Mutex Lock", BadMutex);
}

void Mutex::Unlock() const
{
	CHECK_AND_THROW_DIF(pthread_mutex_unlock (&m_mutex), 0 ,"Mutex unlock", BadMutex);
}

bool Mutex::TryLock() const
{
    int ret = pthread_mutex_trylock(&m_mutex);
    if (ret != 0)
    {
        if (ret == EBUSY)
        {
            return false;
        }
        else
        {
        	THROW("Mutex TryLock", BadMutex);
        }
    }
    return true;
}
