/**************************************************************************************
    Author : Tomer Dery
    Creation date :      31.12.13
    Date last modified : 31.12.13 - 1.1.14
    Description : memory pool 
***************************************************************************************/
#ifndef __MEM_POOL_H__
#define __MEM_POOL_H__

#include<list>

#include "mem.h"
#include "page.h"

using namespace std;

/*will be used for constractor if no size is given 
  initializes m_pagesCapacity*/
#define DEFAULT_INITIAL_PAGE_CAPACITY 10

class MemPool_t : public Memory_t {

private: 
	list<MemPage_t*> m_pages;
	
	int m_pagesCapacity;

	//will never be use
	MemPool_t(const MemPool_t& _pool);	
	MemPool_t& operator=(const MemPool_t& _pool);
	
	//private methods
	MemPage_t* PageCreate();

	MemPage_t* GetPageOfPos(int _pos ,int* _posCounter);
    MemPage_t* getNextPage(MemPage_t* _memPage);
	
public: 
	
	MemPool_t(); 
	MemPool_t(int _defaultPageSize);  	
		
	virtual ~MemPool_t();	
	
	int getPagesCapacity() const {return m_pagesCapacity;}
	void setPagesCapacity(int _newPagesCapacity) { m_pagesCapacity = _newPagesCapacity; }

	/*writes _len bytes from _dataToWrite to cur position of pool , cur position advances by _len, and inc size of pool if nessesery*/  
	virtual bool write(const void* _dataToWrite, int _len) ; 
	virtual bool write(const void* _dataToWrite, int _len, int _pos) ; 
	
	/*will read _len bytes from _pos 
	  the data will be returned on the heap and USER IS RESPONSIBLE FOR DEALOCATING IT!!!!!!!!!
	  necessery for reading from 2 differant blocks 	*/
	virtual void* read(int _len, int _pos) ; 
	virtual void* read(int _len) ; 

};


	
#endif /*__MEM_POOL_H__*/


