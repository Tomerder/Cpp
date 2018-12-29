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
	Config( std::string _company, std::string _product = "" );
#elif UNIX
	Config();
#else
#error only supporrts WIN32 and UNIX
#endif //#ifdef WIN32

	~Config();

	template <class T>
	T Get( std::string _confName, T _defaultVal) const;

	template <class T>
	void Set( std::string _confName, T _val);

private:
#ifdef WIN32
	HKEY m_key;
    static const DWORD maxCharsNum = 256;
#endif

	struct BadConfig: public std::runtime_error	{ BadConfig(const  std::string& _s):std::runtime_error(_s){} };
};

template<>
int			CONFIG_API Config::Get<int>(std::string _confName, int _defaultVal) const;	

template<>
std::string CONFIG_API Config::Get<std::string>(std::string _confName, std::string _defaultVal) const;	

template<>
double		CONFIG_API Config::Get<double>(std::string _confName, double _defaultVal) const;

template<>
void CONFIG_API Config::Set<std::string>(std::string _confName, std::string _val);


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
	wstring wconfName = wstring(_confName.begin(), _confName.end());

	LONG ret = RegSetValueEx(
		m_key,				// HKEY hKey
		wconfName.c_str(),	// LPCTSTR lpValueName,
		0,					// DWORD Reserved,
		0,					// DWORD dwType,
		(const BYTE*)&_val,	// const BYTE *lpData,
		sizeof(_val)		// DWORD cbData
	);
	CHECK_AND_THROW_DIF(ret, ERROR_SUCCESS, "RegSetValueEx", BadConfig);
}

#endif	// #ifndef CONFIG_H



