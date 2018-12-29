/**************************************************************************************
    Author : Tomer Dery
    Creation date :      26.12.13
    Date last modified : 26.12.13
    Description : string.h 
***************************************************************************************/
#ifndef __STR_H__
#define __STR_H__


class String_t{

private: 
	char* m_str;
	
	static bool m_caseSens;
	
	/*sets DM m_str according to parameter , if parameter is NULL - sets m_str to '\0'  */
	void createFrom(const char* _str);
	
	/*pre appand  _strToPrepend to m_str*/ 
	void prependImp(const char* _strToPrepend);
	
	/* gets chat* and change the string to lower case*/
	void toLowerStr(char* _str) const;
	
	/* compere between _str1 and _str2 without case sensitive <=> strcasecmp*/
	int strcmpNotCase(const char* _str1, const char* _str2) const;
	
	/* strstr without case sensitive*/
	char* strstrNotCase(const char* _str1, const char* _str2) const;
	
public: 
	String_t();
	~String_t();
	
	String_t(const char* _str);
	
	String_t(const String_t& _strToCpy);
	
	const String_t& operator=(const String_t&);
	
	bool operator<(const String_t& _toComp) const;
	bool operator>(const String_t& _toComp) const;
	bool operator<=(const String_t& _toComp) const;
	bool operator>=(const String_t& _toComp) const;
	bool operator==(const String_t& _toComp) const;
	bool operator!=(const String_t& _toComp) const;
	
	void setName(const char* _str);
	const char* getName() const;
	
	int length() const;
	
	void setLowerCase();
	void setUpperCase();
	
	void prepend(const char* _strToPrepend);
	void prepend(const String_t& _stringToPrepend);

	static void setCaseSens(bool _caseSens);	
	static bool getCaseSens();

	bool contains(const char* _strToChk) const;
	
	
};


	
#endif /*__STR_H__*/


