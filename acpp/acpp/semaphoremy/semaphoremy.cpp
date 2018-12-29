#include <pthread.h>

#include "semaphoremy.h"
#include "myexceptions.h"	//BadSem

Semaphore::Semaphore(unsigned int _initVal, bool _forProccesses)
{
	CHECK_AND_THROW_EQ(sem_init( &m_sem, (int)_forProccesses, _initVal), -1 ,"Semaphore CTOR", BadSem);
}

Semaphore::~Semaphore()
{
	sem_destroy(&m_sem);
}

void Semaphore::Up()
{
	CHECK_AND_THROW_EQ(sem_post(&m_sem), -1 ,"Semaphore Up", BadSem);
}

void Semaphore::Down()
{
	CHECK_AND_THROW_EQ(sem_wait(&m_sem), -1 ,"Semaphore Dwon", BadSem);
}
