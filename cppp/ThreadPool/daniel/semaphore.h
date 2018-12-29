// Linux Implementation

#ifndef __SEMAPHORE_H__
#define __SEMAPHORE_H__

#include <semaphore.h>

namespace m10
{

class Semaphore
{
public:
    explicit Semaphore(unsigned int initialVal = 0, bool shareProcesses = false);
    ~Semaphore();
    void Up();
    void Down();

private:
    sem_t m_sem;
};

}
#endif // __SEMAPHORE_H__
