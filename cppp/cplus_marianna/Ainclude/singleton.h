/**************************************************************************************
    Author: Marianna Shvartsman
    Creation date :      2013-11-14
    Last modified date: 2013-11-14
    Description : Singleton Implementation
***************************************************************************************/
#ifndef __SINGLETON__
#define __SINGLETON__
/**************************************************************************************
Description:
	class Singleton ensures that class of type T has only one instance
	and provides a global point of access to that instance.
	The instance destroyed in the end of the program
	
This singleton implementation has the following features: 
	-Instance initialize only when used
	-Initialize only once
	-Crashes if used after destruction, can't be initialize one more time after destruction
	-thread safe
	
Class T requirements:
	-Class T need to have default CTOR 
	-If you want your class use only with Singleton, put T CTOR in private and define Singleton as friend

Example:
	Singleton<Person>::Instance().SetName;
	Singleton<Person>::Instance().GetName;
	Singleton<Person>::Instance().GetAge;
Tips:
	-use #define	PERSON	Singleton<Person>::Instance() to simple usage  
***************************************************************************************/
#include <cstdlib>
#include <unistd.h>

template <class T>
class Singleton
{

public:
	static T& Instance();

private:
	static T* s_ptr;
	static bool s_isReady;  //ready to use,first step checking in the case of multi threading usage
	static bool s_shouldInit;	//second step checking in the case of multi threading usage
	//atexit destroy instance function
	static void DeleteFunc(); 
	
	Singleton();
	Singleton(const Singleton&);
	Singleton& operator=(const Singleton&);
};

template <class T> T* Singleton<T>::s_ptr = 0;
template <class T> bool Singleton<T>::s_shouldInit = true;
template <class T> bool Singleton<T>::s_isReady = false;

template <class T>
T& Singleton<T>::Instance()
{
	if(!s_isReady)
	{
		//if the previous value of isInit was false, i'm the first thread and can to do init
		if(__sync_fetch_and_and(&s_shouldInit,false))
		try
		{
			s_ptr = new T;
			atexit(DeleteFunc);
			s_isReady = true;		
		}
		catch (bad_alloc )
		{
			__sync_fetch_and_or(&s_shouldInit,true);
			//LOG
			throw;
		}		
		catch(...)
		{
			__sync_fetch_and_or(&s_shouldInit,true);
			//LOG
			throw;
			
		}
		
		else //yet not ready to use but else thread start initialization
		{
			while(!s_isReady) //TODO cond_var
			{
				sleep(0);
			}
		}
	}		
	
	return *s_ptr;
}

template <class T>
void Singleton<T>::DeleteFunc()
{
	delete s_ptr;
	s_ptr = reinterpret_cast<T*>(0xdeadbeef);
}

#endif

