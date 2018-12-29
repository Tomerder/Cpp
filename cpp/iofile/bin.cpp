#include <string.h>
#include <iostream>

#include "bin.h"

using namespace std;

/*--------------------------------------------------------------------------------*/


int binIO_t::write(const void* _dataToWrite, int _len) 	
{
	int writeRet = 0;

	if(!isWriteLegal() ){
		setStatus(WRITE_ERR_E); 
		return 0;
	}	
	
	writeRet = fwrite(_dataToWrite, _len, 1, getFile() ) ;
	
	if(writeRet != 1){
		setStatus(WRITE_ERR_E); 
	}	

	return writeRet;
}



int binIO_t::read(void* _dataToRead, int _len)  
{
	int readRet = 0;
	
	if(!isReadLegal() ){
		setStatus(READ_ERR_E); 
		return 0;
	}	

	readRet = fread(_dataToRead, _len, 1, getFile() );
	
	if(readRet != 1){
		setStatus(READ_ERR_E); 
	}

	return readRet;
}


/*--------------------------------------------------------------------------------*/


virtIO_t& binIO_t::operator>>(int& _intToRead)
{	
	read(&_intToRead, sizeof(int));   //(*this) >> &_intToRead , sizeof(int);

	return *this;
}


virtIO_t& binIO_t::operator>>(unsigned int& _uintToRead){
	read(&_uintToRead, sizeof(unsigned int));  
	return *this;
}

virtIO_t& binIO_t::operator>>(char& _charRead){
	read(&_charRead, sizeof(char));   
	return *this;
}

virtIO_t& binIO_t::operator>>(unsigned char& _ucharRead){
	read(&_ucharRead, sizeof(unsigned char));  
	return *this;
}

virtIO_t& binIO_t::operator>>(short& _shortRead){
	read(&_shortRead, sizeof(short));   
	return *this;
}

virtIO_t& binIO_t::operator>>(unsigned short& _ushortRead) {
	read(&_ushortRead, sizeof(unsigned short));   
	return *this;
}

virtIO_t& binIO_t::operator>>(long& _longRead){
	read(&_longRead, sizeof(long));   
	return *this;
}

virtIO_t& binIO_t::operator>>(unsigned long& _ulongRead){
	read(&_ulongRead, sizeof(unsigned long));  
	return *this;
}

virtIO_t& binIO_t::operator>>(float& _floatRead){
	read(&_floatRead, sizeof(float));  
	return *this;
}

virtIO_t& binIO_t::operator>>(double& _doubleRead){
	read(&_doubleRead, sizeof(double));  
	return *this;
}


/*--------------------------------------------------------------------------------*/

virtIO_t& binIO_t::binIO_t::operator<<(int _intToWrt)
{	
	write(&_intToWrt, sizeof(int));   //*this << &_intToWrt , sizeof(int);

	return *this;
}


virtIO_t& binIO_t::operator<<(unsigned int _uintToWrt){
	write(&_uintToWrt, sizeof(unsigned int)); 
	return *this;
}

virtIO_t& binIO_t::operator<<(char _charWrt){
	write(&_charWrt, sizeof(char)); 
	return *this;
}

virtIO_t& binIO_t::operator<<(unsigned char _ucharWrt){
	write(&_ucharWrt, sizeof(unsigned char)); 
	return *this;
}

virtIO_t& binIO_t::operator<<(short _shortWrt){
	write(&_shortWrt, sizeof(short)); 
	return *this;
}

virtIO_t& binIO_t::operator<<(unsigned short _ushortWrt){
	write(&_ushortWrt, sizeof(unsigned short)); 
	return *this;
}

virtIO_t& binIO_t::operator<<(long _longWrt){
	write(&_longWrt, sizeof(long)); 
	return *this;
}

virtIO_t& binIO_t::operator<<(unsigned long _ulongWrtWrt){
	write(&_ulongWrtWrt, sizeof(unsigned long)); 
	return *this;
}

virtIO_t& binIO_t::operator<<(float _floatWrt){
	write(&_floatWrt, sizeof(float)); 
	return *this;
}

virtIO_t& binIO_t::operator<<(double _doubleWrt){
	write(&_doubleWrt, sizeof(double)); 
	return *this;
}
/*--------------------------------------------------------------------------------*/


