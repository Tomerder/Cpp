#include <climits>	//SHRT_MAX

#include "myexceptions.h"	//BadSem
#include "semaphoremy.h"

Semaphore::Semaphore(unsigned int _initVal, bool _forProccesses)
{
	 m_sem = CreateSemaphore( 
        NULL,			// default security attributes
        _initVal,		// initial count
        SHRT_MAX,		// maximum count
        NULL);          // unnamed semaphore

	 	CHECK_AND_THROW_EQ( m_sem, 0 ,"Semaphore CTOR", BadSem);
}

Semaphore::~Semaphore()
{
    CloseHandle(m_sem);
}

void Semaphore::Up()
{
	DWORD ret = ReleaseSemaphore( 
                        m_sem,		  // handle to semaphore
                        1,            // increase count by one
                        NULL);       // not interested in previous count
	CHECK_AND_THROW_EQ(ret, 0 ,"Semaphore Up", BadSem);
}

void Semaphore::Down()
{
	DWORD ret = WaitForSingleObject( 
            m_sem,		// handle to semaphore
            INFINITE);	// timeout (infinite)

	CHECK_AND_THROW_DIF(ret, WAIT_OBJECT_0 ,"Semaphore Dwon", BadSem);
}

