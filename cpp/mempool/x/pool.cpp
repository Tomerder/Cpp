#include <string.h>
#include <iostream>

#include "pool.h"

using namespace std;


/*--------------------------------------------------------------------------------*/

//private and will not be used!!!!!!!!!!!!!
MemPool_t& MemPool_t::operator=(const MemPool_t& _mem)   //operator= 
{return *this;}

//private and will not be used!!!!!!!!!!!!!
MemPool_t::MemPool_t(const MemPool_t& _mem)
{}

/*--------------------------------------------------------------------------------*/

MemPool_t::MemPool_t()    //ctor
{
	m_pagesCapacity = DEFAULT_INITIAL_PAGE_CAPACITY;	
	PageCreate();
}


MemPool_t::MemPool_t(int _pagesCapacity)    //ctor
{
	m_pagesCapacity = _pagesCapacity;	 
	PageCreate();
}


MemPage_t* MemPool_t::PageCreate()  //create first page in list
{
	MemPage_t* page = new MemPage_t(m_pagesCapacity);
	
	m_pages.push_back(page);

	return page;
}

/*--------------------------------------------------------------------------------*/

MemPool_t::~MemPool_t()    //dtor
{   		  	
	while (!m_pages.empty())
    {
		delete m_pages.front();
		m_pages.pop_front();
    } 
}

/*--------------------------------------------------------------------------------*/

MemPage_t* MemPool_t::GetPageOfPos(int _pos ,int* _posCounter)
{
	MemPage_t* memPage =0;
	bool wasPageFound = false;
	int pageCapacity;

	list<MemPage_t*>::iterator it;
	for(it = m_pages.begin(); it != m_pages.end() ; it++){ //go through list of pages
		memPage = *it;
		pageCapacity =  memPage->getCapacity();
		if(*_posCounter + pageCapacity <= _pos){ //advance to next page in pool 
			*_posCounter += pageCapacity;
		}else{
			wasPageFound = true;
			break;
		}
	}	
	
	if(!wasPageFound){
		memPage = 0;
	}

	return memPage;
}

/*--------------------------------------------------------------------------------*/	


bool MemPool_t::write(const void* _dataToWrite, int _len) 
{
	int posCounter = 0;		
	int pagePosToWrite;
	int pageCapacity;
	int curPos = getCurPos();	
	MemPage_t* memPage=0;
	
	memPage = GetPageOfPos(curPos, &posCounter);   // posCounter= position of page start
		
	if(!memPage){   //need to create new page 
		memPage = PageCreate();
	}
		
	pageCapacity = memPage->getCapacity();
	pagePosToWrite  =  curPos - posCounter;  //will be 0 if new page was created                          

	if(pagePosToWrite + _len > pageCapacity ){  //check if there is enough space on this page
		//write on this page and on the next
		int bytesToWrtCurPage = pageCapacity - pagePosToWrite;
		int bytesToWrtNxtPage = _len - bytesToWrtCurPage;
		memPage->write(_dataToWrite, bytesToWrtCurPage, pagePosToWrite);  //write on cur page
		memPage = PageCreate(); //create next page
		memPage->write(_dataToWrite + bytesToWrtCurPage , bytesToWrtNxtPage, 0);  //write on next page	   
	}else{  //enough space on this page
		memPage->write(_dataToWrite, _len, pagePosToWrite);
	} 

	int curSize = getCurSize();
	if ( curSize < curPos + _len){	
		setCurSize( curPos + _len );  // set new size
	}	

	setCurPos(curPos + _len );  // set new pos
	
	return true;
}



bool MemPool_t::write(const void* _dataToWrite, int _len, int _pos) 
{
	/*TODO*/
	
	return true;
}


/*--------------------------------------------------------------------------------*/	


void* MemPool_t::read(int _len) 
{
	/*TODO*/
	return 0; 

}



void* MemPool_t::read(int _len, int _pos) 
{
	int posCounter = 0;	
	int pageCapacity;	
	int pagePosToRead;
	MemPage_t* memPage =0;
	void* dataToRead =0;	
	
	//check if read from legal position 
	if( _pos + _len > getCurSize() ){
		return 0;
	}

	dataToRead = new char[_len]; //will be deallocated by user !!!

	memPage = GetPageOfPos(_pos, &posCounter);   // posCounter= position of page start
	
	if(memPage){	
		pageCapacity = memPage->getCapacity();
		pagePosToRead  =  _pos - posCounter;                           
		
		if(pagePosToRead + _len > pageCapacity ){  //check to see if there is enough space on this page	
			//read from this page and from the next
			int bytesToReadCurPage = pageCapacity - pagePosToRead;
			int bytesToReadNxtPage = _len - bytesToReadCurPage;
			//read from cur page	
			memcpy(dataToRead, memPage->read(bytesToReadCurPage, pagePosToRead), bytesToReadCurPage);     
			memPage = getNextPage(memPage);
			//read from next page	   
			memcpy(dataToRead + bytesToReadCurPage, memPage->read(bytesToReadNxtPage, 0), bytesToReadNxtPage);  
		}else{  //all data to read is on this page
		    memcpy(dataToRead, memPage->read(_len, pagePosToRead), _len);
		} 
	}
	

	return dataToRead;
	
} 



/*--------------------------------------------------------------------------------*/	


MemPage_t* MemPool_t::getNextPage(MemPage_t* _memPage){
	list<MemPage_t*>::iterator it = m_pages.begin();
	
	for(; *it !=_memPage ; it++);

	return *(++it); 
}


/*--------------------------------------------------------------------------------*/	









	
	

