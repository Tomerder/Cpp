/**************************************************************************************
    Author: Marianna Shvartsman
    Creation date :      2013-12-10
    Last modified date: 2013-12-10 
    Description : Registry
***************************************************************************************/
#ifndef __CONFIG_H__
#define __CONFIG_H__
#include <string>

#ifndef CONFIG_PATH
#define CONFIG_PATH "Software\\Experis\\h17"
#endif

#define CONF_VAL(TYPE,VAR_NAME,DEF_VAL)		static const TYPE VAR_NAME = config_m7::ReadVal<TYPE>(#VAR_NAME, DEF_VAL)

namespace config_m7
{
	template <class T>
	T ReadVal(std::string& _name, T _defvalue);

	template <>
	int ReadVal<int>(std::string& _name, int _defvalue);

	template <>
	std::string ReadVal<std::string>(std::string& _name, std::string _defvalue);
}

//implementation of ReadVal if the TYPE != int or string
template <class T>
T ReadVal(std::string& _name, T _defvalue) // you got a compilation error here, because you type of your value not no support
{
	ThereIsNoSupport x1;
}

#endif //__CONFIG_H__