#ifndef __SINGLETON__H_
#define __SINGLETON__H_

#include <cassert>	// for assert
#include <unistd.h>

namespace m10{

template<class T>
class Singleton
{
public:
	static T* Instance();

private:
	static T* m_ptr;
	static volatile bool s_isInCreation;
	static volatile bool s_isFinished;

	static void Destroy();	
	Singleton();
	Singleton(const Singleton&);
	Singleton& operator=(const Singleton&);
};

template<class T>
T* Singleton<T>::Instance()
{
	assert(m_ptr != reinterpret_cast<T*>(0xDEADBEEF));
	if (!s_isFinished)
	{
		if(!__sync_fetch_and_or(&s_isInCreation, true))
		{
			m_ptr = new T;
//			__sync_synchronize();	Not needed: global vars and after that a function = memory barrier
			atexit(Destroy);
			s_isFinished = true;	//spinlock - UNLOCK	
		}
		else
		{
			while (!s_isFinished)	//spinlock - LOCK
			{
				sleep(0);
			}
		}
	}
	return m_ptr;
}



template <class T>
void Singleton<T>::Destroy()
{
	delete m_ptr;
	m_ptr = reinterpret_cast<T*>(0xDEADBEEF);
}

template<class T>
T* Singleton<T>::m_ptr = 0; 

template<class T>
volatile bool Singleton<T>::s_isInCreation = false; 

template<class T>
volatile bool Singleton<T>::s_isFinished = false; 

} // end of namespace m10
#endif //#ifndef __SINGLETON__H_

