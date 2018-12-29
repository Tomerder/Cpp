#include <iostream>

#include "runnable.h"
#include "thread.h"

using namespace std;

void Foo()
{
	int i;

	for ( i = 0; i < 1000000; ++i)
	{}
	cout << "Foo " << i << endl;
}


int main()
{
	shared_ptr<Runnable> run1 ( new FunctionRun<Foo> );

	Thread t(run1);

	t.Join();


	return 0;
}