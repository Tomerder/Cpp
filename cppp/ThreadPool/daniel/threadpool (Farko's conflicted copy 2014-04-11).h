
//use tr1 shared pointer, not ours!
//threadpool creates initiale number of threads given in ctor
//Put - user's API to send new runnables - tasks
//GetAssignment - Thread's api to ask from thread pool a new task

//every thread is born with the ruunable function that tells him to go repititly to GetAssignment
// and ask for a new task
//while()
//r = priorityQueue.GetAssignment;
//r();

//for a GracefullShutDown thread pool will insert AOF messages to the queue.
//insert tasks with the lowest priority (priprity = 5 in my case. 1-4 is for user's use - enum)
//so after all the tasks inserted to the queue are handles, the thread will take an AOF message that will kill him

//i didn't really understand what he wanted us to do with the ImmidiateShutDown, but i think the rest is enough for today!! =)

#ifndef THREADPOOL_H
#define THREADPOOL_H

#include "priorityqueue.h"
#include "thread.h"

typedef enum Priority {PRI_URGENT = 1, PRI_HIGH, PRI_MED, PRI_LOW}

class ThreadPool
{
    public:
        ThreadPool(size_t _nThreads);
        ~ThreadPool();
        Put (ruunable)
        size_t GetThreadsNum () const;
        void SetThreadsNum (size_t _nThreads);

        //lets threads finish all tasks in queue and than canceles them
        GracefullShutDown ()

        //cancle threads immidiatly
        ImmidiateShutDown

    private:
        size_t m_nThreads;
        PriorityQueue m_queue;

         GetAssignment ();
};

#endif // THREADPOOL_H


