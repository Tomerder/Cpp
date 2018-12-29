/**************************************************************************************
    Author : Tomer Dery
    Creation date :      31.12.13
    Date last modified : 31.12.13 - 1.1.14
    Description : memory pool 
***************************************************************************************/
#ifndef __MEM_PAGE_H__
#define __MEM_PAGE_H__

#include "mem.h"

#define DEFAULT_INITIAL_PAGE_CAPACITY 10

class MemPage_t : public Memory_t {

private: 
	char* m_startOfPage;
	
	int m_capacity;
	
	static int m_defaultPageSize;
	
	//will never be use
	MemPage_t(const MemPage_t& _mem);	
	MemPage_t& operator=(const MemPage_t& _mem);
	
	//private methods
	void writeImp(const void* _dataToWrite, int _len, int _pos) ; 
	
public: 
	MemPage_t();  	
	MemPage_t(int _capacity);	
		
	virtual ~MemPage_t();	

	int getCapacity() const {return m_capacity;}
	
	bool isFull() const {return (getCurSize() == m_capacity ); } 	
	
	virtual bool write(const void* _dataToWrite, int _len) ; 
	virtual bool write(const void* _dataToWrite, int _len, int _pos) ; 
	
	virtual bool read(void* _buffer, int _len ) ; 
	virtual bool read(void* _buffer, int _len, int _pos) ; 
		
	static void setDefaultPageCapcity(int _newDefaultCapacity) { m_defaultPageSize = _newDefaultCapacity; }
	static int getDefaultPageCapcity() { return m_defaultPageSize; }	

};


	
#endif /*__MEM_PAGE_H__*/

