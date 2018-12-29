#ifndef HKEYHANDLER_H
#define HKEYHANDLER_H

//includes=========================
#ifdef WIN32
#include <windows.h>
#pragma warning(push)
#pragma warning(disable : 4275)
#endif //#ifdef WIN32

#include "uncopyable.h"
#include "myexceptions.h"
//=================================

//export===========================
#ifdef WIN32

#ifdef HKEYHANDLER_EXPORTS
#define HKEYHANDLER_API __declspec(dllexport)
#else
#define HKEYHANDLER_API __declspec(dllimport)
#endif	// HKEYHANDLER_EXPORTS

#elif UNIX
#define HKEYHANDLER_API
#endif	//#ifdef WIN32
//=================================

class HKEYHANDLER_API HkeyHandler : private Uncopyable {
public:
	HkeyHandler(HKEY _hive, std::string _path);	// throws BadConfig

	inline ~HkeyHandler();

	inline operator HKEY() const;

private:
	HKEY m_key;

	struct BadHkeyHandler: public std::runtime_error{ BadHkeyHandler(const  std::string& _s):std::runtime_error(_s){} };
	HkeyHandler(const HkeyHandler&);
	HkeyHandler& operator=(const HkeyHandler&);
};

HkeyHandler::~HkeyHandler()
{
	RegCloseKey(m_key);
}

HkeyHandler::operator HKEY() const
{
	return m_key;
}

#pragma warning(pop)
#endif	// #ifndef HKEYHANDLER_H