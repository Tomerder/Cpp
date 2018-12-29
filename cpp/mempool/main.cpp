#include <iostream>
#include <string.h>

#include "pool.h"

using namespace std;

#define SIZE_OF_ARR 10
#define MAX_NAME_LEN 50


void checkPage10bytesInsert10Ints();
void checkPage2BytesInsertDouble();
/*------------------------------------------------------------------------------------*/

int main() 
{
	cout << "/*---------------------------------------------------------*/" << endl;	

	checkPage10bytesInsert10Ints();
	
	cout << "/*---------------------------------------------------------*/" << endl;	

	checkPage2BytesInsertDouble();
	
	cout << "/*---------------------------------------------------------*/" << endl;	

	return 0;
}

/*------------------------------------------------------------------------------------*/

void checkPage10bytesInsert10Ints()
{
	int i;
	//MemPool_t pool(10);	 //10 bytes per page
	MemPool_t pool;
	int intToWrite[SIZE_OF_ARR] ;
	int intToRead;

	cout << "page size is : 10 , check with 10 ints" << endl;	

	for(i=0; i< SIZE_OF_ARR; i++){
		intToWrite[i] = i;
	}

	for(i=0; i< SIZE_OF_ARR; i++){
		pool.write( &intToWrite[i] , sizeof(int));	
		pool.read(&intToRead ,sizeof(int) , sizeof(int)*i );	
		cout << "num is : " << intToRead << endl;
	}

}

/*------------------------------------------------------------------------------------*/

void checkPage2BytesInsertDouble()
{
	MemPage_t::setDefaultPageCapcity(2); 	
	MemPool_t pool;	
	double dToWrite = 777.555 ;
	double dToRead;

	pool.write( &dToWrite , sizeof(double));	
	pool.read(&dToRead ,sizeof(double) , 0);
	cout << "page size is : 2 , check with double" << endl;	
	cout << "num is : " << dToRead << endl;

}

/*------------------------------------------------------------------------------------*/

