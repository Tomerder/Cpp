// testPriorityQueue.cpp
//
//
//    Author: Vladimir Krapp
//    Created on: 2014-04-08
//    Last modified:

#include <iostream>

#include "runnable.h"
#include "thread.h"
#include "queuewithlocks.h"

#ifdef WINDOWS 
#include <Windows.h>
#define Sleep(T) Sleep(T * 1000) // Sleep(T) instructs thread to sleep for T seconds
#else
#include <unistd.h>
#define Sleep(T) sleep(T) // Sleep(T) instructs thread to sleep for T seconds
#endif

using namespace std;
using namespace m10;
using namespace m10::run;



const int N = 10;

class Producer: public Runnable
{
public:
	Producer(PriorityQueue<int>* _pq):m_pq(_pq){}

	virtual void operator()()
	{
		for(int i = 0; i <= N; ++i)
		{
			m_pq->Push(i);
			Sleep(1);
		}
	}

private:
	PriorityQueue<int>* m_pq;
};

class Consumer : public Runnable
{
public:

	Consumer(PriorityQueue<int>* _pq):m_pq(_pq){}

	virtual void operator()()
	{
		int i = 0;
		while (i < N)
		{
			i = m_pq->Pop();
			cout << "Got: " << i << '\n';
		}
	}

private:
	PriorityQueue<int>* m_pq;
};

int main()
{
    PriorityQueue<int> q;
    cout << "Is queue empty?" << q.Empty() << '\n';

    q.Push(1);
    cout << "Is queue empty?" << q.Empty() << '\n';

    int i = q.Pop();
    cout << "Poped: " << i << '\n';

    Producer producer(&q);
    Consumer consumer(&q);

    Thread prodThread(&producer);
    Thread consThread(&consumer);

    prodThread.Join();
    consThread.Join();

    return 0;
}
