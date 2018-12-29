/**************************************************************************************
    Author: Marianna Shvartsman
    Creation date :      2013-11-05
    Last modified date: 2013-11-05
    Description : Shared Pointer
***************************************************************************************/
#ifndef __SHARED_POINTER_H__
#define __SHARED_POINTER_H__

#include <cstddef>
#include <cassert>

/*Description:
	Shared pointers points to an object of type T, counts the number of references there are to the actual pointer, and deletes the object when that counter reaches zero.
	Can't  point to array
 *Example:
	SharedPtr<Person> p(new Person);
	SharedPtr<Person> p1(p);
	p = p1;
	p->Foo(); Foo mem function of Person
	*p1;
	p1.IsShared();
	SharedPtr<Person> ptrstd(new Student); //Student is derived of Person

*/
namespace m7
{
using std::size_t;

template <class T> //requirement public DTOR
class SharedPtr
{
public:
    explicit SharedPtr (T* _data);
    SharedPtr(const SharedPtr& _o);
    //O should be implicit convertible to T,
    //to provide implicite conversion from derive to base,
    //from pointer to base
    template<class O>
    SharedPtr(const SharedPtr<O>& _o);
    inline	~SharedPtr (); //can't  point to array

    SharedPtr& operator=(const SharedPtr& _o);
    template<class O>
    SharedPtr& operator=(const SharedPtr<O>& _o);
    inline bool IsShared()const;
    inline	T*	 operator->()const;
    inline	T&	 operator*()const;

private:
    T* 		m_data;
    size_t*	m_rc;

    inline	void Increment();
    inline  void Decrement();//Decrement counter and free data when is single owner

    template<class> friend class SharedPtr;// this friend need to support implicite conversion for convertible type (static_cast)
};

//*************************************************************************
//	CTOR
//*************************************************************************
template<class T>
SharedPtr<T>::SharedPtr(T* _data):m_data(_data), m_rc(new size_t(1)) {}

//*************************************************************************
//	CTOR from convertible T type
//*************************************************************************
template<class T>
template<class O>
SharedPtr<T>::SharedPtr(const SharedPtr<O>& _o): m_data(_o.m_data),m_rc(_o.m_rc)
{
    Increment();
}

//*************************************************************************
//	copy CTOR
//*************************************************************************
template<class T>
SharedPtr<T>::SharedPtr(const SharedPtr<T>& _o): m_data(_o.m_data), m_rc(_o.m_rc)
{
    Increment();
}

//*************************************************************************
//	DTOR
//*************************************************************************
template<class T>
inline SharedPtr<T>::~SharedPtr ()
{
    Decrement();
}
//*************************************************************************
//	operator=
//*************************************************************************
template<class T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr& _o)
{
    return operator=<T>(_o);
}
//*************************************************************************
//	operator=
//*************************************************************************
template<class T>
template<class O>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<O>& _o)
{
    SharedPtr temp(_o);

    Decrement();
    m_data = temp.m_data; 	//if it fault in this line, it because assigment of pointers that can't be implicite conversion
    m_rc = temp.m_rc;
    Increment();

    return *this;

}

//*************************************************************************
//	IsShared
//*************************************************************************
template<class T>
inline bool SharedPtr<T>::IsShared()const
{
    assert(m_rc);
    assert(*m_rc);

    return (*m_rc > 1);
}
//*************************************************************************
//	operator->
//*************************************************************************
template<class T>
inline T*	 SharedPtr<T>::operator->()const
{
    assert(m_rc);
    assert(*m_rc);

    return m_data;
}
//*************************************************************************
//	operator*
//*************************************************************************
template<class T>
inline T&	 SharedPtr<T>::operator*()const
{

    assert(m_rc);
    assert(*m_rc);

    return *m_data;
}
//*************************************************************************
//	Atomic Increment
//*************************************************************************
template<class T>
inline	void SharedPtr<T>::Increment()
{
    __sync_add_and_fetch(m_rc, 1);
}
//*************************************************************************
//	Decrement and Destroy if need
//*************************************************************************

template<class T>
inline void	SharedPtr<T>::Decrement()
{
    assert(m_rc);
    assert(*m_rc);

    if ( 0 == __sync_sub_and_fetch(m_rc, 1))
    {

        delete m_data;
        m_data = 0;
        delete m_rc;
        m_rc = 0;
    }

}

}//end of namespace m7

#endif //__SHARED_POINTER_H__

