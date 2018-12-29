#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;

/*-----------------------------------------------------------*/

class B{

private:
	int m_b;

public:
	B() : m_b(0) { cout << "B def Ctor" << endl ;  }
	B(int _i) : m_b(_i) { cout << "B Ctor from int" << endl ;  }
	B(const B& _b) : m_b(_b.m_b) { cout << "B copy Ctor" << endl ;  }
	virtual ~B() { cout << "B Dtor" << endl ;  }

	int GetBdm() const { return m_b; }
};


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

int main()
{
	
	return 0;
}

/*-----------------------------------------------------------*/
