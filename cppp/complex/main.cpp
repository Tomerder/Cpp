#include <iostream>


#include "complex1.h"

using namespace std;
using namespace ComplexNamespace;

#define PRINT_LINE cout << "-----------------------------------------" << endl;

#define PRINT_TST(IS_PASS)   if(IS_PASS) { cout << "PASS" << endl; } else { cout << "FAIL" << endl;  }

/*-------------------------------------------------------*/

void PrintTest();

void UniTest();

/*-------------------------------------------------------*/

int main() 
{
	PRINT_LINE;

	PrintTest();
	PRINT_LINE;	
	UniTest();	
	
	PRINT_LINE;
	
	return 0;
}

/*-------------------------------------------------------*/

void ChkPlusEq()
{
	bool isPass = false;

	Complex c1(1,2);
	Complex c2(3,4);
	Complex c3(4,6);
	
	if( (c1 + c2) == c3 ){
		isPass = true;
	}
	
	PRINT_TST(isPass);
}


void ChkPlusSimetric()
{
	bool isPass = false;

	Complex c1(1,2);
	Complex c2(8,2);
	
	if( (7 + c1) == c2 ){
		isPass = true;
	}
	
	PRINT_TST(isPass);
}

void ChkPlusPlus()
{
	bool isPass = false;

	Complex c1(1,2);
	Complex c2(2,2);
	
	if( (++c1) == c2 ){
		isPass = true;
	}
	
	PRINT_TST(isPass);
}

void ChkSmall()
{
	bool isPass = false;
	Complex c1(1,2);
	Complex c2(2,2);
	
	if( c1 < c2 ){
		isPass = true;
	}
	
	PRINT_TST(isPass);
}


void UniTest()
{
	ChkPlusEq();
	ChkPlusSimetric();
	ChkPlusPlus();
	ChkSmall();
}

/*-------------------------------------------------------*/

void PrintTest()
{
	Complex comp1;
	
	Complex comp2(5);
	cout << "Complex comp2(5);  => " << comp2 << endl;
	
	Complex comp3(5,7);
	cout << "Complex comp3(5,7);  => " << comp3 << endl;
	
	Complex comp4(comp3);
	cout << "Complex comp4(comp3);  => " << comp4 << endl;
	
	comp1 = comp3;
	cout << "comp1 = comp3;  => " << comp1 << endl;
	
	comp1 = 77;
	cout << "comp1 = 77;  => " << comp1 << endl;
	
	double abs = comp3.Abs();
	cout << "abs = comp3.Abs();  => " << abs << endl;
	
	cout << "comp3 + comp4;  => " << (comp3 + comp4) << endl;
	
	cout << "77 + comp4;  => " << (77 + comp4) << endl;
	
	comp3 += comp4;
	cout << "comp3 += comp4;  => " << comp3 << endl;
	
	comp3 += 55;
	cout << "comp3 += 55;  => " << comp3 << endl;
	
	cout << "comp3++  => " << comp3++ << endl;
	cout << "comp3  => " << comp3 << endl;
	
	cout << "++comp3  => " << ++comp3 << endl;
	cout << "comp3  => " << comp3 << endl;
	
	
	cout << "(comp1 == comp3) : " << (comp1 == comp3) << endl;
	comp1 = comp3;
	cout << "comp1 = comp3;  =>  (comp1 == comp3) : " << (comp1 == comp3) << endl;
		
}

/*-------------------------------------------------------*/	
	
