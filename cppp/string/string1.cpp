/**************************************************************************************
    Author : Tomer Dery
    Creation date :      12.3.14
    Date last modified : 12.3.14
    Description : string.h 
***************************************************************************************/
#include <cctype>
#include <cstring>

#include "string1.h"

using namespace std;

namespace String{

/*--------------------------------------------------------------------------------*/

#define DEBUG true

#define PRINT_D(MSG)  if (DEBUG) cout << MSG << endl;

/*--------------------------------------------------------------------------------*/

/*
String_t::String_t()   //ctor
{
	PRINT_D("in : String_t()");
	CreateFrom("");
}
*/

String_t::~String_t()    //dtor
{   
	PRINT_D("in : ~String_t()");  	
	delete[](m_str);
	m_str = 0;   
}


String_t::String_t(const char* _str)   //ctor
{
	PRINT_D("in : String_t(const char* _str)");  	
	CreateFrom(_str);
}


String_t::String_t(const String_t& _strToCpy)  //copy ctor
{
	PRINT_D("in : copy CTOR  ");
	CreateFrom(_strToCpy.m_str);
}


String_t& String_t::operator=(const String_t& _strToAssign)   //operator= 
{	
	PRINT_D("in : operator=");
	if(&_strToAssign != this){	
		delete[] m_str;	
		CreateFrom(_strToAssign.m_str);
	}
	
	return *this;
}

String_t& String_t::operator=(const char* _str)
{
	delete[] m_str;	
	CreateFrom(_str);
	
	return *this;
}


/*
const char* String_t::Cstr() const
{
	return m_str;
}
*/


int String_t::Length() const
{		
	return (strlen(m_str));	
}


/*--------------------------------------------------------------------------------*/

void String_t::CreateFrom(const char* _str)    //private method 
{		
	if(_str){
		m_str = new char[strlen(_str) + 1]; 
		strcpy(m_str, _str);
	}else{
		m_str = new char[1];
		*m_str = '\0';
	}
}

/*--------------------------------------------------------------------------------*/

char& String_t::operator[](int _index)
{
	PRINT_D("in : operator[]");
	return m_str[_index];
}

char String_t::operator[](int _index) const
{
	PRINT_D("in : operator[] const");
	return m_str[_index];
}

/*--------------------------------------------------------------------------------*/

ostream& operator<< (ostream& os, const String_t& _strToPrt)
{
	os << _strToPrt.Cstr();
	return os;
}

/*--------------------------------------------------------------------------------*/

}    /* closing namespace String */

