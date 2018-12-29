#include <iostream>	//for debug

#include "config.h"

using namespace std;


Config::Config(string _company, string _product)
{
	string path = (string)"SOFTWARE" + (string)"\\" + _company + (string)"\\" + _product;
	wstring wpath = wstring(path.begin(), path.end());

	cout << path << endl;
	LONG ret = RegOpenKeyEx( HKEY_LOCAL_MACHINE,
    wpath.c_str(),	//   "SOFTWARE\\Experis"
    0,
    KEY_ALL_ACCESS | KEY_WOW64_64KEY,
    &m_key);

	CHECK_AND_THROW_DIF(ret, ERROR_SUCCESS, "RegOpenKeyEx", BadConfig);
}

Config::~Config()
{
   RegCloseKey(m_key);
}

//Getters==================================================================================
template<>
int	Config::Get<int>(string _confName, int _defaultVal) const
{
    DWORD size = sizeof(int);
	wstring wconfName = wstring(_confName.begin(), _confName.end());

 	int buff = -1;
    LONG ret = RegQueryValueEx( m_key,
                             wconfName.c_str(),
                             NULL,
                             0,
                             (LPBYTE)&buff,
                             &size );

	if (ret == ERROR_SUCCESS)
	{
		return buff;
	}
	return _defaultVal;
}


template<>
string Config::Get<string>(string _confName, string _defaultVal) const
{
    DWORD size = maxCharsNum;
	wstring wconfName = wstring(_confName.begin(), _confName.end());

 	WCHAR buff[maxCharsNum];
    LONG ret = RegQueryValueEx( m_key,
                             wconfName.c_str(),
                             NULL,
                             0,
                             (LPBYTE) buff,
                             &size );
	if (ret == ERROR_SUCCESS)
	{
		wstring wbuff(buff);
		return string(wbuff.begin(), wbuff.end());
	}
	return _defaultVal;
}


template<>
double Config::Get<double>(string _confName, double _defaultVal) const
{
    DWORD size = sizeof(double);
	wstring wconfName = wstring(_confName.begin(), _confName.end());

 	double buff;
    LONG ret = RegQueryValueEx( m_key,
                             wconfName.c_str(),
                             NULL,
                             0,
                             (LPBYTE) &buff,
                             &size );

   	if (ret == ERROR_SUCCESS)
	{
		return buff;
	}
	return _defaultVal;
}


template<>
void Config::Set<string>(string _confName, string _val)
{
    DWORD size = sizeof(WCHAR) * (_val.size() + 1);	// the +1 is for the null terminator 
	wstring wconfName = wstring(_confName.begin(), _confName.end());

	LONG ret = RegSetValueEx(
	m_key,				// HKEY hKey
	wconfName.c_str(),	// LPCTSTR lpValueName,
	0,					// DWORD Reserved,
	0,					// DWORD dwType,
	(const BYTE*)_val.c_str(),	// const BYTE *lpData,
	size				// DWORD cbData
	);

	CHECK_AND_THROW_DIF(ret, ERROR_SUCCESS, "RegSetValueEx string", BadConfig);

}

/*
template<>
void Config::Set<int>(string _confName, int _val)
{
	wstring wconfName = wstring(_confName.begin(), _confName.end());

	LONG ret = RegSetValueEx(
		m_key,				// HKEY hKey
		wconfName.c_str(),	// LPCTSTR lpValueName,
		0,					// DWORD Reserved,
		0,					// DWORD dwType,
		(const BYTE*)&val,	// const BYTE *lpData,
		sizeof(_val)		// DWORD cbData
	);
}

*/