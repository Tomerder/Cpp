#include <stdexcept>
#include "myexceptions.h"
#include "mutex.h"	

Mutex::Mutex()
{
	   m_mutex = CreateMutex( 
        NULL,              // default security attributes
        FALSE,             // initially not owned
        NULL);             // unnamed mutex

	CHECK_AND_THROW_EQ(m_mutex, 0 ,"Mutex CTOR", BadMutex);
}

Mutex::~Mutex()
{
	CloseHandle(m_mutex);	// TODO: if error write to log
}

void Mutex::Lock() const
{
	DWORD ret = WaitForSingleObject( 
            m_mutex,    // handle to mutex
            INFINITE);  // no time-out interval
 
	CHECK_AND_THROW_DIF(ret, WAIT_OBJECT_0, "Mutex Lock", BadMutex);
}

void Mutex::Unlock() const
{
	DWORD ret = ReleaseMutex(m_mutex);
	CHECK_AND_THROW_EQ(ret, 0, "Mutex unlock", BadMutex);
}
