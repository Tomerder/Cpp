#ifndef STDAFX_H
#define STDAFX_H

#ifdef WIN32

#ifdef MULTITHREADING_EXPORTS
#define MULTITHREADING_API __declspec(dllexport)
#define EXPIMP_TEMPLATE
#else
#define MULTITHREADING_API __declspec(dllimport)
#define EXPIMP_TEMPLATE extern
#endif	// MULTITHREADING_EXPORTS

#elif UNIX
#define MULTITHREADING_API
#endif	//#ifdef WIN32

#endif //#ifndef STDAFX_H
