#include <cstdio>
#include <cstdlib>
#include <iostream>


using namespace std;

#define IS_REF FALSE

/*-----------------------------------------------------------*/

class B{

private:
	int m_bDm;

public:
	B() : m_bDm(0) { cout << "B def Ctor" << endl ;  }
	B(int _bDm) : m_bDm(_bDm) { cout << "B Ctor from int" << endl ;  }
	B(const B& _b) : m_bDm(_b.m_bDm) { cout << "B copy Ctor" << endl ;  }
	virtual ~B() { cout << "B Dtot" << endl ;  }
};


class D : public B{

private:
	int m_dDm;

public:
	D() : m_dDm(0) { cout << "D def Ctor" << endl ;  }
	D(int _dDm) : m_dDm(_dDm) { cout << "D Ctor from int" << endl ;  }
	D(const D& _d) : m_dDm(_d.m_dDm) { cout << "D copy Ctor" << endl ;  }
	virtual ~D() { cout << "D Dtor" << endl ;  }
};

/*-----------------------------------------------------------*/

void Foo(const B* _bp)
{
	cout << "Foo(const B* _bp)" << endl;
}

#if IS_REF
void Foo(const B& _b)
{
	cout << "Foo(const B& _b)" << endl;
}
#else
void Foo(B _b)
{
	cout << "Foo(B _b)" << endl;
}
#endif

int main()
{
	B b1;
	B b2(b1);
	B b3(5);
	
	Foo(b3);		
	Foo(7);		

	return 0;
}

/*-----------------------------------------------------------*/
