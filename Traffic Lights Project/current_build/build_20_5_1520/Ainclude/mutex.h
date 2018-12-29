// mutex.h
//
//	Platform independent mutex class
//	Mutex can be relocked by the owner process without blocking
//
//	Author: Vladimir Krapp
//	Created on: 7/4/14
//	Last modified:

#ifndef __GENERIC_MUTEX_H__
#define __GENERIC_MUTEX_H__



#ifdef WINDOWS
	#include <windows.h> // for windows mutex
#else
	#include <pthread.h> // for pthread_mutex
#endif // WINDOWS

#include <stdexcept>

#include "utility.h"



class MutexException : public std::runtime_error
{
public:
    MutexException(std::string _msg):std::runtime_error(_msg){};
};


class Mutex : private Uncopyable
{

public:
    
     
    /*** Mutex() ****************************************************/
    // CTOR
    //
    // Result and Exceptions:
    //      MutexException is thrown if an error is encountered.
    Mutex();


    /*** ~Mutex() ***************************************************/
    // DTOR
    // 				
    // Result and Exceptions:
    //      no throw
    ~Mutex() throw ();

    
    /*** void Lock() ************************************************/
    // Lock mutex. If mutex locked, block until able to lock.
    //
    // Result and Exceptions:
    // 	    on failure:	throw MutexException
    void Lock();

    /*** Lock(int _milliseconds) ************************************/
    // Wait to lock with timeout. 
    //
    // Arguments: 	_milliseconds - timeout length. 
    // 				
    // Output: true - if successfully locked before timeout
    // 	       false - if timed out	
    // 	       MutexException is thrown if an error is encountered.
    //
    bool Lock(int _timeout);


    void TryLock();

    /*** void Unlock() **********************************************/
    // Unlock a locked mutex
    //
    void Unlock();



private:

#ifdef WINDOWS
	HANDLE m_mtx;
#else
    pthread_mutex_t m_mtx;
#endif // WINDOWS

}; // class Mutex



/*** class Lock *****************************************************/
// RAII class for managing locking of Mutex objects
//
class Lock : private Uncopyable
{
    public:
        Lock(Mutex& mtx);

        ~Lock();

    private:
        Mutex& m_mtx;
}; // class Lock


#endif //__GENERIC_MUTEX_H__
