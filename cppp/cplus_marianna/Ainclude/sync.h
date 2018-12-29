/**************************************************************************************
    Author: Marianna Shvartsman
    Creation date :      2013-11-18
    Last modified date: 2013-11-18 
    Description : Synchronization
***************************************************************************************/
#ifndef __SYNC_H__
#define __SYNC_H__

#ifdef __LINUX
#include <pthread.h>
#else
#include <windows.h>
#endif



#include "uncopyable.h"

//Description: user interface to using of sunchronization tool independent of running OS 	
//if functions fail throw exaptions 
namespace multithreading_m7
{
#define TIMEOUT_FOREVER 2147483647L //maximum unsigned int

class Mutex;

//********************************************
//		CondVar Definition
//**********************************************
 class CondVar: private Uncopyable
{
public:
				//cond init
explicit	 CondVar()throw(char*);
				//cond destroy
			~CondVar()throw(char*);
		// default timeout == TIMEOUT_FOREVER, wait forever
bool	Wait(Mutex* _mutex,size_t timeout = TIMEOUT_FOREVER)throw(char*);
void	NotifyOne()throw(char*);
void	NotifyAll()throw(char*);
		
private:
#ifdef __LINUX
		pthread_cond_t m_cond;
#else
		CONDITION_VARIABLE m_cond;
#endif
};

//********************************************
//		Mutex Definition
//********************************************
class Mutex: private Uncopyable
{
//friend bool CondVar::Wait(Mutex* _mutex, size_t _timeout);
friend class CondVar;
public:
				//mutex init
	explicit	Mutex()throw(char*); 
				//mutex destroy
				~Mutex()throw(char*);
			// default timeout == TIMEOUT_FOREVER, lock TIMEOUT_FOREVER
	bool	Lock(size_t timeout = TIMEOUT_FOREVER)throw(char*);
	void	Unlock()throw(char*);

private:
#ifdef __LINUX
		pthread_mutex_t	m_mutex;		
#else	
		CRITICAL_SECTION	m_lock; 
#endif


};
} // end namespace
#endif

