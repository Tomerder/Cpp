/************************************************************************
Threadpool
Author: Dan Bar-On.
Creation Date: 23.04.14 
Modified at:
Description: Takes tasks(runnables) and runs them in seperate threads.
************************************************************************/
#ifndef THREADPOOL_H
#define THREADPOOL_H


#ifdef WIN32
#pragma warning(push)
#pragma warning(disable : 4251)

#ifdef THREADPOOL_EXPORTS
#define THREADPOOL_API __declspec(dllexport)
#define EXPIMPT_TEMPLATE
#else
#define THREADPOOL_API __declspec(dllimport)
#define EXPIMPT_TEMPLATE extern
#endif	// THREADPOOL_EXPORTS

#elif UNIX
#define THREADPOOL_API
#endif	//#ifdef WIN32



#include <map>
#include <vector>

#include "thread.h"
#include "mutex.h"
#include "priorityqueue.h"
#include "uncopyable.h"
#include "semaphoremy.h"



class THREADPOOL_API Threadpool: private Uncopyable
{
public:
    explicit Threadpool(size_t _numThreads);
    ~Threadpool();

	enum Priority{ PRI_LOW = 1, PRI_MED, PRI_HIGH, PRI_URGENT };
    void AddTask( RunShared, Priority _priority);	//throw exception if was shutdown

    void SetThreadNum(unsigned int _num);	//  Not blocking. Will close threads at the end of task.
    inline unsigned int GetThreadNum() const;

    void GracefullShutdown();
	
	// _timeout in seconds. Let threads complete current tasks.
	// Return if timeout reached or everything is done
    bool ImidiateShutdown(float _timeout);

private:
	struct PqPair
	{
		inline PqPair(int _pri, RunShared _run);
		int m_priority;
		RunShared m_run;
		inline bool operator<(const PqPair& _rhs) const;
	};

    WaitablePQueue<PqPair> m_pq;
    std::map<ThreadId,ThreadShared >	m_threads;
    std::vector<ThreadShared >			m_threadsTokill;
    void CleanDeadThreads();
    
    void GetTask();		// runnable who runs runnables provided by the user
    Mutex m_mutex;
	Semaphore m_waitShutDown;

    bool m_shutDown;	//Up the semaphore before shutdown // Change name to wasShutDown or something
	bool m_wasImidiateShutdown; 	// wait for last thread to finish
    
	RunShared m_runner;

    void AddTaskImp( RunShared _run, int _priority);
    void AddThreads(unsigned int _num);       				   //service function
    void SendPoisonApples(unsigned int _num, int _priority);   //service function

    class PoisionApple: public Runnable
	{
		void operator()(){};
	};
    class GoodApple: public Runnable
	{
		void operator()(){};
	};
	RunShared m_poison;
	RunShared m_goodApple;

};


unsigned int Threadpool::GetThreadNum() const
{
	return m_threads.size();
}

Threadpool::PqPair::PqPair(int _pri, RunShared _run)
:m_priority(_pri), m_run(_run){}

bool Threadpool::PqPair::operator<(const PqPair& _rhs) const
{
	return m_priority < _rhs.m_priority;
}


#ifdef WIN32
#pragma warning(pop)
#endif // #ifdef WIN32

#endif // THREADPOOL_H	
