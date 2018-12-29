// utility.h
//
//	Utility classes for advanced cpp projects
//	Author: Vladimir Krapp
//	Created on: 22/4/2014
//	Last modified:

#ifndef __UTILITY_H__
#define __UTILITY_H__

#include <climits> // for timeout limit definitions
#include <stdexcept> // for the exception base class
#include <cstdio>   // for fprintf in EvalAndThrow
#include <cstring>  // for strerror in EvalAndThrow

#include <string>   


#include <errno.h>    // for errno in EvalAndThrow




//=== Exception handling ===
template <class EXPT>
void EvalErrAndThrow(int _err, std::string _msg)
{
    if(!_err)
    {
        return;
    }


//    std::string msg = _msg + ", details: " + strerror(_err);
//    fprintf(stderr, "%s\n", msg.c_str());

    throw EXPT(_msg);
}

template <class EXPT>
void ThrowIfTrue(bool _cond, std::string _msg)
{
    if(!_cond)
    {
        return;
    }

    fprintf(stderr, "%s\n", _msg.c_str());
    throw EXPT(_msg);
}



template <class EXPT>
void ThrowIfError(std::string _msg)
{
    if(!errno)
    {
        return;
    }

    //std::string msg = _msg + ", details: " + strerror(errno);
    //fprintf(stderr, "%s\n", msg.c_str());
    throw EXPT(_msg);
}



//=== Timeout definitions ===
static const int WAIT_ZERO = 0;
static const int WAIT_INFINITE = INT_MAX;






//=== Uncopyable and Unassignable base classes ===

class  Uncopyable
{
    protected:                  // Allow construction 
        Uncopyable(){}          // and destruction of 
        ~Uncopyable(){}         // derived objects

    private:                            // but prevent copying
        Uncopyable(const Uncopyable&);          
        Uncopyable& operator=(const Uncopyable&);
};


// Base classes in hierarchies should 'private' inherit from
// this class to prevent slicing bugs
class  Unassignable
{
    protected:
        Unassignable(){}
        ~Unassignable(){}

    private:
        Unassignable& operator=(const Unassignable&);
};



#endif //__UTILITY_H__
