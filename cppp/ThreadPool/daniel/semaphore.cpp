#include <semaphore.h>
#include <stdexcept>

#include "semaphore.h"

namespace m10
{


Semaphore::Semaphore(unsigned int initialVal, bool shareProcesses)
{
    if (sem_init(&m_sem, shareProcesses, initialVal) == -1)
    {
        throw std::runtime_error("Fail to create Semaphore");
    }
}

Semaphore::~Semaphore()
{
    sem_destroy(&m_sem);
}

void Semaphore::Up()
{
    if (sem_post(&m_sem) == -1)
    {
        throw std::runtime_error("Fail to perform Semaphore::Up");
    }
}

void Semaphore::Down()
{
    if (sem_wait(&m_sem) == -1)
    {
        throw std::runtime_error("Fail to perform Semaphore::Down");
    }
}


}
