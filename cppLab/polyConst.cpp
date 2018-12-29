#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;

/*-----------------------------------------------------------*/
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

/*-----------------------------------------------------------*/

int main()
{
	cout << "/*-------POLIMORPHISEM - B & D - non/const objects & non/const methods-------*/" << endl;
	cout << "/*-func(const B& (D)) -> const foo of D ->  const foo of B-------------------*/" << endl;
    cout << "/*-func(B& (D)) -> foo of D ->  foo of B -> const foo of D -> const foo of D-*/" << endl;
	cout << "/*---------------------------------------------------------------------------*/" << endl;
	test2();
	
	return 0;
}

/*-----------------------------------------------------------*/
