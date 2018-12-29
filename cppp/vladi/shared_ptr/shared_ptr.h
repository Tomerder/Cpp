// shared_ptr.h
//
//	Shared pointer implimentation
//	Author: Vladimir Krapp
//	Created on: 6/4/14
//	Last modified:

#ifndef __SHARED_PTR_H__
#define __SHARED_PTR_H__

#include <cassert>

namespace m10
{

template <class T>
class shared_ptr
{

    public: 

        template <class>
        friend class shared_ptr;

        template <class A, class B>
        friend bool operator==(const shared_ptr<A>&, const shared_ptr<B>&);

        class Bool
        {
            friend class shared_ptr;
            public:
            operator bool(){return m_val;}

            private:
            Bool(bool _b):m_val(_b){}
            bool m_val;

        };


        shared_ptr(T* tPtr = 0);                              



        shared_ptr(const shared_ptr& source);
        
        template<class D>
        shared_ptr(const shared_ptr<D>& source);


        ~shared_ptr();


        shared_ptr& operator=(const shared_ptr& source);

        template<class D>
        shared_ptr& operator=(const shared_ptr<D>& source);

        inline T* GetCPtr();
        inline const T* GetCPtr() const;

        // allow implicit creation of C style pointer
        inline operator T*(); 

        // allow implicit creation of const C style pointer
        inline operator const T*() const; 



        // allow implicit creation of bool value
        //operator bool() const; 

        // allow creation of bool value trough proxy
        operator Bool() const; 



        T& operator*();
        const T& operator*() const;

        T* operator->();
        const T* operator->() const;


        void Swap(shared_ptr& other);


        // Detaches the shared_ptr from the managed object,
        // doesn't destroy the object even if this is the 
        // last shared_ptr
        T* Detach();

        // destroys the managed object if this is the last 
        // shared_ptr
        void Release(); 


        size_t CountRefs();

    private:
        
        void DecrAndDeleteIfLast();
        inline void DetachImpl();

        T            *m_object;
        unsigned int *m_count;

}; // class shared_ptr





//=== Interface Function implementations ===================





//=== CTOR ===========================================
template<class T>
shared_ptr<T>::
shared_ptr(T* tPtr):
    m_object(0), m_count(0)
{
    try
    {
        m_count = new unsigned int(0);
    }
    catch(...)
    {
        delete tPtr;
        throw;
    }

    m_object = tPtr;

    __sync_fetch_and_add(m_count, 1);
}


//=== Copy CTOR ======================================
template <class T>
shared_ptr<T>::
shared_ptr(const shared_ptr& source)
{
    __sync_fetch_and_add(source.m_count, 1);

    m_object = source.m_object;
    m_count = source.m_count;
    
}

//=== Copy CTOR From Derived Class ===================
template <class T>
template <class D>
shared_ptr<T>::
shared_ptr(const shared_ptr<D>& source)
{
    __sync_fetch_and_add(source.m_count, 1);

    m_object = source.m_object;
    m_count = source.m_count;
    
}




//=== DTOR ===========================================
template<class T>
shared_ptr<T>::
~shared_ptr()
{ 
    DecrAndDeleteIfLast();
}

//=== Assignment operator ============================
template < class T>
shared_ptr<T>& shared_ptr<T>::
operator=(const shared_ptr& source)
{
    __sync_fetch_and_add(source.m_count, 1);

    DetachImpl();

    m_object = source.m_object;
    m_count = source.m_count;
    
    return *this;
}

//=== Assignment operator from shared_ptr to Derived==
template <class T>
template <class D>
shared_ptr<T>& shared_ptr<T>::
operator=(const shared_ptr<D>& source)
{
    __sync_fetch_and_add(source.m_count, 1);

    DetachImpl();

    m_object = source.m_object;
    m_count = source.m_count;
    
    return *this;
}


//============================================================
template <class T>
inline T* 
shared_ptr<T>::
GetCPtr()
{
    return m_object;
}

template <class T>
inline const T* 
shared_ptr<T>::
GetCPtr() const
{
    return m_object;
}





template <class T>
inline shared_ptr<T>::
operator T*() 
{
    return m_object;
}

template <class T>
inline shared_ptr<T>::
operator const T*() const
{
    return m_object;
}




//template <class T>
//shared_ptr<T>::
//operator bool() const 
//{
//    return m_object;
//}
//
//

template <class T>
shared_ptr<T>::
operator Bool() const
{
    return Bool(m_object);
}

template <class T>
T& 
shared_ptr<T>::
operator*()
{
    assert(m_object);

    return *m_object;
}

template <class T>
const T& 
shared_ptr<T>::
operator*() const
{
    assert(m_object);

    return *m_object;
}





template <class T>
T* 
shared_ptr<T>::
operator->()
{
    return m_object;
}

template <class T>
const T* 
shared_ptr<T>::
operator->() const
{
    return m_object;
}



template <class T>
T*
shared_ptr<T>::
Detach()
{
    DetachImpl();
    return m_object;
}




template <class T>
void
shared_ptr<T>::
Release()
{
    DecrAndDeleteIfLast(); 
    m_object = 0;
    m_count = 0;
}







//=== CountRefs: number of current references ===
template <class T>
size_t
shared_ptr<T>::
CountRefs()
{
    return *m_count;
}


//============================================================
//=== Private functions implementations

template <class T>
void
shared_ptr<T>::
DecrAndDeleteIfLast()
{
    unsigned int count = 0;

    if(m_count)
    {
       count = __sync_sub_and_fetch(m_count, 1);
    }

    if(count == 0)
    {
        delete m_object;
        delete m_count;
    }
}

template <class T>
inline void
shared_ptr<T>::
DetachImpl()
{
    __sync_sub_and_fetch(m_count, 1);

    if(!*m_count)
    {
        delete m_count;
    }

    m_object = 0;
    m_count = 0;
}






template <class A, class B>
bool operator==(const shared_ptr<A>& a, const shared_ptr<B>& b)
{
    return a.m_object == b.m_object;

}






} // namespace m10
#endif //__SHARED_PTR_H__
