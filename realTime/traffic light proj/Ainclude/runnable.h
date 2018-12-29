// runnable.h
//
// Function-like object base class and specialized derived
// classes to run existing C-style functions, class member
// functions, class static functions etc.
//
// Author: Vladimir Krapp
// Created on: 2014-04-10
// Last modified:

#ifndef __RUNNABLE_H__
#define __RUNNABLE_H__

typedef void*(*Cfunc)(void*);

//=== Runnable ============================================
// Base class for runnable objects
//
class Runnable
{
public:
    virtual void operator()() = 0;
};
//==========================================================



//=== FunctionWrapper =======================================
// Wrapper class to run c-style functions
//
template <typename RT, typename ARG, RT (&F)(ARG)>
class FunctionWrapper : public Runnable
{
public:
       FunctionWrapper(ARG _args):m_args(_args){};

       virtual void operator()()
       {
            (F)(m_args);
       }

private:
    ARG m_args;
};
//==========================================================



//=== MemberFuncWrapper ====================================
// Wrapper object to run an class member function.
// The class and function are template parameters,
// while the object CTOR receives the specific instance of
// the class.
//
template <class T, void (T::*MF)()>
class MemberFuncWrapper : public Runnable
{
    T& m_that;

public:

    MemberFuncWrapper(T& _that):m_that(_that){};

    void operator()()
    {
        m_that.*MF();
    }

private:

    // Disallow copy CTOR and assignment
    MemberFuncWrapper(const MemberFuncWrapper&);
    MemberFuncWrapper& operator=(const MemberFuncWrapper&);

};// class MemberFuncWrapper
//==========================================================

#endif // __RUNNABLE_H__
