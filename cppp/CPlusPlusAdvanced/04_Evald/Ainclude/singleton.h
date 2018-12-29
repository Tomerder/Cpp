/***************************************************************************
	Author: Stav Ofer
	Creation date:  		2013-11-14
	Last modified date:		2013-11-15
	Description: 	Singleton template.
					Used to ensure a global variable is initialized before use,
					with thread safety.
					
					IMPORTANT:
					- Object access is through the Instance() function only.
					Do not attempt to create a Singleton object - it will fail.
					- You can have only one Singleton of each type TYPE, 
					however, use of local variables fo this type is not restricted.
					
					THREAD_SAFETY:
					is only for initizlization. User is responsible for thread-
					safety during the rest of the run.
					
					FEATURES:
					- CTOR is called exactly once.
					- Attempted access after destruction will cause crash.
					- Thread-safe initialization.
					
					USE:
					- Where you would use a global variable of type TYPE, use
					instead: Singleton<TYPE>::Instance().
					Call to a member function TYPE.Func() becomes:
					Singleton<TYPE>::Instance().Func().
					- No variable declaration or definition is needed. It is taken
					care of by the Singleton class.

					RECOMMENDATION:
					Define a variable TYPE& t1 = Singleton<TYPE>::Instance().
					Then you can use it normally, e.g. t1.Func().
					
					EXAMPLE:
					To use a global singleton of type X:
					
					X& x1 = Singleton<X>::Instance();
					X& x2 = Singleton<X>::Instance(); // x1, x2 are references to the same global
					
					// these 3 lines are all equivalent
					x1.Func();
					x2.Func();
					Singleton<X>::Instance().Func();
					
****************************************************************************/

#ifndef __SINGLETON_H__
#define __SINGLETON_H__

#include <cstdlib>

namespace m7
{

//=======================================================================//
template <class TYPE>
class Singleton
{
public:	
	static TYPE& Instance();
	// using generated DTOR
	
private:
	static TYPE* s_ptr;	// global object is stored here
	
	static bool isNotInited;
	static bool isBeingInited;
	static bool lock;
	
	static void Deleter();
	
	// no construction or copy
	Singleton();	// if crashed here, note that you should NOT attempt to create a Singleton object
	Singleton(const Singleton&);
	Singleton& operator=(const Singleton&);
};
//=======================================================================//

// initialize static data members

template <class TYPE>
TYPE* Singleton<TYPE>::s_ptr=0;

template <class TYPE>
bool Singleton<TYPE>::isNotInited = true;
template <class TYPE>
bool Singleton<TYPE>::lock = false;


// Access object, initialize the 1st time
template <class TYPE>
TYPE& Singleton<TYPE>::Instance()
{
	// ----- START critical section ----- //
	while( __sync_lock_test_and_set(&lock, 1) ); // spinlock
	
	if(isNotInited) // initialize if needed
	{
		s_ptr = new TYPE;
		atexit(Deleter);
		isNotInited = false;
	}
	__sync_lock_release(&lock);
	// ----- END critical section ----- //
	
	return *s_ptr;	
}
//-----------------------------------------------------------------------//

// when destroying, set ptr to 0xdeadbeef - will cause crash if trying to access afterwards
template <class TYPE>
void Singleton<TYPE>::Deleter()
{
	delete s_ptr;
	s_ptr = static_cast<TYPE*>((void*)0xdeadbeef);
}
//-----------------------------------------------------------------------//


}
//-------------------------- END namespace m7 ---------------------------//

#endif /* __SINGLETON_H__ */
