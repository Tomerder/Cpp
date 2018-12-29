/**************************************************************************************
    Author: Marianna Shvartsman
    Creation date :      2013-12-10
    Last modified date: 2013-12-10 
    Description : Registry 
***************************************************************************************/
#include <windows.h>
using namespace std;

#include "config.h"
using namespace config_m7;

// This macro throw exception if system call fail
#define CHECK_AND_THROW(FUNC_VAL) if ( ERROR_SUCCESS != FUNC_VAL ) throw FUNC_VAL

#define BUFF_SIZE 64
//**************************************************************************************
//	ReadValAlgorithm
//**************************************************************************************
static void ReadValAlgorithm(const std::string& _name, LPBYTE _data, DWORD _size, DWORD _type, LPBYTE _defValue)
{
	HKEY key;

	long openErr = RegOpenKeyEx(    
								HKEY_CURRENT_USER,				   //_In_        HKEY hKey,
								TEXT(CONFIG_PATH),				   //_In_opt_    LPCTSTR lpSubKey,
								0,								   //_Reserved_  DWORD ulOptions,
								KEY_ALL_ACCESS,                    //_In_        REGSAM samDesired,
								&key );                            //_Out_       PHKEY phkResult

	if ( ERROR_SUCCESS != openErr )
	{
		if ( ERROR_FILE_NOT_FOUND == openErr )
		{
				memcpy(_data, _defValue, _size);
				return;
		}

		else
		{
			throw openErr;
		}
	}
	
	long getValErr = RegGetValue(     
								 HKEY_CURRENT_USER,			//_In_         HKEY hkey,
								 TEXT(CONFIG_PATH),			//_In_opt_     LPCTSTR lpSubKey,
								 _name.c_str(),			    //_In_opt_     LPCTSTR lpValue,
								 RRF_RT_ANY,				//_In_opt_     DWORD dwFlags,
								 NULL,						//_Out_opt_    LPDWORD pdwType,
								 _data,						//_Out_opt_    PVOID pvData,
								  &_size);					//_Inout_opt_  LPDWORD pcbData


	if ( ERROR_SUCCESS != getValErr )
	{
		if (ERROR_FILE_NOT_FOUND == getValErr)
		{
			memcpy(_data, _defValue, _size);
			return;
		}
		else
		{
			throw getValErr;
		}
	}

	RegCloseKey(key);
	return;
}


//**************************************************************************************
//	TYPE == int
//**************************************************************************************
template <>
int ReadVal<int>(std::string& _name, int _defValue)
{
	int data = 0;
	DWORD size = sizeof(int);

	ReadValAlgorithm(_name, reinterpret_cast<LPBYTE>(&data), size, REG_DWORD, reinterpret_cast<LPBYTE>(&_defValue));
	return data;
}

//**************************************************************************************
//	TYPE == string
//**************************************************************************************
template <>
std::string ReadVal<std::string>(std::string& _name, std::string _defValue)
{
	char data[BUFF_SIZE] = {0};
	DWORD size = BUFF_SIZE;
	char *def = const_cast<char*>(_defValue.c_str());
	
	ReadValAlgorithm(_name, reinterpret_cast<LPBYTE>(data), size, REG_SZ, reinterpret_cast<LPBYTE>(def));
	return data;
}

