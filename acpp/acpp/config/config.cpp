#include <iostream>	//for debug
#include "config.h"
using namespace std;

Config::Config(string _company, string _product):
m_key(HKEY_LOCAL_MACHINE, (string)"SOFTWARE" + (string)"\\" + _company + (string)"\\" + _product){}

//Getters==================================================================================
bool Config::GetImp( std::string _confName, void* _val, DWORD _size) const
{
	wstring wconfName = wstring(_confName.begin(), _confName.end());

    LONG ret = RegQueryValueEx( m_key,
                             wconfName.c_str(),
                             NULL,
                             0,
                             (LPBYTE) _val,
                             &_size );

	return (ret == ERROR_SUCCESS) ? true : false;
}

template<>
string Config::Get<string>(string _confName, string _defaultVal) const
{
	WCHAR buff[MAX_CHARS_NUM];
	bool ret = GetImp(_confName, buff, MAX_CHARS_NUM );

	if (ret)
	{
		wstring wbuff(buff);
		return string(wbuff.begin(), wbuff.end());
	}
	return _defaultVal;
}

void Config::SetImp( std::string _confName, void* _val, DWORD _type, DWORD _size)
{
	wstring wconfName = wstring(_confName.begin(), _confName.end());

	LONG ret = RegSetValueEx(
		m_key,				// HKEY hKey
		wconfName.c_str(),	// LPCTSTR lpValueName,
		0,					// DWORD Reserved,
		_type,				// DWORD dwType,
		(const BYTE*)_val,	// const BYTE *lpData,
		_size				// DWORD cbData
	);
	CHECK_AND_THROW_DIF(ret, ERROR_SUCCESS, "RegSetValueEx", BadConfig);
}

template<>
void Config::Set<string>(string _confName, string _val)
{
    wstring wval = wstring(_val.begin(), _val.end() );
	SetImp(_confName, const_cast<wchar_t*>( wval.c_str()), REG_SZ, (_val.size()+1)*sizeof(WCHAR) );
}
