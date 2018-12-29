#include <cassert>


#include "thread.h"
//#include "mytime.h"	// Time
#include "myexceptions.h"	//BadThread

using namespace std;

Thread::Thread(RunShared _run, bool _joinable):
m_run(_run), m_joinable(_joinable), m_joined(false)
{
	m_thread = CreateThread( 
    NULL,                   // default security attributes
    0,                      // use default stack size  
    (LPTHREAD_START_ROUTINE)Runner,			        // thread function name
	this,		            // argument to thread function 
    0,                      // use default creation flags 
    &m_id);   // returns the thread identifier 

	CHECK_AND_THROW_EQ(m_thread, 0, "Thread CTOR", BadThread);

	if (!m_joinable)
	{
		CloseHandle(m_thread);
	}
}

Thread::~Thread()
{
	Lock lock(m_mutex);
    if (m_joinable)
    {
		if (!m_joined)
		{
			TerminateThread(
			m_thread, //  HANDLE hThread
			0         //	DWORD dwExitCode
			);
		}
		CloseHandle(m_thread);
	}
}

bool Thread::JoinImp(DWORD _miliSec)
{
	Lock lock(m_mutex);

	// change to macro
    if (!m_joinable)
    {
        throw runtime_error("Join not joinable");
    }

	DWORD ret = WaitForSingleObject( 
            m_thread,    // handle to mutex
            _miliSec);  // no time-out interval
 
	if (ret != WAIT_OBJECT_0)
	{
		if (ret == WAIT_TIMEOUT) return false;
		THROW("JoinImp fail", BadThread);
	}
	m_joined = true;

	return true;
}


void Thread::Join()
{
	JoinImp(INFINITE);
}


bool Thread::JoinTry()
{
	return JoinImp(0);
}

bool Thread::JoinTimeout(float _interval)
{
	DWORD timeCon = static_cast<DWORD>(_interval*1000);
	return JoinImp(timeCon);
}



void Thread::Cancel()
{
    assert(!m_joined);
	Lock lock(m_mutex);

	DWORD ret = TerminateThread(
		m_thread, //  HANDLE hThread
		0         //	DWORD dwExitCode
		);

	CHECK_AND_THROW_EQ( ret, 0 ,"Cancel", BadThread);
	m_joinable = 0;
}

void Thread::Detach()
{
    assert(!m_joined);
	Lock lock(m_mutex);
	DWORD ret = CloseHandle(m_thread);
	CHECK_AND_THROW_EQ( ret, 0 ,"Detach", BadThread);

    m_joinable = false;
}


//static 
DWORD Thread::Runner(LPVOID _params)
{
    Thread* t = static_cast<Thread*> (_params);

    try{
        (*t->m_run)();
    }
    catch (...)
    {
    	//write to stderr (fprintf(stderr, "  " ) )
    }

	return 0;
}

// bool Thread::JoinTimeoutAbs( Time _abstime){}
