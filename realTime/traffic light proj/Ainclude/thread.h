// thread.h
//
//
//    Author: Vladimir Krapp
//    Created on: 2014-04-08
//    Last modified:

#ifndef __THREAD_H__
#define __THREAD_H__



#ifdef WINDOWS
#include <windows.h>	// for thread implementation
#else
#include <pthread.h>	// for thread implementation
#endif

#include "runnable.h"
#include "utility.h"

#ifdef WINDOWS
	typedef DWORD ThreadID;
#else
    typedef pthread_t ThreadID;
#endif // WINDOWS

//====================================================================


class ThreadException : public std::runtime_error
{
public:
	ThreadException(std::string _msg):runtime_error(_msg){};
};


class Thread
{
    enum Status {DETACHED, NOT_RUNNING, RUNNING};


public:

		
        explicit Thread(Runnable* r, bool _startDetached = false);


        ~Thread();


		//=== void Join() ===
		// Wait for the Thread to finish execution
		// Exceptions: 
		//		throws ThreadException if an error is encoutered
        void Join();


		//=== int Join(int _milliseconds) ===
		// Wait for the Thread to finish execution, with timeout
        // 
		// 
		// Output and Exceptions:
		//		returns 0 if successful
		//		returns 1 if timed out
		//		throws ThreadException if an error is encoutered
        int Join(int _milliseconds);

		//=== void Detach() ===
		// Detach the executing thread from the Thread object. 
		// Execution will continue after Thread object is destroyed
        void Detach();

		//=== void Cancel() ===
		// Cancels the execution of the thread
		// 
        void Cancel();

		//=== ThreadID GetID() ===
		// Returns the identifier of the thread
        ThreadID GetID() const;



private:

#ifdef WINDOWS
		static DWORD RunRoutine(LPVOID _run);
		HANDLE m_thread;
		DWORD m_threadID;
#else
		static void* RunRoutine(void* _th);
        pthread_t m_thread;
#endif // WINDOWS

        Runnable* m_routine; // runnable
        Status m_status;

}; // class Thread





#endif //__THREAD_H__

