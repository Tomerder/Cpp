/**************************************************************************************
    Author: Marianna Shvartsman
    Creation date :      2013-11-17
    Last modified date: 2013-11-17
    Description : threadpool
***************************************************************************************/
#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__

//DESCRIPTION: Provides a pool of threads that used to execute tasks
//NOTE: To use the ThreadPool your tasks MUST inharited class Task and overide function Do()  	
//DANGER: ThreadPool throws exeptions - char*
// EXAMPLE:
//			class ClientTask: public Task
//			{
//				virtual void Do(){...}
//			}
//			TreadPool pool;
//			pool.AddTask(ClientTask task1); 
//			pool.AddTask(ClientTask task2);
//			pool.Addtask(ClientTask task3);

#include <list>
#include <iterator>
#ifdef __LINUX
#include <tr1/memory>
#else
#include <windows.h>
#include <mmsystem.h> 
#include <memory>
#endif

#include "uncopyable.h"
#include "waitableq.h"
#include "thread.h"

namespace multithreading_m7
{
	using namespace std;
	using namespace std::tr1;

class Task
{
	friend class ThreadPool;
public:
	virtual ~Task (){};
protected:
	Task (){};
private:
	virtual void Do()=0;
};//End Task


class ThreadPool : private Uncopyable 
{
friend class ThreadFunctor;
public:
	explicit ThreadPool (int _noThreads)throw(char*);
			//~ThreadPool(); generated DTOR is good enough
	enum Priority{HIGH = 1,MEDIUM = 2,LOW = 3};
	//add new task to ready Q
	//Priority high, medium, low.
	void	Add(shared_ptr<Task> _task, Priority _level)throw(char*);
	//add one more thread to pool
	void	ChangeNumThreads(size_t noThreads)throw(char*);
	
	 //ends ThreadPool work after current executeble task or 
	 //waiting for all tasks end executing.
	 //returns true if tasks ended before timeout expired.
	int	Stop(size_t _timeout, bool _shouldFinishAll)throw(char*);
	
private:
	typedef pair<Priority,shared_ptr<Task> > PriorityTaskPair;
	//data members
	WaitableQ<PriorityTaskPair>			m_queue;
	class ThreadFunctor;
	typedef 	list< shared_ptr<Thread<ThreadFunctor> > > ThreadList;
	ThreadList							m_threads;										
	
	bool								m_stopPop; //stoppable version
	bool								m_stopAdd; //finishable version
	
	//Cmpare fuction to provide executing tasks by priority
	static bool CompPriority(const PriorityTaskPair& _pair1, const PriorityTaskPair& _pair2);
	
	typedef ThreadList::iterator ThreadItr;
	//Internal use function to support variability of Stop function
	//function return timeout to the end of stop
	size_t	StopAlgorithm(size_t _timeout, ThreadItr _itr, int* count);
	
	//********************************************************************
	//				Functor definition
	//*********************************************************************
	
	class ThreadFunctor
	{
	public:
		explicit	ThreadFunctor (ThreadItr _itr,ThreadPool* _pool);
		void		operator()();
	private:
			ThreadItr								m_placeItr;
			ThreadPool*								m_pool;
		
	};//end threadFunctor
	

	//********************************************************************
	//				KillTask definition
	//********************************************************************* 
	class KillTask : public Task 			// If you execute me , die!!!	
	{
		//end while loop of Functor 
		//add to Q Task Clean(m_placeItr)		
		virtual	void	Do();
	};//end kill task

	//********************************************************************
	//				CleanMe definition
	//********************************************************************* 		
	class CleanMe : public Task
	{
	public:
		explicit CleanMe(ThreadItr _thrItr,ThreadList* _list);		// erase the thread from  List
	private:
		virtual void	Do();
		ThreadItr		m_eraseItr;
		ThreadList*		m_list;
	};//end CleanMe
	
	//********************************************************************
	//				EndTask definition
	//********************************************************************* 		
	class EndTask : public Task 	
	{
		//end thread 		
		virtual	void	Do();
	};//end end task
	 
};//end ThreadPool

} //end namespace multithreading_m7

#endif //__THREADPOOL_H__

