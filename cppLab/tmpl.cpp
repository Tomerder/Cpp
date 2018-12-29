#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;

/*-----------------------------------------------------------*/

template <class T>
class B{

private:
	T m_b;

public:
	B() : m_b(0) { cout << "B def Ctor" << endl ;  }
	B(T _i) : m_b(_i) { cout << "B Ctor from int" << endl ;  }
	B(const B& _b) : m_b(_b.m_b) { cout << "B copy Ctor" << endl ;  }
	virtual ~B() { cout << "B Dtor" << endl ;  }

	int GetBdm() const { return m_b; }

	static void StatMemFunc() { cout << "StatMemFunc address : " << unsigned(StatMemFunc) << endl;  }
};

/*-----------------------------------------------------------*/

int main()
{
	B<int> b1;
	B<float> b2;
		
	cout << "call : b1.StatMemFunc();" << endl;
	b1.StatMemFunc();

	cout << "call : b2.StatMemFunc();" << endl;
	b2.StatMemFunc();

	cout << "----------------------------------" << endl;
	cout << "static func code is placed twice - once for int , once for float" << endl;
	cout << "----------------------------------" << endl;

	return 0;
}

/*-----------------------------------------------------------*/
