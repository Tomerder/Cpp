/**************************************************************************************
    Author : Tomer Dery
    Creation date :      31.12.13
    Date last modified : 31.12.13 - 1.1.14
    Description : memory pool 
***************************************************************************************/
#ifndef __MEM_PAGE_H__
#define __MEM_PAGE_H__

#include "mem.h"

class MemPage_t : public Memory_t {

private: 
	char* m_startOfPage;
	
	int m_capacity;
	
	//will never be use
	MemPage_t(const MemPage_t& _mem);	
	MemPage_t& operator=(const MemPage_t& _mem);
	MemPage_t(); 
	
	//private methods
	void writeImp(const void* _dataToWrite, int _len, int _pos) ; 
	void* readImp(int _pos) const; 
	
public: 
	 	
	MemPage_t(int _capacity);	
		
	virtual ~MemPage_t();	

	int getCapacity() const {return m_capacity;}
	
	bool isFull() const {return (getCurSize() == m_capacity ); } 	
	
	virtual bool write(const void* _dataToWrite, int _len) ; 
	virtual bool write(const void* _dataToWrite, int _len, int _pos) ; 
	
	virtual void* read(int _len) ; 
	virtual void* read(int _len, int _pos) ; 

};


	
#endif /*__MEM_PAGE_H__*/


