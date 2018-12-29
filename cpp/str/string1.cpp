#include <string.h>
#include <ctype.h>

#include "string1.h"


/*--------------------------------------------------------------------------------*/

bool String_t::m_caseSens = true;

/*--------------------------------------------------------------------------------*/

String_t::String_t()   //ctor
{
	 createFrom("");
}


String_t::~String_t()    //dtor
{   		  	
	delete[](m_str);
	m_str = NULL;   
}


String_t::String_t(const char* _str)   //ctor
{
	createFrom(_str);
}


String_t::String_t(const String_t& _strToCpy)  //copy ctor
{
	createFrom(_strToCpy.m_str);
}


const String_t& String_t::operator=(const String_t& _strToCpy)   //operator= 
{	
	if(&_strToCpy != this){	
		delete[] m_str;	
		createFrom(_strToCpy.m_str);
	}
	
	return *this;
}


void String_t::setName(const char* _str)
{	
	delete[] m_str;
	createFrom(_str);
}


const char* String_t::getName() const
{
	return m_str;
}


int String_t::length() const
{		
	return (strlen(m_str));	
}


/*--------------------------------------------------------------------------------*/

void String_t::createFrom(const char* _str)    //private method 
{		
	if(_str){
		m_str = new char( strlen(_str) + 1); 
		strcpy(m_str, _str);
	}else{
		m_str = new char(1);
		*m_str = '\0';
	}
}


/*--------------------------------------------------------------------------------*/


void String_t::toLowerStr(char* _str) const   //private method
{
	int i=0;
	char c;

	while( (c = _str[i])  != '\0'){
		if(isupper(c)){
			_str[i] = tolower(c);	
		}
		i++;
	}
}


void String_t::setLowerCase()
{	
	toLowerStr(m_str);
}



void String_t::setUpperCase()
{	
	int i=0;
	char c;
	while( (c = m_str[i])  != '\0'){
		if(islower(c)){
			m_str[i] = toupper(c);	
		}
		i++;
	}
}

/*--------------------------------------------------------------------------------*/


void String_t::prependImp(const char* _str)   
{
	int len;
	char* newStr;	

	len = strlen(_str) + strlen(m_str) + 1; 	
	newStr = new char(len);

	strcpy(newStr, _str);            //newStr = _str

	newStr = strcat(newStr,m_str);   //newStr += m_str 

	createFrom(newStr);
	
	delete[] newStr;
}



void String_t::prepend(const char* _str)
{
	
	if(!_str){
		return;
	}
	
	prependImp(_str);

}


void String_t::prepend(const String_t& _strToPrepend)
{
	const char* parStr = _strToPrepend.getName();
	
	if(! parStr){
		return;
	}
	
	prependImp(parStr);	


}



/*--------------------------------------------------------------------------------*/


void String_t::setCaseSens(bool _caseSens)
{
	m_caseSens =  _caseSens; 
}


bool String_t::getCaseSens(){
	return m_caseSens;
}


/*--------------------------------------------------------------------------------*/


bool String_t::contains(const char* _strToChk) const{
	char* str;
	
	if(m_caseSens){
		str = strstr(m_str, _strToChk);
	}else{
		str = strstrNotCase(m_str, _strToChk);
	}
	
	if(str){
		return true;
	}else{
		return false;
	}

}


/*--------------------------------------------------------------------------------*/


bool String_t::operator<(const String_t& _toComp) const
{
	if(m_caseSens){
		return ( strcmp(m_str, _toComp.getName()) < 0);
	}else{	
		return ( strcmpNotCase( m_str , _toComp.getName()  ) < 0);    //return ( strcasecmp( m_str , _toComp.getName()) == 0);
	}	
}

/*--------------------------------------------------------------------------------*/


bool String_t::operator>(const String_t& _toComp) const
{
	if(m_caseSens){
		return ( strcmp(m_str, _toComp.getName()) > 0);
	}else{	
		return ( strcmpNotCase( m_str , _toComp.getName()  ) > 0);    //return ( strcasecmp( m_str , _toComp.getName()) == 0);
	}	
}

/*--------------------------------------------------------------------------------*/


bool String_t::operator<=(const String_t& _toComp) const
{
	if(m_caseSens){
		return ( strcmp(m_str, _toComp.getName()) <= 0);
	}else{	
		return ( strcmpNotCase( m_str , _toComp.getName()  ) <= 0);    //return ( strcasecmp( m_str , _toComp.getName()) == 0);
	}	
}

/*--------------------------------------------------------------------------------*/


bool String_t::operator>=(const String_t& _toComp) const
{
	if(m_caseSens){
		return ( strcmp(m_str, _toComp.getName()) >= 0);
	}else{	
		return ( strcmpNotCase( m_str , _toComp.getName()  ) >= 0);    //return ( strcasecmp( m_str , _toComp.getName()) == 0);
	}	
}

/*--------------------------------------------------------------------------------*/


bool String_t::operator==(const String_t& _toComp) const
{
	if(m_caseSens){
		return ( strcmp(m_str, _toComp.getName()) == 0);
	}else{	
		return ( strcmpNotCase( m_str , _toComp.getName()  ) == 0);    //return ( strcasecmp( m_str , _toComp.getName()) == 0);
	}	
}

/*--------------------------------------------------------------------------------*/


bool String_t::operator!=(const String_t& _toComp) const
{
	if(m_caseSens){
		return ( strcmp(m_str, _toComp.getName()) != 0);
	}else{	
		return ( strcmpNotCase( m_str , _toComp.getName()  ) != 0);    //return ( strcasecmp( m_str , _toComp.getName()) == 0);
	}	
}

/*--------------------------------------------------------------------------------*/

int String_t::strcmpNotCase(const char* _str1, const char* _str2) const     //private method 
{
	int result;
	char* str1Chk = new char(strlen(_str1 +1));
	char* str2Chk = new char(strlen(_str2 +1));  
	
	strcpy(str1Chk, _str1);
	strcpy(str2Chk, _str2);
	
	toLowerStr(str1Chk);
	toLowerStr(str2Chk);
	
	result =  strcmp(str1Chk, str2Chk );
	
	delete[] (str1Chk);
	delete[] (str2Chk);
	
	return result;

}


char* String_t::strstrNotCase(const char* _str1, const char* _str2) const     //private method 
{
	char* result;
	char* str1Chk = new char(strlen(_str1 +1));
	char* str2Chk = new char(strlen(_str2 +1));  
	
	strcpy(str1Chk, _str1);
	strcpy(str2Chk, _str2);
	
	toLowerStr(str1Chk);
	toLowerStr(str2Chk);
	
	result =  strstr(str1Chk, str2Chk );
	
	delete[] (str1Chk);
	delete[] (str2Chk);
	
	return result;
}




/*--------------------------------------------------------------------------------*/




