/**************************************************************************************
    Author: Marianna Shvartsman
    Creation date :      2013-11-17
    Last modified date: 2013-11-17
    Description :  WaitableQ
***************************************************************************************/
#ifndef	__WAITABLEQ_H__
#define __WAITABLEQ_H__

#include <queue>
#include <vector>
#include <functional>

#include <iostream>
using namespace std;

#include "uncopyable.h"
#include "sync.h"
#ifdef __LINUX
#include "timespecExtension.h"
#endif

namespace multithreading_m7
{

//Description:
//	  WaitableQ implements a priority queue with waiting(with timeout) on empty Q for element
//    Pop is blocking call

//Example:
//	WaitableQ queue(cmpFunc);
//	queue.Push(element);
//  queue.Pop(&popElement, timeout ) 

template<class T, class IsBefore = bool(*)(const T&, const T&)>
class WaitableQ : private Uncopyable
{
	public:
		explicit	WaitableQ(IsBefore _isBefore)throw(char*);
				~WaitableQ()throw(char*);
				
				//throw exeption if allocation faild
		void	Push(const T& _t)throw(char*);
		 		// wait on Q with timeout
		 		//returns true if successed to pop element
		 		//false if timeout expired
		 		// TIMEOUT_FOREVER = waiting without timeout
		bool	Pop(T* _t, size_t _timeout = TIMEOUT_FOREVER)throw(char*);
		bool	IsEmpty()const;

	private:
		Mutex				m_mutex;
		CondVar 			m_cond;
		
		std::priority_queue<T,std::vector<T>, IsBefore>	m_queue;

};

//-----------------------------------------------------
//			CTOR:
//				Mutex and CondVar CTORs throws exeptions
//-----------------------------------------------------
template<class T, class IsBefore>
WaitableQ<T,IsBefore>::WaitableQ(IsBefore _isBefore)throw(char*):
	m_queue(_isBefore){}

//-----------------------------------------------------
//			DTOR
//-----------------------------------------------------
template<class T, class IsBefore>
WaitableQ<T,IsBefore>::~WaitableQ()throw(char*)
{
	//notify all threads waiting on empty Q wake up
	m_cond.NotifyAll();
	//DTORs of Mutex, CondVar and priority_queue
}

//-----------------------------------------------------
//			Push:
//				mutex.Lock, mutex.Unlock, cond.NotifyAll throws exeptions
//-----------------------------------------------------
template<class T, class IsBefore>
void	WaitableQ<T,IsBefore>::Push(const T& _t)throw(char*)
{
	//mutex lock
	m_mutex.Lock();
	//Push pair
	m_queue.push(_t);

	//if Q.size() == 1
	if (m_queue.size() == 1)
	{
		//condvar broadcast all
		m_cond.NotifyAll();
	}

	//mutex unlock
	m_mutex.Unlock();
}

//-----------------------------------------------------
//			Pop:
//				//mutex.Lock, mutex.Unlock, cond.Wait throws exeptions
//-----------------------------------------------------
#ifdef __LINUX
template<class T, class IsBefore>
bool	WaitableQ<T,IsBefore>::Pop(T* _t, size_t _timeout)throw(char*)
{
	//mutex lock
	m_mutex.Lock();
	//while (queue is empty)
	while(m_queue.empty())
	{
		timespec deadline;
		timespec time2end;
	
		TimeSpecExtension::Msec2DeadLine(_timeout, &deadline);

		//wait on condvar until wake up or timeout not expired
		if (!m_cond.Wait(&m_mutex, _timeout))
		{
			m_mutex.Unlock();
			return false;
		}
		
		TimeSpecExtension::TimeSpec2DeadLine(&deadline, &time2end);
		//change timeout
		_timeout = TimeSpecExtension::TimeSpec2SizeT(&time2end);
	}
	*_t = m_queue.top();
	//Pop()
	m_queue.pop();
	//mutex unlock
	m_mutex.Unlock();
	return true;
}
#else
template<class T, class IsBefore>
bool	WaitableQ<T,IsBefore>::Pop(T* _t, size_t _timeout)throw(char*)
{
	//mutex lock
	m_mutex.Lock();
	//while (queue is empty)
	while(m_queue.empty())
	{
		//wait on condvar until wake up or timeout not expired
		if (!m_cond.Wait(&m_mutex, _timeout))
		{
			m_mutex.Unlock();
			return false;
		}
		
	}
	*_t = m_queue.top();
	//Pop()
	m_queue.pop();
	//mutex unlock
	m_mutex.Unlock();
	return true;
}
#endif
//-----------------------------------------------------
//			Pop
//-----------------------------------------------------
template<class T, class IsBefore>
bool	WaitableQ<T,IsBefore>::IsEmpty()const
{
	return m_queue.empty();
}

} //end namespace
#endif

