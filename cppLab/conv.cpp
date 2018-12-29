#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;

/*-----------------------------------------------------------*/

class A1{

};

class A2{
public:
	A2()  { cout << "def Ctor of A2" << endl ;  }	
	A2(const A1& _a1)  { cout << "A2 Ctor from A1" << endl ;  }	
};

/*-----------------------------------------------------------*/

class B{

private:
	int m_b;

public:
	B() : m_b(0) { cout << "B def Ctor" << endl ;  }	
	B(int _i) : m_b(_i) { cout << "B Ctor from int" << endl ;  }
	B(string _str)  { cout << "B Ctor from string" << endl ;  }
	B(const A2& _a2)  { cout << "B Ctor from A2" << endl ;  }	
	
	B(const B& _b) : m_b(_b.m_b) { cout << "B copy Ctor" << endl ;  }
	virtual ~B() { cout << "B Dtor" << endl ;  }

	int GetBdm() const { return m_b; }
};

/*-----------------------------------------------------------*/

class D : public B{

private:
	int m_d;

public:
	D() : m_d(0) { cout << "D def Ctor" << endl ;  }
	D(int _i) : m_d(_i) { cout << "D Ctor from int" << endl ;  }
	D(const D& _d) : m_d(_d.m_d) { cout << "D copy Ctor" << endl ;  }
	virtual ~D() { cout << "D Dtor" << endl ;  }

	int GetDdm() const { return m_d; }
};

/*-----------------------------------------------------------*/

class X{

private:
	int m_x;

public:
	X(const B& _b) : m_x( _b.GetBdm() ) { cout << "X Ctor from B" << endl ;  }

};

/*-----------------------------------------------------------*/

void FooNoConst(X& _x)   
{
	cout << "in Foo" << endl;
}

void Foo(const X& _x)   
{
	cout << "in Foo" << endl;
}

/*-----------------------------------------------------------*/

int main()
{
	B b(5);
	D d(7);

	cout << "---------------------------------" << endl;
	cout << "calling Foo(b);" << endl;
	Foo(b);
	//FooNoConst(b);   compile error - tmp object is const  

	cout << "---------------------------------" << endl;	
	cout << "calling Foo(d);" << endl;
	Foo(d);  
	//FooNoConst(d);   compile error - tmp object is const  
	
	cout << "---------------------------------" << endl;	
	cout << "calling Foo(X(d));  <=> exactly the same as last call" << endl;
	Foo(X(d));   /*** exactly same as before - temp object is created by ctor from B part of D ***/  
	
	//cout << "---------------------------------" << endl;
	//cout << "calling Foo(55);" << endl;
	//Foo(55);     						/*** double conv doesnt work : int => B => X ***/
	
	cout << "---------------------------------" << endl;
	cout << "X x(77);" << endl;
	X x1(77);
	
	cout << "---------------------------------" << endl;
	string str = "abc";
	cout << "X x(str);" << endl;
	X x2(str);
	
	cout << "---------------------------------" << endl;
	A2 a2;
	cout << "X x(a2);" << endl;
	X x3(a2);
	
	cout << "---------------------------------" << endl;
	//A1 a1;
	//cout << "X x(a1);" << endl;
	//X x4(a1);
	
	cout << "---------------------------------" << endl;
	cout << "FooNoConst(x);" << endl;
	FooNoConst(x1); 
	
	cout << "---------------------------------" << endl;
	cout << "Foo(x);" << endl;
	Foo(x1); 
	
	return 0;
}

/*-----------------------------------------------------------*/
