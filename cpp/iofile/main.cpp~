#include <iostream>
#include <string.h>
#include <fstream>

#include "bin.h"
#include "asc.h"

using namespace std;

#define STR_TO_CHK "hello world"
#define STR_TO_CHK_LEN (strlen(STR_TO_CHK) + 1)

void interactiveMain();

void getLocFromUser(virtIO_t& file);

void writeInt(virtIO_t& file); 
void readInt(virtIO_t& file); 

void writePtr(virtIO_t& file); 
void readPtr(virtIO_t& file); 

void writeReadCombo(virtIO_t& file);

//void writeReadComboTry();
/*------------------------------------------------------------------------------------*/

int main() 
{
	
	interactiveMain();	

	return 0;
}

/*------------------------------------------------------------------------------------*/

void interactiveMain()
{
	char ch;
	virtIO_t* file = NULL;	
	
	cout << "/-----------------------------------------------------/" << endl;	
	cout << "Press 'b' to test binary file , any other key to test ascii file: ";
	cin >> ch;

	if(ch == 'b'){
		file = new binIO_t((char*)"test.txt",(char*)"w+"); 
	}else{
		file = new asciiIO_t((char*)"test.txt",(char*)"w+"); 	
	}
	

	int cont = 1;
	
	while(cont) {
		cout << endl;
		cout << "1 - set location to begining of file" 	<< endl;
		cout << "2 - set location relative to begining of file" 	<< endl;
		cout << "3 - get length" 	<< endl;
		cout << "4 - write int" 	<< endl;
		cout << "5 - read int" 	<< endl;
		cout << "6 - write string (void*)" 	<< endl;
		cout << "7 - read string (void*)" 	<< endl;
		cout << "8 - write combintation and read it" 	<< endl;
		cout << "9 - get status" 	<< endl;
		cout << "0 - clear status" 	<< endl;				
		cout << "Please, choose option: ";
	
		cin >> ch;
		
		switch(ch) {
			case '1' : file->setLocation(0,0); break;		
			case '2' : getLocFromUser(*file) ; break;	
			case '3' :cout << "length :" << file->getLength() << endl; break;			
			case '4' : writeInt(*file); break;
			case '5' : readInt(*file); break;
			case '6' : writePtr(*file); break;
			case '7' : readPtr(*file); break;
			case '8' : writeReadCombo(*file); break;
			case '9' : cout << "status :" << file->getStatus() << endl; break;
			case '0' : file->clearStatus() ; break;
					
			default: cont = 0;
		}
	}

	delete file;

	cout << "/-----------------------------------------------------/" << endl;

}

/*--------------------------------------------------------------------------*/

void writeInt(virtIO_t& file){
	int intToWrt = 777;	
	file << intToWrt;
}

void readInt(virtIO_t& file){
	int intToRead = 0;
	file >> intToRead;

	cout << "int is : " << intToRead << endl;
}

/*--------------------------------------------------------------------------*/

void writePtr(virtIO_t& file){
	char toWrt[STR_TO_CHK_LEN] = STR_TO_CHK;
	file << toWrt , STR_TO_CHK_LEN;
}

void readPtr(virtIO_t& file){
	char* toRead = new char[STR_TO_CHK_LEN];
	
	file >> toRead , STR_TO_CHK_LEN ;

	cout << "string is : " << toRead << endl;
	
	delete[] toRead;
}

/*--------------------------------------------------------------------------*/


void writeReadCombo(virtIO_t& file){
	int intToWrt = 555;	
	float flToWrt = 777.777;
	char charToWrt1 = 'T';
	char charToWrt2 = 'A';
	short sToWrt = 88;		
	int intToRead = 0;	
	float flToRead = 0;
	char charToRead1 = 0;
	char charToRead2 = 2;
	short sToRead = 0;		
	char toWrt[STR_TO_CHK_LEN] = STR_TO_CHK;	
	char* toRead = new char[STR_TO_CHK_LEN];
	
	file << intToWrt << charToWrt1 << flToWrt << charToWrt2 << sToWrt << toWrt , STR_TO_CHK_LEN ;

	file.setLocation(0,0);

	file >> intToRead >> charToRead1 >> flToRead >> charToRead2 >> sToRead >>toRead , STR_TO_CHK_LEN ;

	cout << "combo is : " << intToRead << charToWrt1 << flToRead << charToRead2 << sToRead << toRead  << endl;
	
	delete[] toRead;
}



/*--------------------------------------------------------------------------*/

void getLocFromUser(virtIO_t& file){
	int loc = 0;	
	cout << "enter location: ";
	cin >> loc;

	file.setLocation(loc,0);

}

/*--------------------------------------------------------------------------*/

/*
void writeReadComboTry(){

	int intToWrt = 555;	
	float flToWrt = 777.777;
	char charToWrt = 'T';
	double dbToWrt = 888.009;		
	int intToRead = 0;	
	float flToRead = 0;
	char charToRead = 0;
	double dbToRead = 0;		
	char toWrt[STR_TO_CHK_LEN] = STR_TO_CHK;	
	char* toRead = new char[STR_TO_CHK_LEN];

	fstream file("test.txt");
	
	file << intToWrt << flToWrt << charToWrt << dbToWrt << toWrt , STR_TO_CHK_LEN ;

	file.seekg (0, ios::beg);

	file >> intToRead >> flToRead >> charToRead >> dbToRead >>toRead , STR_TO_CHK_LEN ;

	cout << "combo is : " << intToRead  << flToRead << charToRead << dbToRead << toRead  << endl;
	
	file.close(); 

}
*/


