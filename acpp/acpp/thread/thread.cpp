#include <string>
#include <assert.h>
#include <cxxabi.h>	//__cxxabiv1::__forced_unwind


#include "thread.h"
#include "mytime.h"	// Time
#include "myexceptions.h"	//BadThread

//add mutex to make the threa thread-safe


using namespace std;

Thread::Thread(std::tr1::shared_ptr<Runnable> _run, bool _joinable):
m_run(_run), m_joinable(_joinable), m_joined(false)
{
    // pthread create is a memory barrier
	CHECK_AND_THROW_DIF(pthread_create(&m_thread , 0, Runner, this), 0 ,"Thread CTOR", BadThread);
	//this is a problem - if detached object Thread was destroyed. what to do? Send pointer to shared ptr. But then we have a race. Then - in the DTOR wait on a condition or something to the copy of the shared_ptr.

	if (!m_joinable)
	{
		CHECK_AND_THROW_DIF(pthread_detach(m_thread), 0 ,"Thread CTOR", BadThread);
	}
}

Thread::~Thread()
{
	Lock lock(m_mutex);
    if (m_joinable && !m_joined)
    {
//        std::terminate();
    }
}

void Thread::Join()
{
	Lock lock(m_mutex);
    if (!m_joinable)
    {
        throw std::runtime_error("Join not joinable");
    }
	CHECK_AND_THROW_DIF(pthread_join(m_thread,0), 0 ,"Thread Join", BadThread);
	m_joined = true;
}

bool Thread::JoinTimeout(float _interval)
{
	Lock lock(m_mutex);
    if (!m_joinable)
    {
    	THROW("JoinTimeout not joinable", BadThread);
    }

    Time time(_interval);
    time.AddNowToGetAbsTime();

	int ret = pthread_timedjoin_np(m_thread,0, time);
	if (ret != 0)
	{
	    if (ret == ETIMEDOUT)
	    {
            return false;
	    }
	    else
	    {
  	    	THROW("Thread JoinTimeout", BadThread);
	    }
	}
    m_joined = true;
	return true;
}

bool Thread::JoinTimeoutAbs(Time _abstime)
{
	Lock lock(m_mutex);
    if (!m_joinable)
    {
		THROW("JoinTimeout not joinable", BadThread);
    }

	int ret = pthread_timedjoin_np(m_thread,0, _abstime);
	if (ret != 0)
	{
	    if (ret == ETIMEDOUT)
	    {
            return false;
	    }
	    else
	    {
			THROW("Thread JoinTimeout", BadThread);
	    }
	}
    m_joined = true;
	return true;
}




bool Thread::JoinTry()
{
	Lock lock(m_mutex);
    if (!m_joinable)
    {
		THROW("JoinTry not joinable", BadThread);
    }
	int ret = pthread_tryjoin_np(m_thread,0);
	if (ret != 0)
	{
        if (ret == EBUSY)
        {
            return false;
        }
        else
        {
       		THROW("Thread Join", BadThread);
        }
	}
	m_joined = true;
    return true;
}



void Thread::Cancel()
{
    assert(!m_joined);
	Lock lock(m_mutex);

	CHECK_AND_THROW_DIF( pthread_cancel(m_thread), 0 ,"Cancel", BadThread);
	m_joinable = 0;
}

void Thread::Detach()
{
    assert(!m_joined);
	Lock lock(m_mutex);
	CHECK_AND_THROW_DIF( pthread_detach(m_thread), 0 ,"Detach", BadThread);
    m_joinable = false;
}


//static 
void* Thread::Runner(void* _params)
{
    Thread* t = static_cast<Thread*> (_params);

    try{
        (*t->m_run)();
    }
    catch (__cxxabiv1::__forced_unwind&) { throw;}
    catch (...)
    {
    	//write to stderr (fprintf(stderr, "  " ) )
    }

	return 0;
}
