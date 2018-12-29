#include <iostream>
#include <cmath>	//abs
#include <unistd.h>
#include <cstdio>

#include "threadpool.h"
#include "runnable.h"
#include "mytime.h"
#include "myexceptions.h"	//BadThreadPool

using namespace std;
using namespace std::tr1;

//==========================================================================================

Threadpool::Threadpool(size_t _numThreads):
m_shutDown(false),
m_wasImidiateShutdown(false),
m_runner(new MemberMethodRun<Threadpool,&Threadpool::GetTask>(*this)),
m_poison(new PoisionApple())
{
    AddThreads(_numThreads);
}
//==========================================================================================
void Threadpool::AddThreads(unsigned int _numThreads)
{
	Lock lock (m_mutex);
    for (unsigned int i = 0; i < _numThreads; ++i)
    {
        shared_ptr<Thread> t(new Thread(m_runner, true));
        m_threads.insert(pair<ThreadId,shared_ptr<Thread> >(t->GetId(), t));
    }
}
//==========================================================================================
Threadpool::~Threadpool()
{
    if (!m_shutDown)
    {
        GracefullShutdown();
    }

//    while (!m_threads.empty())
//	{
//	    sleep(0);
//	}
}
//==========================================================================================
void Threadpool::AddTask( std::tr1::shared_ptr<Runnable> _run, Priority _priority)
{
	CHECK_AND_THROW_EQ(m_shutDown, true,"Adding tasks after shutdown", BadThreadPool);
    AddTaskImp(_run, _priority);
}
//==========================================================================================
void Threadpool::AddTaskImp( std::tr1::shared_ptr<Runnable> _run, int _priority)
{
    m_pq.Push( PqPair(_priority, _run));
}
//==========================================================================================
void Threadpool::SetThreadNum(unsigned int _num)
{
    int dif = _num - m_threads.size();
	
    if (dif > 0)
    {
        AddThreads(dif);
    }
    if (dif < 0)
    {
        SendPoisonApples(abs(dif), PRI_URGENT + 1 );
    }
    
    CleanDeadThreads();
}
//==========================================================================================
void Threadpool::GetTask()
{
    while (!m_wasImidiateShutdown)
    {
        PqPair p = m_pq.Pop();
		
		if (typeid(*p.m_run) == typeid(*m_poison)) 
		{
			Lock lock(m_mutex);
			map<ThreadId, shared_ptr<Thread> >::iterator it = m_threads.find(pthread_self() );
			m_threadsTokill.push_back(it->second);
			
			m_threads.erase(it);
			if (m_threads.empty() )
			{
				m_waitShutDown.Up();
			}

			return;
		}
        try
        {
            (*p.m_run)();
        }
        catch(...)
        {
        	//write to stderr
        }
    }
}
//==========================================================================================
void Threadpool::GracefullShutdown()
{
    m_shutDown = true;
	SendPoisonApples(m_threads.size(),  PRI_LOW - 1);  //service function

	// wait for last thread to finish
	m_waitShutDown.Down();

	// usually loop happens onlt once, hence there's no need to use synchronization tools.
	while (!m_threadsTokill.empty())
	{
		CleanDeadThreads();
		sleep(0);
	}
}
//==========================================================================================
bool Threadpool::ImidiateShutdown(float _timeout)       // _timeout in seconds
{
	CHECK_AND_THROW_EQ(m_shutDown, true,"ImidiateShutdown after shutdown", BadThreadPool);

	bool timeoutNotReached = true;
	m_wasImidiateShutdown = true;
	m_shutDown = true;

	// release threads waiting on pop.
	//	SendPoisonApples(m_threads.size() , PRI_URGENT + 1 ); 
	
    Time absTIme(_timeout);
    absTIme.AddNowToGetAbsTime();

	{
		Lock lock(m_mutex);
		map<ThreadId,shared_ptr<Thread> >::iterator it = m_threads.begin();

		for (; it != m_threads.end(); ++it )
		{
			if ( (*(it->second)).JoinTimeoutAbs(absTIme) == false )
			{
				timeoutNotReached = false;
				(*(it->second)).Cancel();
			}
		}
	}
    
    CleanDeadThreads();
	m_threads.clear();

	return timeoutNotReached;
}
//==========================================================================================
void Threadpool::SendPoisonApples(unsigned int _num, int _priority)   //service function
{
    for (unsigned int i = 0; i < _num; ++i)
    {
        AddTaskImp(m_poison, _priority);
    }
}
//==========================================================================================
void Threadpool::CleanDeadThreads()
{
	Lock lock(m_mutex);
	vector<std::tr1::shared_ptr<Thread> >::iterator it = m_threadsTokill.begin();
	
	while ( it != m_threadsTokill.end() )
	{
		if ( (*it)->JoinTry() )
		{	
			it = m_threadsTokill.erase(it);
		}	
		else 
		{
			++it;
		}
	}
}





