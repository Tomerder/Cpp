#include <tr1/memory>
#include <iostream>
#include <list>
#include <unistd.h>
#include <exception>

#include "threadpool.h"
#include "priorityqueue.h"

using namespace std;

namespace m10
{


struct PqPair
{
    PqPair (shPtrRunbl_t run, Priority priority):   m_run(run),
                                                    m_priority(priority) {}
    PqPair(): m_priority(PRI_LOW) {}
    bool operator < (const PqPair& other) const
    {
        return m_priority < other.m_priority;
    }

    shPtrRunbl_t m_run;
    int m_priority;
};

class ExceptionStopThread: public exception
{
public:
        ExceptionStopThread(ulong_t id): m_id(id) {}
        ulong_t m_id;
        bool gracefull;
};



class BadApple: public Runnable
{
public:
    BadApple(){}
    virtual void operator()();
};

void BadApple::operator()()
{
    throw ExceptionStopThread(Thread::GetID());
}




void ThreadPool::RunTasks()
{
    try
    {
        while (1)
        {
            (*GetTask())();
        }
    }
    catch (ExceptionStopThread e)
    {
        Lock lock(m_listLock);
        listItr_t inThreadsList = m_IdToIter[e.m_id];
        m_threadsToBeRemoved.push_back(inThreadsList);
        return;
    }
    catch(...)
    {
        throw;
    }
}

ThreadPool::ThreadPool(size_t nThreads): m_nThreads(0), m_runWrapper(*this)
{
    SetThreadsNum(nThreads);
}

ThreadPool::~ThreadPool()
{
    CleanGarbage();

    listItr_t itrEnd = m_threads.end();
    for (listItr_t itr=m_threads.begin(); itr != itrEnd; ++itr)
    {
        (*itr)->Kill();
    }
    m_nThreads = 0;
    m_threads.clear();
    m_threadsToBeRemoved.clear();
    m_IdToIter.clear();
}

void ThreadPool::AddTask(shPtrRunbl_t run, Priority priority)
{
    m_tasks.Push(PqPair(run, priority));
}

size_t ThreadPool::GetThreadsNum() const
{
    return m_nThreads;
}

shPtrRunbl_t ThreadPool::GetTask ()
{
    return m_tasks.Pop().m_run;
}

void ThreadPool::SetThreadsNum (size_t nThreads)
{
    // Add more threads
    if (m_nThreads < nThreads)
    {
        for (size_t i=m_nThreads; i<nThreads; ++i)
        {
            Thread* thread = new Thread(m_runWrapper);
            listItr_t inList = m_threads.insert(m_threads.begin(), shPtrThrd_t(thread));
            m_IdToIter[thread->MyID()] = inList; // overwrite existing data
        }
        m_nThreads = nThreads;
        return;
    }

    // Remove threads
    for (int toBeRemoved=m_nThreads-nThreads; toBeRemoved>0; --toBeRemoved)
    {
        AddTask(shPtrRunbl_t(new BadApple), PRI_STUB_LAST);
    }

    CleanGarbage();
}

void ThreadPool::CleanGarbage()
{
    for (list<listItr_t>::iterator itr = m_threadsToBeRemoved.begin(),
         itrEnd = m_threadsToBeRemoved.end();
         itr != itrEnd;
         itr = m_threadsToBeRemoved.begin())
    {
        m_listLock.Lock();
        (**itr)->Join(); // join a dead thread
        m_threads.erase(*itr);
        m_threadsToBeRemoved.erase(itr);
        --m_nThreads;
        m_listLock.Unlock();
    }
}


void ThreadPool::GracefullShutDown()
{
    for (int toBeRemoved=m_nThreads; toBeRemoved>0; --toBeRemoved)
    {
        AddTask(shPtrRunbl_t(new BadApple), PRI_STUB_LAST);
    }

    while (m_nThreads)
    {
        sleep(0);
        CleanGarbage();
    }
}

void ThreadPool::ImmidiateShutDown(ulong_t sec)
{
    for (int toBeRemoved=m_nThreads; toBeRemoved>0; --toBeRemoved)
    {
        AddTask(shPtrRunbl_t(new BadApple), PRI_STUB_FIRST);
    }

    if (sec)
    {
        sleep(sec);
    }

    CleanGarbage();

    listItr_t itrEnd = m_threads.end();
    for (listItr_t itr=m_threads.begin(); itr != itrEnd; ++itr)
    {
        (*itr)->Kill();
    }
    m_nThreads = 0;
}




}
