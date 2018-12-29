#include <iostream>
#include <string.h>

#include "string1.h"

using namespace std;

#define SIZE 100

const char* resultArr[2] = {"FALSE","TRUE"};


void setString (String_t& _string);	
void compere (String_t& _string);	
void setCaseSensitive (String_t& _string);
void getCaseSensitive (String_t& _string);
void setLowerCase (String_t& _string);
void setUpperCase (String_t& _string);	
void prependChar (String_t& _string);
void prependString (String_t& _string);
void isContains (String_t& _string);
void printStr(String_t& _string);




int main() {

	int cont=1;
	int ch  =0;
	String_t string1("TEMP STRING");
	
	while(cont) {
		cout << endl;
		cout << "1 - set string  " 	<< endl;
		cout << "2 - compere " 	<< endl;
		cout << "3 - set Case Sensitive" 	<< endl;
		cout << "4 - get Case Sensitive" 	<< endl;
		cout << "5 - set Lower Case" << endl;
		cout << "6 - set Upper Case" << endl;
		cout << "7 - prepend from String" << endl;
		cout << "8 - is contains" << endl;
		cout << "9 - print String" << endl;
		
		cout << "Please, choose option: ";
	
		cin >> ch;
		
		switch(ch) {
			case 1 : setString(string1); break;			
			case 2 : compere(string1); break;			
			case 3 : setCaseSensitive(string1); break;
			case 4 : getCaseSensitive(string1); break;
			case 5 : setLowerCase(string1); break;
			case 6 : setUpperCase(string1); break;
			case 7 : prependString(string1); break;
			//case 8 : isContains(string1); break;
			case 9 : printStr(string1); break;
			
			default: cont = 0;
		}
	}

}



void printStr(String_t& _string)
{
	cout << endl << "string = " << _string.getName()  << endl;
}




void setString (String_t& _string)
{

	char str[SIZE];
	
	cout << endl << "enter string to set : " ;
	cin	>> str; 
	
	_string.setName(str);
	
}




void compere (String_t& _string){
	char str[SIZE];
	int resultInd;
	
	cout << endl << "enter string to compere: " ;
	cin	>> str; 
	
	resultInd = (_string == str);
	
	cout << endl << resultArr[resultInd] << endl;

}



void setCaseSensitive (String_t& _string){
	int setCase;
	
	cout << endl << "set Case Sensitive to (0/1) : " ;
	cin	>> setCase;
	
	_string.setCaseSens(setCase);
}


void getCaseSensitive (String_t& _string){
	int resultInd = String_t::getCaseSens();
	
	cout << endl << "Case Sensitive : " << resultArr[resultInd] << endl;
}




void setLowerCase (String_t& _string)
{
	_string.setLowerCase();
}


void setUpperCase (String_t& _string)
{
	_string.setUpperCase();
}


void prependString (String_t& _string){
	char str[SIZE];
	
	cout << endl << "enter string to pre append : " ;
	cin	>> str; 
	
	_string.prepend(str);	

}

	


