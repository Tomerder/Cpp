#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <pthread.h>


#include "singleton.h"

#define RETURN_IF_ERROR1(RET,MSG)\
		if (RET != 0) { perror("Error "); printf(MSG); printf("\n");\
		return 0;}

static const int NUM_THREADS = 10;
using namespace std;
using namespace m10;

class X{
friend class Singleton<X>;
public:
	void PrintStar(){cout << "*" << endl;}

private:
	X(){};
};

void* Foo(void* _params)
{
	X* x = Singleton<X>::Instance();
	x->PrintStar();

	cout << "object's address: " << x << endl;
	return 0;
}

int main()
{
	int status;
	pthread_t threads[NUM_THREADS];
	
	for (int i = 0; i < NUM_THREADS; ++i)
	{
		status = pthread_create(&threads[i], 0, Foo, 0);
		RETURN_IF_ERROR1(status, "pthread_create threads");
	}

	for (int i = 0; i < NUM_THREADS; ++i)
	{
		status = pthread_join(threads[i], 0);
		RETURN_IF_ERROR1(status, "pthread_join threads");
	}

	return 0;
}
