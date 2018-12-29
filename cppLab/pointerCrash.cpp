#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;

/*-----------------------------------------------------------*/

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

/*-----------------------------------------------------------*/

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

/*-----------------------------------------------------------*/

int main()
{
	cout << "/*-----------POINTER CRUSH - virtual method vs non virtual method------------*/" << endl;
	test3();
	cout << "/*---------------------------------------------------------------------------*/" << endl;
	
	return 0;
}

/*-----------------------------------------------------------*/
