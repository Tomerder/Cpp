/***************************************************************************
    Author: Stav Ofer
    Creation date:  		2013-10-31    
    Last modified date:		2013-10-31
    Description: 	class String implementation
****************************************************************************/

#include <cstring>
#include <iostream>

#include "../AInclude/String.h"


// print
std::ostream operator << (std::ostream _os, String& _str)
{
	return _os << _str.CString();
}


/*######################################################################*/	
/*							CTOR, DTOR									*/
/*######################################################################*/	

// default CTOR
String:: String()
{
	m_str = new char[1];
	*m_str = 0;
}

// CTOR from char*
String:: String(const char* _other)
{
	PutString(_other);
}

// copy CTOR
String:: String(const String& _other)
{
	PutString(_other.CString());
}

// DTOR
String:: ~String()
{
	delete m_str;
	m_str = 0;
}


/*######################################################################*/	
/*								ASSIGNMENT								*/
/*######################################################################*/	

// from char* 
String& String:: operator = (const char* _other)
{
	char* temp = m_str;
	
	PutString(_other);
	delete[] temp;
	
	return *this;
}

// from String
String& String:: operator = (const String& _other)
{
	char* temp = m_str;
	
	PutString(_other.CString());
	delete[] temp;
	
	return *this;
}

/*######################################################################*/	
/*								OTHER									*/
/*######################################################################*/	

// get string length
size_t String:: Size() const
{
	return strlen(m_str);
}


/*######################################################################*/	
/*								PRIVATE									*/
/*######################################################################*/	

// service func
void String:: PutString(const char* _str)
{
	int len = strlen(_str) + 1;
	m_str = new char[len];
	strcpy(m_str, _str);
	m_str[len] = 0;
}

