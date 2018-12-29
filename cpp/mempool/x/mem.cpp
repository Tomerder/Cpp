#include <string.h>
#include <iostream>

#include "mem.h"

using namespace std;

/*--------------------------------------------------------------------------------*/

Memory_t::~Memory_t(){}

bool Memory_t::write(const void* _dataToWrite, int _len){return true;}
bool Memory_t::write(const void* _dataToWrite, int _len, int _pos){return true;}
void* Memory_t::read(int _len) {return 0;} 
void* Memory_t::read(int _len, int _pos) {return 0;} 


bool Memory_t::setCurPos(int _pos)
{
	if(_pos > m_numOfBytesWriten ) { 
		return false;
	}
	
	 m_curPos = _pos;
	 
	 return true;
}
/*--------------------------------------------------------------------------------*/	




















	
	

