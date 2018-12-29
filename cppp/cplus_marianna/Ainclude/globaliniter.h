/**************************************************************************************
    Author: Marianna Shvartsman
    Creation date :      2013-11-14
    Last modified date: 2013-11-14
    Description : GlobalIniter
***************************************************************************************/
#ifndef __GLOBALINITER__
#define __GLOBALINITER__

//GlobalIniter lets you use global objects safly- wihtout
//the danger of using an object before it was constructured

//DANGER: clients of your code MUST include your header, 
//and NOT declare the extern declarations themself 

//EXAMPLE:
//--------if your .h file look like this:
// extern X g_x;
//extern Y g_y;

//--------and your .cpp file look like this:
//X g_x;
//Y g_y;

//-----------------------------------------

//-------replace the .h with
// GLOBAL_DECLARE(X,g_x)
// GLOBAL_DECLARE(Y,g_y)														

//DO NOT INCLUDE .h file in .cpp file

//------and replace the .cpp with
//GLOBAL_DEFINE(X,g_x)
//GLOBAL_DEFINE(Y,g_y)

											
#define GLOBAL_DEFINE(TYPE,NAME)			double NAME[sizeof(TYPE)/8+1];\
											bool NAME##_inited = false;
																			
#define GLOBAL_DECLARE(TYPE,NAME)			extern TYPE NAME;				\
											extern bool NAME##_inited;		\
											static GlobalIniter<TYPE> g_initer_##NAME(&NAME##_inited, &NAME);
											

template<class T>
class GlobalIniter //: TODO Uncopyable 
{
	public:
		GlobalIniter (bool* _isInited, T* _t);
		~GlobalIniter ();

	private:
		bool m_should;
		T*	 m_t;
};

template<class T>
GlobalIniter<T>::GlobalIniter(bool* _isInited, T* _t): m_should(!*_isInited), m_t(_t)
{
	if (!*_isInited)
	{
		new (m_t) T;
		*_isInited = true;
	}	
}

template<class T>
GlobalIniter<T>::~GlobalIniter()
{
	if(m_should)
	{
		m_t->~T();
	}
}

#endif

