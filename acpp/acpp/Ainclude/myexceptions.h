/************************************************************************
Myexceptions
Author: Dan Bar-On.
Creation Date: 23.04.14 
Modified at:
Description: Exceptions for different types of errors.
			Also includes macros for error handling.
************************************************************************/
#ifndef MY_EXCEPTIONS_H
#define MY_EXCEPTIONS_H

#include <stdexcept>//runtime_error
#include <string>
#include <cstring>	//strerror
#include <cerrno>	//errno
#include <cstdio>	//fprintf

//============Error handling MACROS===================

template <class EXC_TYPE>
void COMMON_ERROR_MACRO( std::string MESSAGE) 
{
	 std::string err = ( std::string)"error: " + ( std::string)(MESSAGE) + ( std::string)"from errno: ";/* + (string)strerror(errno);*/
	fprintf(stderr, "%s", err.c_str() );
	throw EXC_TYPE(err);
}


#define CHECK_AND_THROW_DIF(VAL_GOT, VAL_GOOD ,MESSAGE, EXC_TYPE)\
if ( (VAL_GOT) != (VAL_GOOD) ) COMMON_ERROR_MACRO<EXC_TYPE>(MESSAGE)

#define CHECK_AND_THROW_EQ(VAL_GOT, VAL_BAD ,MESSAGE, EXC_TYPE)\
if ( (VAL_GOT) == (VAL_BAD) ) COMMON_ERROR_MACRO<EXC_TYPE>(MESSAGE)

#define THROW(MESSAGE, EXC_TYPE)\
COMMON_ERROR_MACRO<EXC_TYPE>(MESSAGE)

//============Exceptions===================

struct BadThread: public std::runtime_error	{ BadThread(const  std::string& _s):std::runtime_error(_s){} };
struct BadSem: public std::runtime_error	{ BadSem(const  std::string& _s):std::runtime_error(_s){} };
struct BadMutex: public std::runtime_error	{ BadMutex(const  std::string& _s):std::runtime_error(_s){} };
struct BadThreadPool: public std::runtime_error { BadThreadPool(const  std::string& _s):std::runtime_error(_s){} };

#endif // MY_EXCEPTIONS_H
