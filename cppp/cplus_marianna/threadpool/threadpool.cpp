/**************************************************************************************
    Author: Marianna Shvartsman
    Creation date :      2013-11-17
    Last modified date: 2013-11-17
    Description : ThreadPool implementation
***************************************************************************************/
#include <typeinfo>
#ifdef  __LINUX
#include <unistd.h>
#endif
#include <iostream>
using namespace std;

#ifdef __LINUX
#else
#include <windows.h>
#include <mmsystem.h> 
#include <memory>
#endif

#include "threadpool.h"
using namespace multithreading_m7;

#define DEFAULT_TIMEOUT 500

//--------------------------------------------------------------------------------------
//				Compare Tasks Priority function
//--------------------------------------------------------------------------------------
bool ThreadPool::CompPriority(const PriorityTaskPair& _pair1, const PriorityTaskPair& _pair2)
{
//cout << "Cmp func!!!!!" << endl;
	return (_pair1.first > _pair2.first);
}

//--------------------------------------------------------------------------------------
//				CTOR
//--------------------------------------------------------------------------------------
ThreadPool::ThreadPool(int _noThreads)throw(char*):	m_queue(CompPriority), m_threads(_noThreads), m_stopPop(false), m_stopAdd(false)
{
	// initialize WaitableQ whit cmpFunc
	// reserve place to new thread (Push 0 to the Q)

	//for on itr from begin to end
	for(ThreadItr itr = m_threads.begin(); itr != m_threads.end(); ++itr)
	{
		*itr = shared_ptr<Thread <ThreadFunctor> > (new Thread<ThreadFunctor>(ThreadFunctor(itr,this)));
	}
}

//--------------------------------------------------------------------------------------
//				Add
//--------------------------------------------------------------------------------------
//add new task to ready Q
//Priority high, medium, low.
void	ThreadPool::Add(shared_ptr<Task> _task, Priority _priority)throw(char*)
{

		//create pair <shared_ptr, priority>
		//Insert task to waitableQ according to given priority
		if(!m_stopAdd)
		{
			m_queue.Push(PriorityTaskPair(_priority,_task));
		}

}
//--------------------------------------------------------------------------------------
//				AddThreads
//--------------------------------------------------------------------------------------
//add one more thread to pool
void	ThreadPool::ChangeNumThreads(size_t _noThreads)throw(char*)
{
	size_t prevSize = m_threads.size();
	//if noThreads > list.size() add threads
	if(_noThreads > prevSize)
	{
		m_threads.resize(_noThreads);
		ThreadItr itr = m_threads.begin();
		for(size_t i = prevSize; i< _noThreads; ++i,++itr);

		for(; itr != m_threads.end(); ++itr)
		{
			*itr = shared_ptr<Thread <ThreadFunctor> > (new Thread<ThreadFunctor>(ThreadFunctor(itr,this)));
		}
	}
	else //add difference num of KillTasks with super high priority to Q
	{
		for (size_t i = 0; i < m_threads.size() - _noThreads; ++i)
		{
			shared_ptr<Task> killtask(new KillTask);
			Add(killtask,static_cast<Priority>(0));
		}
	}

}
//--------------------------------------------------------------------------------------
//		StopAlgorithm:
//					Internal use function to support variability of Stop function
//					function return timeout to the end of stop
//--------------------------------------------------------------------------------------

size_t	ThreadPool::StopAlgorithm(size_t _timeout, ThreadItr _itr, int* count)
#ifdef __LINUX
{
	timespec deadline;
	timespec time2end;

	TimeSpecExtension::Msec2DeadLine(_timeout, &deadline);

	if (!(*_itr)->Wait(_timeout))
	{
		m_threads.clear();
		return 0;
	}

	++(*count);

	TimeSpecExtension::TimeSpec2DeadLine(&deadline, &time2end);
	//after every thread had finished executing change time interval of executing
	return TimeSpecExtension::TimeSpec2SizeT(&time2end);
}
#else
{
	
	long time2die = timeGetTime() + _timeout;

	if (!(*_itr)->Wait(_timeout))
	{
		m_threads.clear();
		return 0;
	}

	++(*count);

	//after every thread had finished executing change time interval of executing
	return (timeGetTime() - time2die);
}
#endif

//--------------------------------------------------------------------------------------
//				Stop: returns num of threads exit gracefully
//--------------------------------------------------------------------------------------

int	ThreadPool::Stop(size_t _timeout, bool _shouldFinishAll)throw(char*)
{
	int count = 0; //num of threads ends gracefully

	//Up stopAdd flag and wait _timeot for finish executing task
	m_stopAdd = true;
	if(!_shouldFinishAll)
	{
		m_stopPop = true;
	}
	else
	{
		shared_ptr<Task> endtask(new EndTask);
		for(size_t i = 0; i < m_threads.size(); ++i)
		{
			m_queue.Push(PriorityTaskPair(static_cast<Priority>(4),endtask));
		}
	}

	for(ThreadItr itr = m_threads.begin(); itr !=  m_threads.end(); ++itr)
	{
		_timeout = StopAlgorithm(_timeout,itr,&count);
		if(0 == _timeout)
		{
			break;
		}
	}

	return count;

}

//--------------------------------------------------------------------------------------
//				ThreadFunctor
//--------------------------------------------------------------------------------------
ThreadPool::ThreadFunctor::ThreadFunctor(ThreadItr _threadItr, ThreadPool* _pool):
	m_placeItr(_threadItr),
	m_pool(_pool){}

//--------------------------------------------------------------------------------------
//				operator()
//--------------------------------------------------------------------------------------
void ThreadPool::ThreadFunctor::operator()()
{
	//while m_stopPop is false
	while(!m_pool->m_stopPop)
	{
		//pop task from waitableQ
		PriorityTaskPair pair;
		//if timeout was expired check the loop condition
		if (!m_pool->m_queue.Pop(&pair,DEFAULT_TIMEOUT))
		{
			continue;
		}
		//if Task is KillTask (RTTI)
		if (typeid(*(pair.second)) == typeid(KillTask) )
		{
			//Push CleanMe  to Q and die
			shared_ptr<Task> cleanMe(new CleanMe(m_placeItr,&(m_pool->m_threads)));
			//PriorityTaskPair(_priority,_task)
			m_pool->m_queue.Push(PriorityTaskPair(static_cast<Priority>(0),cleanMe));
			return;
		}

		if (typeid(*(pair.second)) == typeid(EndTask) )
		{

			return;
		}
		//execute Task
		pair.second->Do();
	}

}
//--------------------------------------------------------------------------------------
//				KillTask Do
//--------------------------------------------------------------------------------------
void ThreadPool::KillTask::Do()
{
	//Relax and take it easy
}
//--------------------------------------------------------------------------------------
//				CleanMe CTOR
//--------------------------------------------------------------------------------------
ThreadPool::CleanMe::CleanMe(ThreadItr _threadItr, ThreadList* _list):
 m_eraseItr(_threadItr), m_list(_list){}


//--------------------------------------------------------------------------------------
//				CleanMe Do
//--------------------------------------------------------------------------------------
void	ThreadPool::CleanMe::Do()
{

	//Wait to thread iterator point to it
	(*m_eraseItr)->Wait(DEFAULT_TIMEOUT);
	//Erase iterator node
	m_list->erase(m_eraseItr);
}
//--------------------------------------------------------------------------------------
//				EndTask CTOR
//--------------------------------------------------------------------------------------

void ThreadPool::EndTask::Do()
{
	//It's time to say goodbye
}
