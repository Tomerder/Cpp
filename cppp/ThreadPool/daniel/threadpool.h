#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <list>
#include <map>
#include <tr1/memory>

#include "priorityqueue.h"
#include "thread.h"
#include "runnable.h"
#include "mutex.h"

namespace m10
{

typedef enum Priority {PRI_STUB_LAST = 0, PRI_LOW, PRI_MED, PRI_HIGH, PRI_URGENT, PRI_STUB_FIRST} Priority;
typedef unsigned long ulong_t;
typedef std::tr1::shared_ptr<Thread> shPtrThrd_t;
typedef std::tr1::shared_ptr<Runnable> shPtrRunbl_t;
typedef std::list<shPtrThrd_t>::iterator listItr_t;
typedef std::map<ulong_t, listItr_t>::iterator mapItr_t;


struct PqPair;

class ThreadPool
{

public:
    explicit ThreadPool(size_t nThreads);
    ~ThreadPool();
    void AddTask (shPtrRunbl_t run, Priority priority);
    size_t GetThreadsNum() const;
    void SetThreadsNum (size_t nThreads);
    void GracefullShutDown();
    void ImmidiateShutDown(ulong_t sec = 0);


private:
    shPtrRunbl_t GetTask ();
    void RunTasks();
    void CleanGarbage();

    size_t m_nThreads;
    PriorityQueue<PqPair> m_tasks;
    std::list<shPtrThrd_t> m_threads;
    std::map<ulong_t, listItr_t> m_IdToIter;
    std::list<listItr_t> m_threadsToBeRemoved;
    Mutex m_listLock;
    MemberFuncWrapper<ThreadPool, &ThreadPool::RunTasks> m_runWrapper;

};




}
#endif // THREADPOOL_H


