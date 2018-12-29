#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;

/*-----------------------------------------------------------*/

class X;

class Y{
public:
	operator X&() const {cout << "Y cast operator to X" << endl; }
};


class X{
public:
	explicit X(const Y& _y)  { cout << "ctor of X from Y" << endl;}
	
	X(const X& _x)  { cout << "copy ctor of X" << endl;}
};



void test1()
{
	Y y;	
	
	/*if (Y has operator cast to X) && (X has CTOR from Y(non explicit)) -> compilation error : "conversion from ‘Y’ to ‘X’ is ambiguous"*/
	cout << "X x1=y; " << endl;
	X x1=y;	 
	
	/*(1)ctor of X from Y.  (2)Y cast operator to X->copy CTOR  (3)if both exist: 1 will be prefered */  							
	cout << "X x2(y); " << endl;
	X x2(y);

	/*the only way to force cast operator + copy CTOR , when CTOR from Y is exist*/
	cout << "X x3( y.operator X&() ); " << endl;
	X x3( y.operator X&() );

	//X x3;   /*not possible : if CTOR(Y) is provided then default CTOR wont be provided from compiler*/ 
	//X x4(); /*can be only : function call*/ 	

}

/*-----------------------------------------------------------*/

int main()
{
	cout << "/*---------------------ctor , copy ctor , cast operator----------------------*/" << endl;
	test1();

	return 0;
}

/*-----------------------------------------------------------*/
