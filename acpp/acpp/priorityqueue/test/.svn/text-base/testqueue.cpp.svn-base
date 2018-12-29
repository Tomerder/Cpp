#include <iostream>
#include <unistd.h>

#include "priorityqueue.h"

using namespace std;

typedef enum {OK, ERROR} TEST;
TEST PqCreate();

int main()
{
 	const string pass = "Pass", fail = "fail";

	//Unit test.
	//case 1:
	cout << "\nWaitable priority queue Test:" << ((PqCreate()==OK)?pass:fail) << endl;




    return 0;
}

//---------------------------------------------------------------
//			Waitable priority queue Test
//---------------------------------------------------------------
struct PqAndCounter
{
	size_t m_count;
    WaitablePQueue<int> pq;
};

void* ThreadProducer(void* _param)
{
    PqAndCounter* st = (PqAndCounter*)_param;

   // (st->pq).Push(1);
    for (int i = 0; i < 10; ++i)
    {
        (st->pq).Push(1);
        cout << "Item pushed" << endl;
    }

	return 0;
}

void* ThreadConsumer(void* _param)
{
    PqAndCounter* st = (PqAndCounter*)_param;

    for (int i = 0; i < 10; ++i)
    {
        (st->pq).Pop();
        cout << "Item poped" << endl;
    }
	return 0;
}


TEST PqCreate()
{
	struct PqAndCounter st;
	st.m_count = 1;

	pthread_t t1, t2;

	pthread_create(&t1, 0, ThreadProducer, &st);

	pthread_create(&t2, 0, ThreadConsumer, &st);

	pthread_join(t1, 0);
	pthread_join(t2, 0);

	if (st.m_count != 1) return ERROR;

	return OK;
}


