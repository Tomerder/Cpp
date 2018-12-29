/***************************************************************************
	Author: Stav Ofer
	Creation date:  		2013-11-05
	Last modified date:		2013-11-14
	Description: 	Shared pointer interface.
					
					The SharedPtr is used to manage the reference counter for
					a heap-allocated object of type T, and free the memory when
					the counter goes down to 0.
					
					Usage: 
					- * and -> like a regular pointer: *p for direct access to
					object, p->func() to access members.
					- accepts types that have implicit conversion to T:
					derived classes and const T.
					- use ONLY for stand-alone objects, not arrays (memory is
					freed using delete, not delete[]). Can use STL containers
					as single objects.
					- no pointer arithmetic.
					
					
					Notes:
					- const: const functions mean that the **pointer** is const,
					e.g. points to the same object with the same counter. The pointed-to
					objects can be changed.
					- all SharedPtr classes are friends with each other, to
					facilitate implicit conversion
					
					class T shoud have:
					- a destructor
					
****************************************************************************/

#ifndef __SHARED_PTR_H__
#define __SHARED_PTR_H__

#include <cstddef>
#include <cassert>

namespace m7
{
using std::size_t;

//---------------------------------------------------------------------//
//						CLASS SHARED PTR
//---------------------------------------------------------------------//
template <class T>
class SharedPtr
{
public:
	
	inline ~SharedPtr();
	inline explicit SharedPtr(T* _obj);
	inline SharedPtr(const SharedPtr& _other);
	inline SharedPtr& operator =(const SharedPtr& _other);
	
	// "copy CTOR" and assginment operator from class O that's implicitly
	// convertible to T (derived class or const T)
	template <class O>	
	inline SharedPtr(const SharedPtr<O>& _other);
	template <class O>
	inline SharedPtr& operator =(const SharedPtr<O>& _other);
	
	// dereference and member access operators
	inline T& operator *() const;
	inline T* operator ->() const;
	
	inline bool IsShared() const;	// is m_counter > 1
	
private:
	T* m_obj;
	size_t* m_counter;
	
	inline void DecrementAndFree();		// atomic --counter, then delete if 0
	
	inline static void Increment(size_t* _counter);	// atomic ++counter
	
	// make implicit conversion possible
	template <class O> friend class SharedPtr;
};
//######################################################################//


// DTOR
template <class T>
inline SharedPtr<T>::~SharedPtr()
{
	assert(m_obj); assert(m_counter); assert(*m_counter);
	DecrementAndFree();
}
//---------------------------------------------------------------------

// CTOR
template <class T>
inline SharedPtr<T>::SharedPtr(T* _obj) : m_obj(_obj), m_counter(new size_t(1))
{
	assert(_obj);
}
//---------------------------------------------------------------------

// copy CTOR
template <class T>
inline SharedPtr<T>::SharedPtr(const SharedPtr& _other) :
	m_obj(_other.m_obj), m_counter(_other.m_counter)
{
	assert(_other.m_obj); assert(_other.m_counter); assert(*_other.m_counter);
	Increment(m_counter);
}
//---------------------------------------------------------------------

// assignment - actually calls a specialization of the more general
// version (from class O to class T)
template <class T>
inline SharedPtr<T>& SharedPtr<T>::operator =(const SharedPtr& _other)
{
	return operator=<T>(_other);
}
//---------------------------------------------------------------------


// "copy CTOR" and assginment operator from class O that's implicitly
// convertible to T (derived class or const T)
template <class T>
template <class O>
inline SharedPtr<T>::SharedPtr(const SharedPtr<O>& _other) :
		m_obj(_other.m_obj), m_counter(_other.m_counter)
{
	assert(_other.m_obj); assert(_other.m_counter); assert(*_other.m_counter);
	Increment(m_counter);
}
//---------------------------------------------------------------------
template <class T>
template <class O>
inline SharedPtr<T>& SharedPtr<T>::operator =(const SharedPtr<O>& _other)
{
	assert(_other.m_obj); assert(_other.m_counter); assert(*_other.m_counter);
	
	// incrementing first to take care of assignment to self
	Increment(_other.m_counter);
	DecrementAndFree();
	
	m_obj = _other.m_obj; // compilation error here means no implicit conversion from _other to *this
	m_counter = _other.m_counter;
	return *this;
}
//---------------------------------------------------------------------


// atomic ++_counter (accepts argument b/c in assignment needs to act on another object
template <class T>
inline void SharedPtr<T>::Increment(size_t* _counter)
{
	assert(_counter); assert(*_counter);
	__sync_add_and_fetch(_counter, 1);
}
//---------------------------------------------------------------------

// atomic --m_counter & delete if 0
template <class T>
inline void SharedPtr<T>::DecrementAndFree()
{
	assert(m_obj); assert(m_counter); assert(*m_counter);
	if( 0 == __sync_sub_and_fetch(m_counter, 1) )
	{
		delete m_counter;
		delete m_obj;
		m_counter = 0;
		m_obj = 0;
	}
}
//---------------------------------------------------------------------

// dereference operator
template <class T>
inline T& SharedPtr<T>::operator *() const
{
	assert(m_obj); assert(m_counter); assert(*m_counter);
	return *m_obj;
}
//---------------------------------------------------------------------

// member access operator
template <class T>
inline T* SharedPtr<T>::operator ->() const
{
	assert(m_obj); assert(m_counter); assert(*m_counter);
	return m_obj;
}
//---------------------------------------------------------------------

// true of pointer is shared
template <class T>
inline bool SharedPtr<T>::IsShared() const
{
	assert(m_obj); assert(m_counter); assert(*m_counter);
	return ( *m_counter > 1 );
}
//---------------------------------------------------------------------


}
//------------------------- END namespace m7 ----------------------//


#endif  /* __SHARED_PTR_H__ */

