/************************************************************************
Runnable
Author: Dan Bar-On.
Creation Date: 23.04.14 
Modified at:
Description: Excution entity.
************************************************************************/
#ifndef RUNNABLE_H
#define RUNNABLE_H

class Runnable
{
public:
    virtual void operator()() = 0;
};

template <void (&pFunc)() >
class FunctionRun:public Runnable
{
public:
    virtual void operator()()
    {
        (pFunc)();
    }
};

template <class T, void(T::*pMemFunc)()>
class MemberMethodRun:public Runnable
{
public:
    MemberMethodRun(T& _obj):that(_obj){}
    virtual void operator()(){ (that.*pMemFunc)();}

protected:
    T& that;
};


// unify shared pointer definition for UNIX and WINDOWS
#include "stdafx.h"

#ifdef WIN32 
#include <memory>	//shared_ptr
typedef std::shared_ptr<Runnable> RunShared;
EXPIMP_TEMPLATE template class MULTITHREADING_API std::shared_ptr<Runnable>;
#elif UNIX
#include <tr1/memory>	//shared_ptr
typedef std::tr1::shared_ptr<Runnable> RunShared;
#endif



#endif // RUNNABLE_H
