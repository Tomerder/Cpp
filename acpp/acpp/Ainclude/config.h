#ifndef CONFIG_H
#define CONFIG_H

//includes=========================
#ifdef WIN32
#include <windows.h>
#endif //#ifdef WIN32

#include <vector>
#include <string>
#include <stdexcept>//runtime_error
#include "uncopyable.h"
#include "myexceptions.h"
#include "hkeyhandler.h"
//=================================

//export===========================
#ifdef WIN32

#ifdef CONFIG_EXPORTS
#define CONFIG_API __declspec(dllexport)
#else
#define CONFIG_API __declspec(dllimport)
#endif	// CONFIG_EXPORTS

#elif UNIX
#define CONFIG_API
#endif	//#ifdef WIN32
//=================================

class CONFIG_API Config { // : private Uncopyable {
public:
#ifdef WIN32
	Config( std::string _company, std::string _product = "" );	// throws BadConfig
#elif UNIX
	Config();	// not yet supported
#else
#error only supporrts WIN32 and UNIX
#endif //#ifdef WIN32

	template <class T>
	T Get( std::string _confName, T _defaultVal) const;

	template <class T>
	void Set( std::string _confName, T _val);	// throws BadConfig

private:
#ifdef WIN32
	HkeyHandler m_key;
	static const DWORD MAX_CHARS_NUM = 256;
#endif
    void SetImp( std::string _confName, void* _val, DWORD _type, DWORD _size);
	bool GetImp( std::string _confName, void* _val, DWORD _size) const;

	struct BadConfig: public std::runtime_error	{ BadConfig(const  std::string& _s):std::runtime_error(_s){} };
};

//=============================================================================
// Get specializations
template<>
inline int CONFIG_API Config::Get<int>(std::string _confName, int _defaultVal) const
{
	DWORD buff;
	return GetImp(_confName, &buff, sizeof(int) ) ? buff : _defaultVal;
}

template<> 
inline double CONFIG_API Config::Get<double>(std::string _confName, double _defaultVal) const
{
	double buff;
	return GetImp(_confName, &buff, sizeof(double) ) ? buff : _defaultVal;
}

template<>
std::string CONFIG_API Config::Get<std::string>(std::string _confName, std::string _defaultVal) const;

//=============================================================================
// Set specializations
template<>
inline void CONFIG_API Config::Set<int>(std::string _confName, int _val)
{
    SetImp(_confName, &_val, REG_DWORD, sizeof(int) );
}

template<>
inline void CONFIG_API Config::Set<double>(std::string _confName, double _val)
{
    SetImp(_confName, &_val, REG_BINARY, sizeof(double) );
}

template<>
void CONFIG_API Config::Set<std::string>(std::string _confName, std::string _val);

//=============================================================================
// if trying to call a function with another type - you get a compilation error
template <class T>
T Config::Get(std::string _confName, T _defaultVal) const
{
	// if you got error here - it's because there is no support for your type
	typename std::vector<T>::NoSupportForThisType t;
}

template <class T>
void Config::Set( std::string _confName, T _val)
{
	// if you got error here - it's because there is no support for your type
	typename std::vector<T>::NoSupportForThisType t;
}

#endif	// #ifndef CONFIG_H