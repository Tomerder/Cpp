/***************************************************************************
    Author: Stav Ofer
    Creation date:  		2013-10-31    
    Last modified date:		2013-10-31
    Description: 	class String declaration
****************************************************************************/

#ifndef __STRING_H__
#define __STRING_H__

#include <cstring>

class String;

// print
std::ostream& operator << (std::ostream& _os, String& _str);


class String
{
public:
	// CTOR, DTOR
	explicit String();
	explicit String(const char* _other);
			 String(const String& _other);
	~String();
	
	// assignment
	String& operator = (const char* _other);
	String& operator = (const String& _other);
	
	inline const char* 	CString() const; // get the char* string
	inline size_t 		Size() const; 	 // get string length
	
private:
	char* m_str;
	
	void PutString(const char* _str);	// service functions
	void PutStringEmpty();				
};
/*######################################################################*/	

// get string length
inline size_t String:: Size() const
{
	return strlen(m_str);
}

// get the char* string
inline const char* String:: CString() const
{
	return m_str;
}

#endif /* __STRING_H__ */
