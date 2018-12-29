// semaphore.h
//
//	Platform independent semaphore class
//	Author: Vladimir Krapp
//	Created on: 7/4/14
//	Last modified:

#ifndef __GENERIC_SEMAPHORE_H__
#define __GENERIC_SEMAPHORE_H__

#ifdef WINDOWS
#include <windows.h> // for windows semaphore
#else
#include <semaphore.h> // for sem_t
#endif // WINDOWS


#include <stdexcept>    // for runtime_error
#include <string>   // for std::string

#include "utility.h"    // for various utilities


#define SEM_MAX_VAL MAXSHORT



// Exception thrown by the Semaphore class in case of error
class SemException : public std::runtime_error
{
public:
	SemException(std::string _msg);
};




class Semaphore : private Uncopyable
{
public:
    enum SharingPolicy{THREADS = 0, PROCESS = 1};


    /*** Semaphore() ***********************************************/
    // CTOR
    //
    // Arguments: 	_count				- initial semaphore value
	//				_processSharable	- allow the semaphore to be shared 
	//									between different processes, LINUX ONLY!
    // 				
    // Result and Exceptions:
    // 	on failure:	throws SemException
    explicit Semaphore(unsigned int _count, SharingPolicy _processSharable = THREADS);

    /*** ~Semaphore ***********************************************/
    // DTOR
    // 				
    // Result and Exceptions:
	//		doesn't throw exceptions
    ~Semaphore();

	/*** Up() ***********************************************/
    // Increase the semaphore value by one
    //
    // Result and Exceptions:
    // 	on failure:	
	//		throws SemException
    void Up();

	/*** Down() ***********************************************/
    // Decrease the semaphore value by one. If current semaphore value is 0, 
	// process will block untill semaphore is raised by another process
    //
    // Result and Exceptions:
    // 	on failure:	
	//		throws SemException
    void Down();


private:    
	
#ifdef WINDOWS
	HANDLE m_sem;
#else
	sem_t m_sem;
#endif // WINDOWSs

};// class Semaphore



#endif //__GENERIC_SEMAPHORE_H__
