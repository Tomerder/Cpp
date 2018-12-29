/***************************************************************************
	Author: Stav Ofer
	Creation date:  		2013-11-14
	Last modified date:		2013-11-15
	Description: 	Global initializer template.
					Used to ensure a global variable is initialized before use.
					
					IMPORTANT:
					If you use this header, DO NOT also use "extern" declarations, 
					use only the supplied macros.
					
					USE:
					- Instead of declaring "extern TYPE t1" in headers, use the
					macro GLOBAL_DECLARE(TYPE, t1).
					- Insead of defining "TYPE t1" in a .cpp file, use the macros
					GLOBAL_DEFINE(TYPE,NAME). DO NOT include any headers that use
					the GLOBAL_DECLARE macro.
					
					RECOMMENDATION:
					Use the GLOBAL_DEFINE macro in a separate .cpp file, which
					includes only this header and whatever headers are neccessary
					to use TYPE.
					
					EXAMPLE:
					
					To have a safe global of type X, instead of this:
					
						--- .h file ---
						extern X g_x;
					
						--- .cpp file ---
						X g_x;
					
					write this:
					
						--- .h file ---
						GLOBAL_DECLARE(X, g_x);
					
						--- .cpp file ---
						GLOBAL_DEFINE(X, g_x);
					
					then use g_x as you would normally use it.
					
					NOTES:
					class Initer is not a real class, and the user will not be
					able to create objects of this type. It is used as a wrapper
					for the global variable.
					
****************************************************************************/

#ifndef __GLOBAL_INITER_H__
#define __GLOBAL_INITER_H__

// use instead of "extern TYPE NAME" in header files
#define GLOBAL_DECLARE(TYPE,NAME)	extern TYPE NAME; \
									extern bool NAME##_inited; \
									static m7::Initer<TYPE> g_initer_##NAME\
										(&NAME##_inited, &NAME);

// use instead of "TYPE NAME" in a .cpp file, with NO includes that use GLOBAL_DECLARE
#define GLOBAL_DEFINE(TYPE,NAME)	char NAME[sizeof(TYPE)];\
									bool NAME##_inited = false;


namespace m7
{

//=======================================================================//
// Class TYPE should have public default CTOR and DTOR
template <class TYPE>
class Initer
{
public:
	Initer(bool* _isInited, TYPE* _t);
	~Initer();
	
private:
	TYPE* m_t;
	bool m_shouldKill;
};
//=======================================================================//


// CTOR - calls CTOR of TYPE by using placement new
template <class TYPE>
Initer<TYPE>::Initer(bool* _isInited, TYPE* _t) : m_t(_t), m_shouldKill(!*_isInited)
{
	if(!*_isInited)
	{
		new (_t) TYPE;
		m_t = _t;
		*_isInited = true;
	}
}
//-----------------------------------------------------------------------//

// DTOR - calls DTOR of TYPE ("placement delete")
template <class TYPE>
Initer<TYPE>::~Initer()
{
	if(m_shouldKill)
	{
		m_t->~TYPE();
	}
}
//-----------------------------------------------------------------------//

}
//-------------------------- END namespace m7 ---------------------------//

#endif /* __GLOBAL_INITER_H__ */
