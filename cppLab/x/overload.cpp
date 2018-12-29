#include <stdio.h>
#include <stdlib.h>

/*-----------------------------------------------------------*/

class A{

private:
	int i;
	
public:
	A() { i = 0; }

	/* A(A _a) { i = _a.i; }  => error */
	A(A* _a) { i = _a->i; }    /*ctor*/
	
	void Foo(int* i) {};
	void Foo(int& i) {};
	void Foo(int i) {};
	
	void Foo(int* i) const{};
	void Foo(int& i) const{};
	void Foo(int i) const{};
	
	void Foo(const int* i) {};
	void Foo(const int& i) {};
	
	void Foo(const int* i) const{};
	void Foo(const int& i) const{};

};


int main()
{
	A a1;
		

	return 0;
}

/*-----------------------------------------------------------*/
