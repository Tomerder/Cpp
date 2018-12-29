#include <iostream>
#include <string.h>

#include "student.h"

using namespace std;

typedef enum {FAIL,PASS} Result;
const char* resultArr[2] = {"FAIL","PASS"};

int main() 
{
	int res;
	int resultInd = PASS; 
	
	Student st1("name");
	Student st1B(st1);
	Student st2("name2");
	
	
	 //test operator==   &  copy CTOR
	res = (st1 == st1B);	
	if( res != true){
		resultInd = FAIL;
	}
	
	 //test operator==
	res = (st1 == st2);	  
	if( res == true){
		resultInd = FAIL;
	}
	
	 //test operator= 
	st1B = st2;  
	res = (st1B == st2);	
	if( res != true){
		resultInd = FAIL;
	}
	
	//test m_nStudents	
	if( st1B.getnStudents() != 3){
		resultInd = FAIL;
	}
	
	cout << "test :" << resultArr[resultInd] << endl ;
}






