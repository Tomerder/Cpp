#include <iostream>
#include <string.h>

#include "big.h"

using namespace std;

#define SIZE 1000

void setBigNum(BigNum& _bigNum);
void sumBigNums(BigNum& _bigNum1, BigNum& _bigNum2);
void areEqual(const BigNum& _bigNum1, const BigNum& _bigNum2);
void isSmaller(const BigNum& _bigNum1, const BigNum& _bigNum2);

int main() 
{
	
	int cont = 1;
	int ch = 0;
	
	BigNum bigNum1("1234578901234567890");
	BigNum bigNum2(12345);
	
	
	while(cont) {
		cout << endl;
		cout << "1 - set bigNum 1" 	<< endl;
		cout << "2 - set bigNum 2" 	<< endl;
		cout << "3 - sum numbers" 	<< endl;
		cout << "4 - compere numbers (are equal)" 	<< endl;
		cout << "5 - is first smaller" 	<< endl;
		cout << "6 - print first number" << endl;
		cout << "7 - print second number" << endl;		
		cout << "Please, choose option: ";
	
		cin >> ch;
		
		switch(ch) {
			case 1 : setBigNum(bigNum1); break;			
			case 2 : setBigNum(bigNum2); break;			
			case 3 : sumBigNums(bigNum1, bigNum2); break;
			case 4 : areEqual(bigNum1, bigNum2); break;
			case 5 : isSmaller(bigNum1, bigNum2); break;
			case 6 : bigNum1.Print(); break;
			case 7 : bigNum2.Print(); break;
					
			default: cont = 0;
		}
	}

}


void setBigNum(BigNum& _bigNum)
{
	char numToSet[SIZE];	
	cout << endl << "enter a number to set :" ;
	cin>> numToSet;

	_bigNum = numToSet;

}

void sumBigNums(BigNum& _bigNum1, BigNum& _bigNum2)
{
	BigNum bigNum3 = _bigNum1 + _bigNum2;	
	
	bigNum3.Print();	
	cout << endl;	
}


void areEqual(const BigNum& _bigNum1,const BigNum& _bigNum2)
{
	if(_bigNum1 == _bigNum2){
		cout << "TRUE" << endl;
	}else{
		cout << "FALSE" << endl;
	}
}

void isSmaller(const BigNum& _bigNum1, const BigNum& _bigNum2)
{
	if(_bigNum1 < _bigNum2){
		cout << "TRUE" << endl;
	}else{
		cout << "FALSE" << endl;
	}
}

