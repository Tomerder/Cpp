/**************************************************************************************
    Author : Tomer Dery
     Creation date :      02.01.14
    Date last modified : 02.01.14
    Description : io file
***************************************************************************************/
#ifndef __BINARY_IO_H__
#define __BINARY_IO_H__

#include "file.h" 		
 
class binIO_t : public virtIO_t{  

private: 	
	//private read write methods - called from operators	
	virtual int write(const void* _dataToWrite, int _len)  ; 	
	virtual int read(void* _dataToRead, int _len)  ; 

public: 	
	binIO_t();
	binIO_t(char* _pathName, char* _access) : virtIO_t(_pathName, _access) {}	
	
	virtual ~binIO_t() {} 	

	//operators override
	virtual virtIO_t& operator>>(int& _intToRead);
	virtual virtIO_t& operator<<(int _intToWrt);

	virtual virtIO_t& operator>>(unsigned int& _uintToRead);
	virtual virtIO_t& operator>>(char& _charRead);
	virtual virtIO_t& operator>>(unsigned char& _ucharRead);
	virtual virtIO_t& operator>>(short& _shortRead);
	virtual virtIO_t& operator>>(unsigned short& _ushortRead) ;
	virtual virtIO_t& operator>>(long& _longRead);
	virtual virtIO_t& operator>>(unsigned long& _ulongRead);
	virtual virtIO_t& operator>>(float& _floatRead);
	virtual virtIO_t& operator>>(double& _doubleRead);

	virtual virtIO_t& operator<<(unsigned int _uintToWrt);
	virtual virtIO_t& operator<<(char _charWrt);
	virtual virtIO_t& operator<<(unsigned char _ucharWrt);
	virtual virtIO_t& operator<<(short _shortWrt);
	virtual virtIO_t& operator<<(unsigned short _ushortWrt);
	virtual virtIO_t& operator<<(long _longWrt);
	virtual virtIO_t& operator<<(unsigned long _ulongWrtWrt);
	virtual virtIO_t& operator<<(float _floatWrt);
	virtual virtIO_t& operator<<(double _doubleWrt);
};

	
#endif /*__BINARY_IO_H__*/

