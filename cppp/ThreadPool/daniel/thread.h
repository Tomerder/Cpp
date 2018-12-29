#ifndef __THREAD_H__
#define __THREAD_H__

#include <pthread.h>

#include "runnable.h"

namespace m10
{

class Thread
{
public:
    explicit Thread(Runnable& r);

    // Blocking. After a successful Join, a second call to Join will return immediately.
    void Join() const;

    //After a successful JoinTO, a second call to JoinTO will return immediately.
    int JoinTO(unsigned long sec = 0, unsigned long usec = 0) const;

    //After a successful Kill, a second call to Kill will return immediately.
    void Kill() const;

    //After a successful Deattach, a second call to Kill will return immediately.
    void Deattach() const;

    //Return the Thread's ID
    unsigned long MyID() const;

    //Return the caller's ID
    static unsigned long GetID();

    // Terminate the thread
    ~Thread();

private:
    static void* Runner(void*);
    Thread(const Thread& other);
    Thread& operator=(const Thread& other);
    pthread_t m_thread;
    mutable bool m_isAlive;
};

}
#endif // __THREAD_H__
