/************************************************************************
String class. h file.
Author: Dan Bar-On.
Creation Date: 12.3.14 
Modified at:
Description:
************************************************************************/
#ifndef __MyString_H__
#define __MyString_H__

#include <stdlib.h>
#include <string.h>
#include <iostream> 

using namespace std;

namespace m10{

class String {
public:
	inline String(const char* _inputString = "");		//CTOR from char*. When _inputString invalid - undefined behavior

	inline String(const String& _sr); 					//copy CTOR
	String& operator= (const String& _sr);				//Assignment operator
	String& operator= (const char* _inputString);		//Assignment operator
	inline ~String();									//DTOR

	size_t Length() const;								//If was deleted returns 0
	inline const char* Cstr() const;					//If was deleted returns '\0'
	inline const char& operator[] (size_t _pos) const;	//If out of range - undefined behavior
	inline char& operator[] (size_t _pos);				//If out of range - undefined behavior
	
	inline friend ostream& operator<< (ostream& _out, const String& _str);
private:
	char* m_str;
	char* CreateFrom(const char* _inputString);
};

// inline functions
/*-------------------------------------------------------------------------------------------*/
inline String::~String()
{
	delete[] m_str;
	m_str = NULL;	// Cause of this can delete twice.
}
/*-------------------------------------------------------------------------------------------*/
inline String::String(const String& _sr) /*copy CTOR*/
{
	m_str = CreateFrom(_sr.m_str);
}
/*-------------------------------------------------------------------------------------------*/
inline String::String(const char* _inputString) /*CTOR from char*  */
{
	m_str = CreateFrom(_inputString);
}
/*-------------------------------------------------------------------------------------------*/
inline const char* String::Cstr() const
{
	return m_str;
}
/*-------------------------------------------------------------------------------------------*/
inline const char& String::operator[] (size_t _pos) const
{
	return m_str[_pos];
}	

inline char& String::operator[] (size_t _pos)
{
	return const_cast<char&> (const_cast<const String&>(*this)[_pos]);	//I wanted to try it.
}
/*-------------------------------------------------------------------------------------------*/
inline ostream& operator<< (ostream& _out, const String& _sr)
{
	_out << _sr.m_str;
	return _out;
}
/*-------------------------------------------------------------------------------------------*/
inline size_t String::Length() const
{
	return strlen(m_str);
}
/*-------------------------------------------------------------------------------------------*/


} // end of namespace m10
#endif	// #ifndef __MyString_H__

