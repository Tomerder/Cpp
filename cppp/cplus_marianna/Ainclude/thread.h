/**************************************************************************************
    Author: Marianna Shvartsman
    Creation date :      2013-11-17
    Last modified date: 2013-11-22
    Description : Thread
***************************************************************************************/
#ifndef __THREAD_H__
#define __THREAD_H__

#include <iostream>
using namespace std;

#include "uncopyable.h"
#ifdef __LINUX
#include "timespecExtension.h"
#else
#include <windows.h>
#endif
//Class Thread will implement thread depends on OS the program is running on( Linux or Windows)
//F is a function (or functor) that thread will to execute

//EXAMPLE:
//	Thread<ClientFunc> thr(_clientFunc);
//	thr.Wait(100);
namespace multithreading_m7
{

template <class F> //F requirement operator()
class Thread : private Uncopyable
{
	public:
		explicit	 Thread(F _func);
					~Thread();
		//returns true if thread terminated before timeout expired
		//returns false if timeout expired
		//use timeout = 0 if you want -to check if task is finished
		bool	 Wait(size_t timeout)const throw(char*); //Join

	private:
		F 			m_func;
#ifdef __LINUX
		pthread_t	m_thread;
		//internal function uses to unix thread implementation
		// _param is clientFuction
		static void* Function(void* _param);
#else
		DWORD  m_threadID;
		HANDLE m_handle;
		static DWORD WINAPI Function(LPVOID _param);
#endif
};


//------------------------------------------------------------------
//		CTOR
//------------------------------------------------------------------
template <class F>
Thread<F>::Thread(F _func):m_func(_func)
{

#ifdef __LINUX
	pthread_create(&m_thread , 0, Function, &m_func);
#else 	//windows
	m_handle = CreateThread(NULL, 0, Function,static_cast<LPVOID>(&m_func), 0, &m_threadID);
#endif;
}
//------------------------------------------------------------------
//		DTOR
//------------------------------------------------------------------
template<class F>
Thread<F>::~Thread()
{
#ifdef __LINUX
	pthread_cancel(m_thread);

#else //windows
	TerminateThread(m_handle, 0);
	CloseHandle(m_handle);
#endif
}
//------------------------------------------------------------------
//		WAIT == JOIN
//------------------------------------------------------------------
template <class F>
bool	 Thread<F>::Wait(size_t _timeout)const throw(char*)
{
#ifdef __LINUX
	timespec deadline;
	
	TimeSpecExtension::Msec2DeadLine(_timeout,&deadline);

	//calls specific join/wait depend OS function
	if (pthread_join(m_thread,0))
	{
		throw "Thread wait faild!";
	}
	
	timespec now;
	TimeSpecExtension::GetCurrentTime(&now);
	
	//if timeout expired returns false, else true
	return TimeSpecExtension::TimeSpec2DeadLine(&deadline, &now);
#else
	DWORD s=WaitForSingleObject(m_handle, _timeout);

	if (s != 0)
           throw "waitForSingleObject";
	return !s;	
#endif


}
//------------------------------------------------------------------
//		Function
//------------------------------------------------------------------
template <class F>
#ifdef __LINUX
void* Thread<F>::Function(void* _param)
#else
 DWORD WINAPI Thread<F>::Function(LPVOID _param)
#endif
{
	//running client function
	(*static_cast<F*>(_param))();

	return 0 ;
}

} //end namespace
#endif

