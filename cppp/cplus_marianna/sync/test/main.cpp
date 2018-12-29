/**************************************************************************************
    Author: Marianna Shvartsman
    Creation date :      2013-11-18
    Last modified date: 2013-11-18
    Description : sync Test
***************************************************************************************/
#include <iostream>
using namespace std;
#ifdef __LINUX
#include <unistd.h>
#endif
#include <cstdlib>

#include "sync.h"
using namespace multithreading_m7;

#define MAX_THREADS 2

typedef struct Arg
{
	Mutex*		m;
	CondVar*	cond;
}Arg;

int test = 0; // global var


#ifdef __LINUX
void*	MTest(void* _params)
#else
DWORD WINAPI	MTest(void* _params)
#endif
{
	Arg* arg = reinterpret_cast<Arg*>(_params);

	cout << "My num is ";
	arg->m->Lock();
	cout << ++test << endl;
	arg->cond->Wait(arg->m,560);
#ifdef __LINUX
	sleep(1);
#else
	Sleep(1000);
#endif
	arg->m->Unlock();

	return 0;
}


#ifdef __LINUX
void*	CondTest(void* _params)
#else
DWORD WINAPI	CondTest(void* _params)
#endif
{
	Arg* arg = reinterpret_cast<Arg*>(_params);
	cout << "My num is ";
	arg->m->Lock(6856);
	cout << ++test << endl;
	arg->m->Unlock();

	cout << "CondVar Work" << endl;
	return 0;
}


int main()
{
	Mutex m;
	CondVar cond;

	Arg arg;
	arg.m = &m;
	arg.cond = &cond;
	
#ifdef __LINUX
	pthread_t arrThr[2];
	
	pthread_create(&arrThr[0],0,MTest,reinterpret_cast<void*>(&arg));
	
	pthread_create(&arrThr[1],0,CondTest,reinterpret_cast<void*>(&arg));

	sleep(1);

	
	cond.NotifyOne();
	
	for(int i = 0; i < 2; ++i)
	{
		pthread_join(arrThr[i],0);
	}
	
#else
	DWORD   dwThreadIdArray[MAX_THREADS];
    HANDLE  hThreadArray[MAX_THREADS]; 

	hThreadArray[0] = CreateThread(NULL,0,MTest,reinterpret_cast<void*>(&arg), 0, &dwThreadIdArray[0]);  

	hThreadArray[1] = CreateThread(NULL,0,CondTest,reinterpret_cast<void*>(&arg), 0, &dwThreadIdArray[1]); 

	for(int i = 0; i < MAX_THREADS; ++i)
	{
		if (hThreadArray[i] == NULL) 
		{
			return 0;
		}
	}
	Sleep(1000);

    // Wait until all threads have terminated.

    WaitForMultipleObjects(MAX_THREADS, hThreadArray, TRUE, INFINITE);

    // Close all thread handles and free memory allocations.

    for(int i=0; i<MAX_THREADS; i++)
    {
        CloseHandle(hThreadArray[i]);
    }

#endif


	return 0;
}


