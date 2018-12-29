/************************************************************************
Thread
Author: Dan Bar-On.
Creation Date: 23.04.14 
Modified at:
Description: Provides API for thread. Thread is thread-safe.
************************************************************************/
#ifndef THREAD_H
#define THREAD_H

#include "uncopyable.h"
#include "runnable.h"
#include "mutex.h"

#ifdef WIN32 
#include <windows.h>
#include "stdafx.h"
typedef DWORD ThreadId;
#elif UNIX
#include <pthread.h>
#include "mytime.h"	//Time
typedef pthread_t ThreadId;
#endif




class MULTITHREADING_API Thread: private Uncopyable{
public:
	explicit Thread(RunShared, bool _joinable = true);
    ~Thread();

	// All these functions throw BadThread
	void Join();
	bool JoinTimeout(float _interval);

	#ifdef UNIX
	bool JoinTimeoutAbs( Time _abstime); //not implemented in windows
	#endif // #ifdef UNIX

	bool JoinTry();	
	void Cancel();
	void Detach();
	
	inline ThreadId GetId();

private:

#ifdef WIN32
	HANDLE m_thread;
	DWORD m_id;
	bool JoinImp(DWORD _miliSec);
	static DWORD Runner(LPVOID _params);
	RunShared m_run;
#elif UNIX
	ThreadId m_thread;
	static void* Runner(void* _params);
	RunShared m_run;
#endif

	bool m_joinable;
    bool m_joined;
    Mutex m_mutex;
};

ThreadId Thread::GetId()
{
#ifdef WIN32
	return m_id;
#elif UNIX
	return m_thread;
#endif
}

// unify shared pointer definition for UNIX and WINDOWS

#ifdef WIN32 
#include <memory>	//shared_ptr
typedef std::shared_ptr<Thread> ThreadShared;
EXPIMP_TEMPLATE template class MULTITHREADING_API std::shared_ptr<Thread>;
#elif UNIX
#include <tr1/memory>	//shared_ptr
typedef std::tr1::shared_ptr<Thread> ThreadShared;
#endif


#endif // THREAD_H

