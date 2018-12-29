#include <iostream>
#include <string.h>

#include "pool.h"

using namespace std;

#define SIZE_OF_ARR 10
#define MAX_NAME_LEN 50


/*------------------------------------------------------------------------------------*/

int main() 
{
	int i;
	MemPool_t pool(10);	 //10 bytes per page
	int intToWrite[SIZE_OF_ARR] ;
	int* intToRead;

	for(i=0; i< SIZE_OF_ARR; i++){
		intToWrite[i] = i;
	}

	for(i=0; i< SIZE_OF_ARR; i++){
		pool.write( &intToWrite[i] , sizeof(int));	
		intToRead = (int*) (pool.read(sizeof(int) , sizeof(int)*i ));	
		cout << endl << "num is : " << *intToRead << endl << endl;
		delete[] intToRead;   //should be deallocated by user
	}

	return 0;
}

/*------------------------------------------------------------------------------------*/

