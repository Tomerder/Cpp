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

class MemPool_t : public Memory_t {

private: 
	list<MemPage_t*> m_pages;
	
	//int m_pagesCapacity;   // managed by static default size at page class 

	//will never be use
	MemPool_t(const MemPool_t& _pool);	
	MemPool_t& operator=(const MemPool_t& _pool);
	
	/*----------------------private methods----------------*/
	/*creates new page add it to list and returns it*/	
	MemPage_t* PageCreate();
	/*return page and pos in age acording to pool pos*/
	MemPage_t* GetPageOfPos(int _pos ,int* _posCounter);   
	 /*returns next on list*/ 
	MemPage_t* getNextPage(MemPage_t* _memPage);	
	/*returns next page to write to - if next page is STUB - creates new page add it to list and return it*/	
	MemPage_t* getNextPageToWriteTo(MemPage_t* _memPage);
	/*recursively write to next page - creates new pages when out of space */ 
	void writeRec(const void* _dataToWrite, int _lenLeftToWrite ,  int _lenWriten , MemPage_t* _pageToWrtTo );
	/*recursively read from next pages*/ 
	void readRec(void* _dataToRead, int _lenLeftToRead ,  int _lenWasRead , MemPage_t* _pageToReadFrom );
public: 
	
	MemPool_t(); 
	
	virtual ~MemPool_t();	
	
	/*writes _len bytes from _dataToWrite to cur position of pool , cur position advances by _len, and inc size of pool if nessesery*/  
	virtual bool write(const void* _dataToWrite, int _len) ; 
	virtual bool write(const void* _dataToWrite, int _len, int _pos) ; 
	
	/*will read _len bytes from _pos into _buffer ,advances to the point after the part that has been read*/
	virtual bool read(void* _buffer, int _len ) ; 
	virtual bool read(void* _buffer, int _len, int _pos) ;  

	void setDefaultPageCapcity(int _newDefaultCapacity) const { MemPage_t::setDefaultPageCapcity(_newDefaultCapacity); }
	int getDefaultPageCapcity() const { return MemPage_t::getDefaultPageCapcity(); }

	/*disabled - pages will be created on default size only(static DM of page)*/
	//MemPool_t(int _defaultPageSize);  	
	//int getPagesCapacity() const {return m_pagesCapacity;}
	//void setPagesCapacity(int _newPagesCapacity) { m_pagesCapacity = _newPagesCapacity; }	
};


	
#endif /*__MEM_POOL_H__*/


