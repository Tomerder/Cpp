#include <iostream>
#include "observer.h"
using namespace std;

struct Y	//observer
{
	void Foo(int _num) {cout << "Foo. The number: " << _num << endl; }
};

class X	//subject
{
public:
	X();
	~X();

	void Register	(CallBackBase<int, X>* _cb);
	void Unregister	(CallBackBase<int, X>* _cb);

	void Notify(int _num) { m_sbj->Notify(_num); }

private:	
	Subject<int, X>* m_sbj;
};

X::X():m_sbj(new Subject<int, X>){}
X::~X(){delete m_sbj;}

void X::Register (CallBackBase<int, X>* _cb) 
{m_sbj->Register(_cb);}

void X::Unregister (CallBackBase<int, X>* _cb) 
{m_sbj->Unregister(_cb);}


class Xi : public Subject<int, Xi>{};	// using inheritance


int main ()
{
	X x;
	Y y, y1;

	CallBack<int, X, Y, void, &Y::Foo> callback1(&y, &x);
	CallBack<int, X, Y, void, &Y::Foo> callback2(&y1, &x);

	x.Notify(5);

	// with inheritance
	Xi xi;
	Y y2;
	CallBack<int, Xi, Y, void, &Y::Foo> callback3(&y2, &xi);
	xi.Notify(6);

	return 0;
}






