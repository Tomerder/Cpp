#include "Modernizing5.h"

#include <cmath>
#include <vector>

#include <Windows.h>

// Adapted from sample code, Win32 Concurrent Programming course, Sela

bool is_prime(unsigned n) {
	if (n % 2 != 0) {
		unsigned root = static_cast<unsigned>(std::sqrt(n));
		for (unsigned d = 3; d <= root; d += 2) {
			if (n % d == 0) return false;
		}
		return true;
	}
	return n == 2;
}

struct search_range {
	unsigned start_;
	unsigned end_;
	primes_vector& primes_;
	CRITICAL_SECTION& lock_;

	search_range(unsigned start, unsigned end, primes_vector& primes, CRITICAL_SECTION& lock) :
		start_(start), end_(end), primes_(primes), lock_(lock) {}
};

DWORD WINAPI primes_thread(LPVOID param) {
	search_range* range = static_cast<search_range*>(param);
	for (unsigned n = range->start_; n < range->end_; ++n) {
		if (is_prime(n)) {
			EnterCriticalSection(&range->lock_);
			range->primes_.push_back(n);
			LeaveCriticalSection(&range->lock_);
		}
	}
	return 0;
}

void find_primes(unsigned start, unsigned end, primes_vector& primes, unsigned parallelism) {
	unsigned chunk_size = (end - start) / parallelism;
	search_range** ranges = new search_range*[parallelism];
	HANDLE* threads = new HANDLE[parallelism];
	CRITICAL_SECTION lock;
	InitializeCriticalSection(&lock);
	for (unsigned p = 0; p < parallelism; ++p) {
		ranges[p] = new search_range(start + p*chunk_size, start + (p + 1)*chunk_size, primes, lock);
		threads[p] = CreateThread(NULL, 0, primes_thread, static_cast<LPVOID>(ranges[p]), 0, NULL);
	}
	WaitForMultipleObjects(parallelism, threads, TRUE, INFINITE);
}
