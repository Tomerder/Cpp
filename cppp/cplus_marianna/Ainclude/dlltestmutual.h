/**************************************************************************************
    Author: Marianna Shvartsman
    Creation date :      2013-12-15
    Last modified date: 2013-12-15 
    Description : Template + Dll
***************************************************************************************/
#ifndef __MUTUAL_H__
#define __MUTUAL_H__

#ifdef TESTDLL_EXPORTS
#define TESTDLL_API __declspec(dllexport)
#else
#define TESTDLL_API __declspec(dllimport)
#endif

TESTDLL_API void DllFunc2();
TESTDLL_API void DllFunc1();

#endif