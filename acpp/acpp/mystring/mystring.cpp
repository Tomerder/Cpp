/************************************************************************
String class. cpp file.
Author: Dan Bar-On.
Creation Date: 12.3.14 
Modified at:
Description:
************************************************************************/
#include <string.h>
#include <assert.h>

#include "mystring.h"
using namespace std;

namespace m10{

/*-------------------------------------------------------------------------------------------*/
char* String::CreateFrom(const char* _inputString)
{
	char* tmp;

	assert(_inputString);
	tmp = new char[strlen(_inputString)+1];
	strcpy(tmp, _inputString);
	return tmp;
}
/*-------------------------------------------------------------------------------------------*/
String& String::operator= (const String& _sr)	/*Assignment operator*/	
{
	char* originalString = m_str;
	m_str = CreateFrom(_sr.m_str);
	delete originalString;
	return *this;
}
/*-------------------------------------------------------------------------------------------*/
String& String::operator= (const char* _inputString) //Assignment operator from char*
{
	delete[] m_str;
	m_str = CreateFrom(_inputString);

	return *this;
}
/*-------------------------------------------------------------------------------------------*/

} // end of namespace m10

