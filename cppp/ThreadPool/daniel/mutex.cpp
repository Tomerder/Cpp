#include <pthread.h>
#include <stdexcept>

#include "mutex.h"

namespace m10
{

Mutex::Mutex()
{
    int error = pthread_mutex_init(&m_mut, 0);
    if (error)
    {
        throw std::runtime_error("Fail to create Mutex");
    }
}

Mutex::~Mutex()
{
    pthread_mutex_destroy(&m_mut);
}

void Mutex::Lock()
{
    int error = pthread_mutex_lock(&m_mut);
    if (error)
    {
        throw std::runtime_error("Fail to Mutex::Lock");
    }
}


void Mutex::Unlock()
{
    int error = pthread_mutex_unlock(&m_mut);
    if (error)
    {
        throw std::runtime_error("Fail to Mutex::Unock");
    }
}


Lock::Lock(Mutex& mutex): m_mut(mutex)
{
    m_mut.Lock();
}

Lock::~Lock()
{
    m_mut.Unlock();
}



}
