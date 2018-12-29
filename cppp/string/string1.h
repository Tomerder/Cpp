/**************************************************************************************
    Author : Tomer Dery
    Creation date :      12.3.14
    Date last modified : 12.3.14
    Description : string.h 
***************************************************************************************/
#ifndef __STR_H__
#define __STR_H__

#include <iostream>

/*--------------------------------------------------------------------------------*/

namespace String{

using namespace std;

class String_t{

private: 
	char* m_str;
	
	/*sets DM m_str according to parameter , if parameter is NULL - sets m_str to '\0'  */
	void CreateFrom(const char* _str);
	
public: 
	//String_t();
	~String_t();
	
	String_t(const char* _str = "");  
	
	String_t(const String_t& _strToCpy);
	
	String_t& operator=(const String_t& _strToAssign);
	
	/*if wouldnt have been defined => implicit call of ctor(char*) for creating temp string obj => dtor of temp string obj*/
	String_t& operator=(const char* _str);
	
	const char* Cstr() const  { return m_str; }
	
	int Length() const;	
	
	char& operator[](int _index);
	
	//could have returned const char& (in this case return char by val is less expensive)
	char operator[](int _index) const;
	
	/*should not be friend because there is a method Cstr that returns the DM*/
	//friend ostream& operator<< (ostream& stream, const String_t& _strToPrt);
	
};

//non-member non-friend function
ostream& operator<< (ostream& stream, const String_t& _strToPrt);
		
}   /* closing namespace String */
	
	
#endif /*__STR_H__*/


