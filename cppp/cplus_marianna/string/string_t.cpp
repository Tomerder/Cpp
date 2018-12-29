#include <iostrem>
#include <string.h>
using namespace std;

#include "string_h"


string_h::string_h()
{
	m_str = 0;
}
string_h::string_h(char* _other)
{
	m_str = new char[strlen(_other)+1];
	strcpy(m_str,_other);
}

string_h::string_h(const string_h& _other)
{
	m_str = new char[strlen(_other.m_str)+1];
	strcpy(m_str,_other.m_str);
}

string_h::~string_h()
{
	delete[] m_str;
	m_str = 0;
}

string_h	string_h::operator=(const string_h& _other)
{
	if(*this != _other)
	{
		delete[] m_str;
		m_str = new char[strlen(_other.m_str)+1];
		strcpy(m_str,_other.m_str);
	}
	
	return *this;
}
		
inline int	string_h::Lenth()const
{
	return strlenth(m_str);  
}

inline const string_h& GetString()const 
{
	return m_str;
	
}



ostrem & operator<<(ostrem& os, const string_h _str)
{
	os << _str.m_str<< endl;
}		
