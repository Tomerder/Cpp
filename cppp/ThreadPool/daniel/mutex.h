// Linux Implementation
// Non recursive mutex

#ifndef __MUTEX_H__
#define __MUTEX_H__

#include <pthread.h>

namespace m10
{

class Lock;

class Mutex
{
public:
    Mutex();
    ~Mutex();
    void Lock();
    void Unlock();

private:
    pthread_mutex_t m_mut;
};

class Lock
{
public:
    Lock(Mutex& mutex);
    ~Lock();
private:
    Mutex& m_mut;
};

}
#endif // __MUTEX_H__
