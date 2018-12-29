/*************************************************
    Author: Yiftach Ariel
    Creation date :      9.12.13
    Last modified date:  10.12.13
    Description : conf h-file.

	CONF_VAL is a macro to load a value from configuration file.
	1'st parameter is the type of the variable.
	2'nd parameter is the name of the variable.
	3'rd parameter is the default value of the variable, and is used in case that the value isn't found in the configuration file.
	4'th parameter is boolean that tell if we want to save the def_value in the configuration file in case it doesn't exist there.

	Usage: To load a value named VAL then put in the h-file CONF_VAL(int, VAL, 5);
	If VAL doesn't exist in the configuration file then it will get the value '5', the default value.

	Supported types: int, string
**************************************************/
#ifndef __CONF_H__
#define __CONF_H__

#ifndef KEY_PATH
#define KEY_PATH "Software\\Experis"
#endif

#define CONF_VAL(TYPE, NAME, DEF_VALUE, SAVE) static const TYPE NAME = m7::ReadVal<TYPE>(#NAME, DEF_VALUE, SAVE)

//=================================================================================================

namespace m7
{
	template <class T>
	T ReadVal(const std::string& _valName, T _defVal, bool _shouldSaveDefVal);

	// Decleration of ReadVal function
	template <>
	int ReadVal<int>(const std::string& _valName, int _defVal, bool _shouldSaveDefVal);
	template <>
	std::string ReadVal<std::string>(const std::string& _valName, std::string _defVal, bool _shouldSaveDefVal);

//=================================================================================================

template <class T>
T ReadVal<T>(const std::string& _valName, T _defVal, bool _shouldSaveDefVal)
{
	ThereIsNoSupport x1;	// If you got a compilation error here that's because you've tried to declare an object with no support 
}

} // namespace m7

#endif // #define __CONF_H__