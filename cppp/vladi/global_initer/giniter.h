// giniter.h
//
//	Global variable template initer
//	Author: Vladimir Krapp
//	Created on: 6/4/14
//	Last modified:

#ifndef __GLOBAL_INITER_H__
#define __GLOBAL_INITER_H__

#include <new>

#define GLOBAL_DECL(TYPE, G_VAR)                    \
        extern TYPE (G_VAR);                      \
        extern bool G_VAR##should;                \
        static TIniter<TYPE> G_VAR##I(&(G_VAR), &G_VAR##should)

#define GLOBAL_DEF(TYPE, G_VAR)                                     \
                double (G_VAR)[(sizeof(TYPE)/ sizeof(double)) + 1];     \
                bool G_VAR##should

template<class T>
class TIniter
{
    public:
    TIniter(T* _t, bool* _should):m_t(_t), m_should(_should)
    {
        if (m_should)
        {
            new (_t) T;
            *_should = false;
        }
    }

    ~TIniter()
    {
        if(m_should)
        {
            m_t->~T();
        }
    }

    private:
    T* m_t;
    bool m_should;
};



#endif //__GLOBAL_INITER_H__
