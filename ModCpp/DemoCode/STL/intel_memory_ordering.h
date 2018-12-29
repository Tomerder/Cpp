#pragma once

// Adapted from "Memory Reordering Caught in the Act", http://preshing.com/20120515/memory-reordering-caught-in-the-act/

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <intrin.h>

#include <thread>
#include <iostream>
#include <random>
#include <atomic>

// * _ReadWriteBarrier() prevents compiler reorderings, but doesn't affect CPU reordering.
// * MemoryBarrier() is a full fence that enforces complete ordering.
// * std::atomic<int> is cheaper because it doesn't require a full fence.
// Uncomment one of these to introduce the necessary fences.

// #define WITH_FENCE
// #define WITH_ATOMIC


// Add Barrier between read and write : flag0 = 1; Barrier; r1 = flag1;
#ifdef WITH_FENCE
#define Barrier MemoryBarrier()
#else
#define Barrier _ReadWriteBarrier()
#endif

#ifdef WITH_ATOMIC
#define VAR_TYPE std::atomic<int>
#else
#define VAR_TYPE int
#endif

HANDLE beginEvent1;
HANDLE beginEvent2;
HANDLE endSemaphore;

VAR_TYPE flag0, flag1;
int r1, r2;

void thread1()
{
	std::mt19937 random(1);
	for (;;)
	{
		WaitForSingleObject(beginEvent1, INFINITE);
		while (random() % 8 != 0)
		{
		}

		flag0 = 1; 
		r1 = flag1;

		ReleaseSemaphore(endSemaphore, 1, NULL);
	}
};

void thread2()
{
	std::mt19937 random(2);
	for (;;)
	{
		WaitForSingleObject(beginEvent2, INFINITE);
		while (random() % 8 != 0)
		{
		}

		flag1 = 1;
		r2 = flag0;

		ReleaseSemaphore(endSemaphore, 1, NULL);
	}
};

void reordering_experiment()
{
	beginEvent1 = CreateEvent(nullptr, FALSE, FALSE, nullptr);
	beginEvent2 = CreateEvent(nullptr, FALSE, FALSE, nullptr);
	endSemaphore = CreateSemaphore(nullptr, 0, 99, nullptr);

	std::thread first_thread(thread1);  first_thread.detach();
	std::thread second_thread(thread2); second_thread.detach();

	constexpr size_t ITERATIONS = 1000000;

	size_t detected = 0;
	for (size_t iterations = 1; iterations < ITERATIONS; iterations++)
	{
		flag0 = 0;
		flag1 = 0;

		SetEvent(beginEvent1);
		SetEvent(beginEvent2);

		WaitForSingleObject(endSemaphore, INFINITE);
		WaitForSingleObject(endSemaphore, INFINITE);
		
		// Check if there was a simultaneous reorder
		if (r1 == 0 && r2 == 0)
		{
			detected++;
			std::cout << detected << " reorders detected after " << iterations << " iterations\n";
		}
	}

	TerminateThread(first_thread.native_handle(), 0);
	TerminateThread(second_thread.native_handle(), 0);

	getchar();
}


