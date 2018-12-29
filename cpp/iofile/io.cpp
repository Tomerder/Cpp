#include <string.h>
#include <iostream>

#include "io.h"

using namespace std;

/*--------------------------------------------------------------------------------*/

bool IO_ABS::isReadLegal() const
{
	int access = getAccess();
	
	if(!isGood()){
		return false;
	}		

	if(access != READ && access != READ_WRITE){
		return false;
	}

	return true;
}

bool IO_ABS::isWriteLegal() const
{
	int access = getAccess();

	if(!isGood()){
		return false;
	}		

	if(access != WRITE && access != READ_WRITE){
		return false;
	}

	return true;
}

/*--------------------------------------------------------------------------------*/











	
	

