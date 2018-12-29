/************************************************************************
Waitable Priority Queue
Author: Dan Bar-On.
Creation Date: 23.04.14 
Modified at:
Description: This priority queue is thread safe.
************************************************************************/
#ifndef WaitablePQueue_H
#define WaitablePQueue_H

#include <queue>          // std::priority_queue
#include <vector>         // std::vector

#include "mutex.h"
#include "semaphoremy.h"
#include "uncopyable.h"

template <class T, class CMP = std::less<T> >
class WaitablePQueue: private Uncopyable
{
public:

    void Push(const T& _val);	//throws bad_alloc
    T Pop();            // if empty - waits
    bool Empty() const; // Not safe!

private:
    std::priority_queue<T, std::vector<T>, CMP> m_pq;
    Mutex m_mutex;
    Semaphore m_sem;
};

template <class T, class CMP>
void WaitablePQueue<T,CMP>::Push(const T& _val)
{
    {
        Lock lock(m_mutex);
        m_pq.push(_val);	// might throw an exception - bad_alloc
    }
    m_sem.Up();
}

template <class T, class CMP>   // When poping the end - undefined behavior
T WaitablePQueue<T,CMP>::Pop()
{
    m_sem.Down();
    Lock lock(m_mutex);
    T tcopy = m_pq.top();
    m_pq.pop();

    return tcopy;
}

template <class T, class CMP>
bool WaitablePQueue<T,CMP>::Empty() const
{
    Lock lock(m_mutex);
    bool ret = m_pq.empty();
    return ret;
}

#endif // WaitablePQueue_H
