#ifndef __GLOBAL_INITIALIZER_H__
#define __GLOBAL_INITIALIZER_H__

/*
Global Initialier.
To use safely global variables, declare them in your .h file,
using this macro:
	GLOBAL_DEC(type of the var, name of the var)
and define them in your cpp file usingg this macro:
	GLOBAL_DEF(type of the var, name of the var)

You must not #include the h file in the cpp file.
*/


#include <cstdio>

#define GLOBAL_DEF(T, g_t)\
static const size_t SIZE = sizeof(T) % sizeof(double) ? sizeof(T) / sizeof(double) + 1 : sizeof(T) / sizeof(double);\
double g_t[SIZE];\
bool g_t##Should = true;

#define GLOBAL_DEC(T, g_t)\
extern T g_t;\
extern bool g_t##Should;\
static Initer<T> g_t##I(&g_t, &g_t##Should);


template<class T>
class Initer
{
public:
	Initer(T* _t, bool* _should);
	~Initer();
	
private:
	T* m_t;
	bool m_should;

};

template<class T>
Initer<T>::Initer(T* _t, bool* _should)
:m_t(_t), m_should(*_should)
{
	if (m_should)
	{
		new (_t) T;
		*_should = false;
	}
}

template<class T>
Initer<T>::~Initer()
{
	if(m_should)
	{
		m_t->~T();
	}
}

#endif //#ifndef __GLOBAL_INITIALIZER_H__
