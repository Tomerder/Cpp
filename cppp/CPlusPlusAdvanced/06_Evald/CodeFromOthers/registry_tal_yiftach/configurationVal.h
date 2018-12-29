// Name: Tal Krig
// Date: 2013-12-09
// Description: Configuration Val General Definitions

#ifndef __CONFIGURATION_VAL__
#define __CONFIGURATION_VAL__

#include <string>

//-------------------------------------------------------------------------------------------------
// DESCRIPTION: 
//		Allow changing const static parameters without re - compiling
//		If no saved value exist, default parameter (supply by the caller) will be returned.
//		Available only for string and int data types. Using with diffrent types will cause compliation error.
//
// NOTE:
//		Data is poped from external storage, therfore require system call which  cost time and might return error.
//		Data configuration path, default value is "Software\\H17\\MyKey"
//		Path can be modified by defining  __CONFIGURATION_PATH__ in preprocessor. 	
//
// USE INSTRUCTION:
//		Replace variable definition and initialization:
//			static const data_type VAR_NAME = defaltValue;
//		with:
//			CONF_VAL(data_type,VAR_NAME,defaultValue);
//
// EXAMPLE:
//		CONF_VAL(int,SIZE,3);
//		CONF_VAL(string,MESSAGE,"hello");
//-------------------------------------------------------------------------------------------------

#ifndef __CONFIGURATION_PATH__
#define __CONFIGURATION_PATH__	"Software\\H17\\MyKey"
#endif //__CONFIGURATION_PATH__

#define CONF_VAL(TYPE,NAME,DEFAULT_VALUE)	static const TYPE NAME = ReadVal<TYPE>(#NAME, DEFAULT_VALUE);

template <class T>
T ReadVal(std::string _keyName, T _defaultVal)
{
	NotSupportedType x; // Compilation ERROR due to not supported data type. Currentlly only string and float available.
}

template <>
int ReadVal<int> (std::string _keyName, int _defaultVal);

template <>
std::string ReadVal<std::string> (std::string _keyName, std::string _defaultVal);

#endif //__CONFIGURATION_VAL__