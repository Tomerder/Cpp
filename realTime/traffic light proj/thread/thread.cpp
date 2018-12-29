#include "thread.h"

#include <stdexcept>
#include <cstdio>
#include <iostream>

#include <cstdlib>
#include <unistd.h>
#include <time.h>

#include <cxxabi.h>

using namespace std;



class Attr
{
    pthread_attr_t m_attr;

public:
        Attr()
        {
            pthread_attr_init(&m_attr);

        }
        ~Attr(){pthread_attr_destroy(&m_attr);}

        int SetDettachedState(bool _createDetached)
        {
            return pthread_attr_setdetachstate(
                            &m_attr,
                            (_createDetached)?
                            PTHREAD_CREATE_DETACHED:
                            PTHREAD_CREATE_JOINABLE);
        }

        operator pthread_attr_t*()
        {
            return &m_attr;
        }

};

Thread::Thread(Runnable* _routine, bool _startDetached)
    :m_routine(_routine), m_status(RUNNING)
{
    Attr attr;

    if(_startDetached)
    {
        m_status = DETACHED;
    }

    attr.SetDettachedState(_startDetached);

    pthread_create(&m_thread, attr, Thread::RunRoutine, m_routine);

}

Thread::~Thread()
{
    if(m_status == RUNNING)
    {
        perror("still running at DTOR");
        pthread_cancel(m_thread);
    }
}

void* Thread::RunRoutine(void* _th)
{
    Runnable* pThis = static_cast<Runnable*>(_th);
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, 0);

    try
    {
        (*pThis)();
    }
    catch(abi::__forced_unwind&)
    {
        throw;
    }
    catch(...)
    {
        ;
    }

    return 0;
}

void Thread::Join()
{
    int err = pthread_join(m_thread, 0);

    if(err)
    {
        throw runtime_error("Error joining thread");
    }
    m_status = NOT_RUNNING;
}

int Thread::Join(int  _milliseconds)
{

    timespec ts;

    clock_gettime(CLOCK_REALTIME, &ts);

     ts.tv_sec += _milliseconds/1000;
     ts.tv_nsec += (_milliseconds%1000)*1000000;

    int err = 0;

    if(_milliseconds)
    {
         err = pthread_timedjoin_np(m_thread, 0, const_cast<const timespec*>(&ts));
    }
    else
    {
        err = pthread_tryjoin_np(m_thread, 0);
    }

    if(!err)
    {
        m_status = NOT_RUNNING;
    }

    return err;
}

void Thread::Detach()
{
    m_status = DETACHED;
    int err = pthread_detach(m_thread);


    if(err)
    {
        throw runtime_error("Error detaching thread");
    }
}

void Thread::Cancel()
{
    if(m_status != RUNNING)
    {
        ;
    }

    m_status = NOT_RUNNING;

    int err = pthread_cancel(m_thread);

    if(err)
    {
        throw runtime_error("Error cancelling thread");
    }

}


ThreadID Thread::GetID() const
{
    return m_thread;
}








//== Class Time function ============================================
//
//Time::Time(size_t _sec, size_t _usec)
//{
//    tv_sec = _sec;
//    tv_usec = _usec;
//}
//
//bool Time::operator<(const Time& _rhs) const
//{
//    return timercmp(this, &_rhs, <);
//}
//
//bool Time::operator==(const Time& _rhs) const
//{
//    return timercmp(this, &_rhs, ==);
//}
//
//Time Time::operator-(const Time& _rhs) const
//{
//    Time ret;
//    timersub(this, &_rhs, &ret);
//    return ret;
//}
//
//Time Time::operator+(const Time& _rhs) const
//{
//    Time ret;
//    timeradd(this, &_rhs, &ret);
//    return ret;
//}
//
//
//const struct timeval* Time::Timeval()
//{
//    return this;
//}
//
//int Time::SetToCurrent()
//{
//   return gettimeofday(this, 0);
//}
