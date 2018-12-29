/************************************************************************
Semaphore
Author: Dan Bar-On.
Creation Date: 23.04.14 
Modified at:
Description: Standard API for semaphore services.
************************************************************************/
#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#ifdef WIN32 
#include <windows.h>
#include "stdafx.h"
#elif UNIX
#include <semaphore.h>	//sem_t
#endif

#include "uncopyable.h"

class MULTITHREADING_API Semaphore: private Uncopyable{
public:
	explicit Semaphore(unsigned int _initVal = 0, bool _forProccesses = false);	//throws BadSem exception. _forProccesses not relevant to WIN32
    ~Semaphore();
    void Up();		//throws BadSem exception
    void Down();	//throws BadSem exception
    
	bool Down(float _timeout);	//not implemented

private:
#ifdef WIN32 
	HANDLE m_sem;	
#elif UNIX
	sem_t m_sem;
#endif

};

#endif // SEMAPHORE_H
