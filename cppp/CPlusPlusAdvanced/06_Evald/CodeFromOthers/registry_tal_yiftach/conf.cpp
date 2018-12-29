/*************************************************
    Author: Yiftach Ariel
    Creation date :      9.12.13
    Last modified date:  10.12.13
    Description : conf cpp-file.
**************************************************/
#include <string>

#include <Windows.h>

#include "conf.h"

// This macro throw exception if system call fail
#define CHECK_AND_THROW(RET_FUNC_VAL) if ( ERROR_SUCCESS != RET_FUNC_VAL ) throw RET_FUNC_VAL

static void ReadValImpl(const std::string& _valName, LPBYTE _data, DWORD _size, DWORD _type, LPBYTE _defVal, bool _shouldSaveDefVal)
{
	HKEY key;

	long openStatus = RegOpenKeyEx(HKEY_CURRENT_USER, TEXT(KEY_PATH), 0, KEY_ALL_ACCESS, &key);
	if ( ERROR_SUCCESS != openStatus )
	{
		if ( ERROR_FILE_NOT_FOUND == openStatus )
		{
			if (_shouldSaveDefVal)
			{
				CHECK_AND_THROW( RegCreateKeyEx(HKEY_CURRENT_USER, TEXT(KEY_PATH), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL) );
			}
			else
			{
				memcpy(_data, _defVal, _size);
				return;
			}
		}
		else
		{
			throw openStatus;
		}
	}
	
	long getStatus = RegGetValue(HKEY_CURRENT_USER, TEXT(KEY_PATH), _valName.c_str(), RRF_RT_ANY, NULL, _data, &_size);
	if ( ERROR_SUCCESS != getStatus )
	{
		if (ERROR_FILE_NOT_FOUND == getStatus)
		{
			memcpy(_data, _defVal, _size);

			if (_shouldSaveDefVal)
			{

				CHECK_AND_THROW( RegSetValueEx(key, _valName.c_str(), 0, _type, _data, _size) );
			}
			else
			{
				return;
			}
		}
		else
		{
			throw openStatus;
		}
	}

	RegCloseKey(key);
	return;
}

//=================================================================================================

template <>
int m7::ReadVal<int>(const std::string& _valName, int _defVal, bool _shouldSaveDefVal)
{
	int data = 0;
	DWORD size = sizeof(int);

	ReadValImpl(_valName, reinterpret_cast<LPBYTE>(&data), size, REG_DWORD, reinterpret_cast<LPBYTE>(&_defVal), _shouldSaveDefVal);
	return data;
}

//=================================================================================================

template <>
std::string m7::ReadVal<std::string>(const std::string& _valName, std::string _defVal, bool _shouldSaveDefVal)
{
	char data[80] = {0};
	DWORD size = 80;
	char *def = const_cast<char*>(_defVal.c_str());
	
	ReadValImpl(_valName, reinterpret_cast<LPBYTE>(data), size, REG_SZ, reinterpret_cast<LPBYTE>(def), _shouldSaveDefVal);
	return data;
}