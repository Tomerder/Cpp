/* semaphore_m10.c
*
* What's this?
*
* Author: Vladimir Krapp
* Created on:
* Last modified:
*/

#include <semaphore.h>

#include "semaphore_m10.h"


//using namespace m10;


Semaphore::Semaphore(unsigned int count, SharingPolicy _processSharable)
{
    sem_init(&m_sem, _processSharable, count);
}


 Semaphore::~Semaphore()
{
    sem_destroy(&m_sem);
}


void Semaphore::Down()
{
    sem_wait(&m_sem);
}


void Semaphore::Up()
{
    sem_post(&m_sem);
}
