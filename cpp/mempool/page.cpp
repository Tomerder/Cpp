#include <string.h>
#include <iostream>

#include "page.h"

using namespace std;

/*--------------------------------------------------------------------------------*/

int MemPage_t::m_defaultPageSize = DEFAULT_INITIAL_PAGE_CAPACITY;

/*--------------------------------------------------------------------------------*/

//private and will not be used!!!!!!!!!!!!!
MemPage_t& MemPage_t::operator=(const MemPage_t& _mem)   //operator= 
{return *this;}

//private and will not be used!!!!!!!!!!!!!
MemPage_t::MemPage_t(const MemPage_t& _mem)
{}
/*--------------------------------------------------------------------------------*/

MemPage_t::MemPage_t()       //ctor
{
	 m_startOfPage = new char[m_defaultPageSize];
	 
	 m_capacity = m_defaultPageSize;
}

MemPage_t::MemPage_t(int _capacity)    //ctor
{
	 m_startOfPage = new char[_capacity];
	 
	 m_capacity = _capacity;
}

MemPage_t::~MemPage_t()    //dtor
{   		  	
	delete[]((char*)m_startOfPage);
	m_startOfPage = NULL;   
}

/*--------------------------------------------------------------------------------*/	
	
	
bool MemPage_t::write(const void* _dataToWrite, int _len) 
{
	int curPos = getCurPos();	
	if ( curPos + _len > m_capacity){    
		return false;
	}
	
	writeImp(_dataToWrite, _len, curPos);
	return true;
}

bool MemPage_t::write(const void* _dataToWrite, int _len, int _pos) 
{
	if ( _pos + _len > m_capacity){
		return false;
	}
	
	writeImp(_dataToWrite, _len,_pos);
	return true;
}

void MemPage_t::writeImp(const void* _dataToWrite, int _len, int _pos) 
{
	char* dst = m_startOfPage + _pos;
	
	memcpy(dst, _dataToWrite, _len);

	if( _pos + _len > getCurSize() ){   
		setCurSize(_pos + _len); 
	}
	
	setCurPos(_pos + _len); 
	
}

/*--------------------------------------------------------------------------------*/	


bool MemPage_t::read(void* _buffer, int _len )
{
	int curPos = getCurPos();	
	if( curPos+ _len > m_capacity){  
		return 0;
	}

	memcpy(_buffer, m_startOfPage + curPos, _len);
	
	setCurPos(curPos + _len); 
	
	return  true;

}



bool MemPage_t::read(void* _buffer, int _len, int _pos)
{
	if(_pos + _len > m_capacity){
		return 0;
	}
	
	memcpy(_buffer, m_startOfPage + _pos, _len);

	setCurPos(_pos + _len); 
	
	return true; 
} 




/*--------------------------------------------------------------------------------*/	




















	
	

