#ifndef __LOCKING_PRIORITY_QUEUE_H__
#define __LOCKING_PRIORITY_QUEUE_H__

#include <queue>

#include "mutex.h"
#include "semaphore_m10.h"

#include "utility.h"


// 
template<class T, class SEQ = std::vector<T>,
	   class CMP = std::less<T> >
class PriorityQueue : private Uncopyable
{
public:

    //CTOR
    PriorityQueue();

    // Insert an item into the queue.
    void Push(T t);

    // Extract an item from the queue. 
    // If queue is empty, thread will block until an item is
    // available.
    T Pop();

    bool Empty() const;


private:

    std::priority_queue<T, SEQ, CMP> m_queue;

    Mutex     m_mtx; // Lock access while operating on the queue

    Semaphore m_items; // 

}; // class PriorityQueue




template <class T, class SEQ, class CMP>
PriorityQueue<T, SEQ, CMP>::PriorityQueue()
:m_items(0)
{
    //ctor
}

template <class T, class SEQ, class CMP>
void 
PriorityQueue<T, SEQ, CMP>::Push(T t)
{
    {
        Lock _(m_mtx);
        m_queue.push(t);
    }

    m_items.Up();
}

template <class T, class SEQ, class CMP>
T 
PriorityQueue<T, SEQ, CMP>::Pop()
{
    m_items.Down();

    Lock _(m_mtx); // will unlock in Dtor

    T tReturn = m_queue.top();
    m_queue.pop();

    return tReturn;
}


template <class T, class SEQ, class CMP>
bool
PriorityQueue<T, SEQ, CMP>::Empty() const
{
    return m_queue.empty();
}












#endif // __LOCKING_PRIORITY_QUEUE_H__
