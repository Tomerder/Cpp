#include <iostream>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
#include <errno.h>
#include <stdexcept>

#include "thread.h"

using namespace std;

namespace m10
{


Thread::Thread(Runnable& r): m_isAlive(false)
{
    int error = pthread_create(&m_thread, 0, Runner, &r);
    if (error)
    {
        throw runtime_error("Fail to create Thread");
    }
    m_isAlive = true;
}

void* Thread::Runner(void* ptr)
{
    Runnable* pThis = static_cast<Runnable*>(ptr);
    try
    {
        (*pThis)();
    }
    catch(...)
    {
        throw;
    }
}

void Thread::Join() const
{
    if (!m_isAlive)
    {
        return;
    }

    int error = pthread_join(m_thread, 0);
    if (error)
    {
        throw std::runtime_error("Fail to Thread::Join");
    }
    m_isAlive = false;
}

int Thread::JoinTO(unsigned long sec, unsigned long usec) const
{
    if (!m_isAlive)
    {
        return -1;
    }

    struct timeval touSec = {sec, usec};
    struct timeval now;
    struct timeval res;

    int error = gettimeofday(&now, 0);
    if (error)
    {
        throw runtime_error("Fail to Thread::JoinTO");
    }

    timeradd(&now, &touSec, &res);
    struct timespec tonSec = {res.tv_sec, res.tv_usec*1000};
    error = pthread_timedjoin_np(m_thread, 0, &tonSec);
    if (!error) // join succeeded
    {
        m_isAlive = false;
    }
    return error;
}

void Thread::Kill() const
{
    if (!m_isAlive)
    {
        return;
    }

    int error = pthread_cancel(m_thread);
    if (error==ESRCH) cout << m_thread << " ESRCH" << endl;
    if (error)
    {
        throw runtime_error("Fail to Thread::Kill");
    }
    m_isAlive = false;
}

void Thread::Deattach() const
{
    if (!m_isAlive)
    {
        return;
    }

    int error = pthread_detach(m_thread);
    if (error)
    {
        throw runtime_error("Fail to Thread::Deattach");
    }
    m_isAlive = false;

}

unsigned long Thread::MyID() const
{
    return m_thread;
}

unsigned long Thread::GetID()
{
    return pthread_self();
}

Thread::~Thread()
{
    try
    {
        Kill();
    }
    catch(...)
    {

    }

}

}
