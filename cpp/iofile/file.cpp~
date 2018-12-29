#include <string.h>
#include <iostream>

#include "file.h"

using namespace std;

#define FAIL -1

/*--------------------------------------------------------------------------------*/

virtIO_t::virtIO_t(char* _pathName, char* _access)
{
	m_pathName = 0;
	Open(_pathName, _access);
}

/*--------------------------------------------------------------------------------*/	

virtIO_t::~virtIO_t()
{
	delete[] m_pathName;
	m_pathName = 0;
	
	fclose (m_file);
}

/*--------------------------------------------------------------------------------*/	

void virtIO_t::Open(char* _pathName, char* _access) 
{
	if( ! strcmp(_access , "r") ){
		setAccess(READ);
	}else if( ! strcmp(_access , "w") ){
		setAccess(WRITE);
	}else if( ! strcmp(_access , "w+") ){
		setAccess(READ_WRITE);
	}else{
		setStatus(CANT_OPEN_FILE_E);
		return;
	}
	
	m_file = fopen (_pathName, _access);
	if(!m_file){
		setStatus(CANT_OPEN_FILE_E);
		return;
	}
	
	createName( _pathName);
	
	setStatus(OK_E);
}



void virtIO_t::createName(const char* _str)    //private method 
{		
	if(_str){
		m_pathName = new char[ strlen(_str) + 1]; 
		strcpy(m_pathName, _str);
	}else{
		m_pathName = new char;
		*m_pathName = '\0';
	}
}

/*--------------------------------------------------------------------------------*/	

int virtIO_t::setLocation ( int _offset, int _base) 
{
	int toRet = 0;

	if (_base < SEEK_SET && _base > SEEK_END){
		setStatus(BAD_ACCESS_E);
		return FAIL;
	}

	int loc =  getLocation();
	int len = getLength();

	if( ( (_base == SEEK_SET ||_base == SEEK_END) && (_offset > len) )    ||    ( (_base == SEEK_CUR) && ( loc + _offset > len ) ) ){ 
		setStatus(BAD_ACCESS_E);
		return FAIL;		
	}

	toRet = fseek ( m_file, _offset , _base); 
		
	if(toRet != OK_E ){
		setStatus(BAD_ACCESS_E);
	}
		
	return toRet;
}


int virtIO_t::getLength() const
{	
	int curLoc = ftell(m_file);  //save cur loc
	fseek ( m_file, 0, SEEK_SET); 
	int beg = ftell(m_file);        //begin
	fseek ( m_file, 0, SEEK_END); 
	int end = ftell(m_file);        //end
	fseek ( m_file, curLoc, SEEK_SET); //return to original loc
	
	return end - beg;
}

/*--------------------------------------------------------------------------------*/

virtIO_t& virtIO_t::operator>>(void* _ptrToRead)
{
	m_buffAdr = _ptrToRead;
	m_readWriteFlag = READ;
	
	return *this;
}


virtIO_t& virtIO_t::operator<<(void* _ptrToWrt)
{
	m_buffAdr = _ptrToWrt;
	m_readWriteFlag = WRITE;
	
	return *this;
}


virtIO_t& virtIO_t::operator,(int _len)
{
	if(m_readWriteFlag == WRITE){
		write(m_buffAdr, _len);
	}else if(m_readWriteFlag == READ){
		read(m_buffAdr, _len);
	}

	return *this;
}

/*--------------------------------------------------------------------------------*/









	
	

