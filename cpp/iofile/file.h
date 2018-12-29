/**************************************************************************************
    Author : Tomer Dery
    Creation date :      02.01.14
    Date last modified : 02.01.14
    Description : io file
***************************************************************************************/
#ifndef __VIR_IO_H__
#define __VIR_IO_H__

#include<stdio.h>

#include "io.h"
 
class virtIO_t : public IO_ABS{   //abstract

private: 	
	FILE* m_file;
	
	char* m_pathName;
	
	//for reading writing void* 
	void* m_buffAdr;
	bool m_readWriteFlag;
	
	//will never be used
	virtIO_t(const virtIO_t& _io);	
	virtIO_t& operator=(const virtIO_t& _io);	
	
	//private methods
	void createName(const char* _str)	;
	
	//private read write methods - called from operators
	virtual int write(const void* _dataToWrite, int _len) = 0 ; 	
	virtual int read(void* _dataToRead, int _len) = 0 ; 

protected:
	FILE* getFile() const {return m_file;} 
	void setBuffAdr(void* _adr)  {m_buffAdr = _adr;}	
	void setreadWriteFlag(bool _flag)  {m_readWriteFlag = _flag;}

public: 
	virtIO_t() : IO_ABS(READ) , m_file(0)  {} 	
	virtIO_t(char* _pathName, char* _access) ;	
	
	virtual ~virtIO_t();	
		
	void Open(char* _pathAndName, char* _access) ; 
	void Close() { fclose (m_file); }	
	
	int getLength() const;
	bool isEOF() const { return feof(m_file); } 	
	
	char* getPathName() const {return m_pathName;}	

	int getLocation() const {return ftell(m_file); }
	int setLocation ( int _offset, int _base);


	//operators that saves adr and read/write flag 
	virtIO_t& operator>>(void* _ptrToRead);
	virtIO_t& operator<<(void* _ptrToWrt);	
	//operator that calls write/read methods on derived classes - params:(adr,len)
	virtIO_t& operator,(int _len);

	//pure virtual methods for reading from file 
	virtual virtIO_t& operator>>(int& _intToRead) = 0;
	virtual virtIO_t& operator>>(unsigned int& _uintToRead) = 0;
	virtual virtIO_t& operator>>(char& _charRead) = 0;
	virtual virtIO_t& operator>>(unsigned char& _ucharRead) = 0;
	virtual virtIO_t& operator>>(short& _shortRead) = 0;
	virtual virtIO_t& operator>>(unsigned short& _ushortRead) = 0;
	virtual virtIO_t& operator>>(long& _longRead) = 0;
	virtual virtIO_t& operator>>(unsigned long& _ulongRead) = 0;
	virtual virtIO_t& operator>>(float& _floatRead) = 0;
	virtual virtIO_t& operator>>(double& _doubleRead) = 0;
	
	//pure virtual methods for writing to file 
	virtual virtIO_t& operator<<(int _intToWrt)  = 0;
	virtual virtIO_t& operator<<(unsigned int _uintToWrt) = 0;
	virtual virtIO_t& operator<<(char _charWrt) = 0;
	virtual virtIO_t& operator<<(unsigned char _ucharWrt) = 0;
	virtual virtIO_t& operator<<(short _shortWrt) = 0;
	virtual virtIO_t& operator<<(unsigned short _ushortWrt) = 0;
	virtual virtIO_t& operator<<(long _longWrt) = 0;
	virtual virtIO_t& operator<<(unsigned long _ulongWrtWrt) = 0;
	virtual virtIO_t& operator<<(float _floatWrt) = 0;
	virtual virtIO_t& operator<<(double _doubleWrt) = 0;
	

};

	
#endif /*__VIR_IO_H__*/


