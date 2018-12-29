#ifndef __PRIORITYQUEUE_H__
#define __PRIORITYQUEUE_H__

#include <queue>

#include "semaphore.h"
#include "mutex.h"

namespace m10
{

template <class T> //T must implement operator<
class PriorityQueue
{
public:
    PriorityQueue() {}
    void Push(const T& val);
    T Pop();

private:
    PriorityQueue(const PriorityQueue& other);
    PriorityQueue& operator=(const PriorityQueue& other);

    std::priority_queue<T> m_q;
    Semaphore m_sem;
    Mutex m_lock;
};

template <class T>
void PriorityQueue<T>::Push(const T& val)
{
    {
        Lock lock(m_lock);
        m_q.push(val);
    }
    m_sem.Up();
}

template <class T>
T PriorityQueue<T>::Pop()
{
    T ret;
    m_sem.Down();
    {
        Lock lock(m_lock);
        ret = m_q.top();
        m_q.pop();
    }
    return ret;
}




}
#endif // __PRIORITYQUEUE_H__
