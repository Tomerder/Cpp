#include <iostream>
#include <string.h>

using namespace std;

void test1();  //ctor , copy ctor , cast operator 
void test2();  //polimorfizem - base & derived - non/const objects & non/const methods 
void test3();  //pointer crash - virtual method vs non virtual method 

/*------------------------------------------------------------------------------------*/
int main() 
{
	cout << "/*---------------------ctor , copy ctor , cast operator----------------------*/" << endl;
	test1();
	
	cout << "/*-------POLIMORPHISEM - B & D - non/const objects & non/const methods-------*/" << endl;
	cout << "/*-func(const B& (D)) -> const foo of D ->  const foo of B-------------------*/" << endl;
    cout << "/*-func(B& (D)) -> foo of D ->  foo of B -> const foo of D -> const foo of D-*/" << endl;
	cout << "/*---------------------------------------------------------------------------*/" << endl;
	test2();
	
	cout << "/*-----------POINTER CRUSH - virtual method vs non virtual method------------*/" << endl;
	test3();
	cout << "/*---------------------------------------------------------------------------*/" << endl;
	
	return 0;
}

/*------------------------------------------------------------------------------------*/
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

/*------------------------------------------------------------------------------------*/

class B{
public:
	virtual void foo() const {cout << "const foo of B" << endl;}
	virtual void foo() {cout << "foo of B" << endl;}

};

class D : public B{
public:
	virtual void foo() const {cout << "const foo of D" << endl;}
	//virtual void foo()  {cout << "foo of D" << endl;}
};

/* func(const B& (D)) -> const foo of D ->  const foo of B */
/* func(B& (D)) -> foo of D ->  foo of B -> const foo of D -> const foo of D */

void func1(const B& _b){
	_b.foo();
}

void func2(B& _b){
	_b.foo();
}

void func1P(const B* _b){
	_b->foo();
}

void func2P(B* _b){
	_b->foo();
}

void test2()
{
	D d;
	B* bpD =new D;
	
	/*const object can only execute const methods : no const foo in D -> executes foo of B*/
	cout << "func1(const B& d);" << endl;
	func1(d);    
	func1P(bpD);

	/*there is foo in D -> execute foo of D*/
	cout << "func2(B& d);" << endl;
	func2(d);
	func2P(bpD);
}

/*------------------------------------------------------------------------------------*/


class A{
private:
	int dataMember;
public:
	void foo() {
		cout << "foo started" << endl;
		dataMember = 5;	/*falls here*/
	}

	virtual void foo2() {cout << "virtual foo" << endl;} /*wont be called*/

};



void test3()
{
	A* ap = NULL;
	
	/*foo is CALLED and falls when dataMember is accessed (object does not exist) */
	/*address of function is known and will be called even if object does not exist*/
	cout << "ap->foo(); -  not virtual" << endl;
	ap->foo();  

	/*virtual foo2 is NOT CALLED because address of func is not known (object does not exist - VT dm cant be accessed) */
	cout << "ap->foo2(); -  virtual" << endl;
	ap->foo2();
}

/*------------------------------------------------------------------------------------*/









