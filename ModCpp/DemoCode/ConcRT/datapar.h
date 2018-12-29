#pragma once

#include <ppl.h>
#include <concurrent_vector.h>

#include <atomic>
#include <iostream>

#include "timer.h"

constexpr unsigned START = 2;
constexpr unsigned END = 5000000;

bool is_prime(unsigned n)
{
	if (n % 2 != 0)
	{
		auto root = static_cast<unsigned>(std::sqrt(static_cast<double>(n)));
		for (auto d = 3u; d <= root; d += 2)
		{
			if (n % d == 0)
			{
				return false;
			}
		}
		return true;
	}
	return n == 2;
}

template <typename Partitioner>
void do_primes_count(Partitioner const& partitioner)
{
	std::atomic<int> primes{ 0 };
	concurrency::parallel_for(START, END, [&primes](unsigned n) {
		if (is_prime(n))
		{
			++primes;
		}
	}, partitioner);
}

void primes_count()
{
	{
		timer t{ "static partitioner" };
		do_primes_count(concurrency::static_partitioner());
	}
	{
		timer t{ "auto partitioner" };
		do_primes_count(concurrency::auto_partitioner());
	}
	{
		timer t{ "simple partitioner, chunk size 100" };
		do_primes_count(concurrency::simple_partitioner(100));
	}
}

void primes_sum()
{
	concurrency::concurrent_vector<int> primes;
	concurrency::parallel_for(START, END, [&primes](unsigned n) {
		if (is_prime(n))
		{
			primes.push_back(n);
		}
	});
	std::cout << "sum of primes = " << concurrency::parallel_reduce(primes.begin(), primes.end(), 0) << "\n";
}

void primes_combinable()
{
	{
		timer t{ "no combinable" };
		std::atomic<int> primes{ 0 };

		// wrap with concurrency::task_group for cancelation, or concurrency::run_with_cancellation_token
		concurrency::parallel_for(START, END, [&primes](unsigned n) {
			if (is_prime(n))
			{
				++primes;
			}
		});
	}
	{
		timer t{ "combinable" };
		concurrency::combinable<int> primes;
		concurrency::parallel_for(START, END, [&primes](unsigned n) {
			if (is_prime(n))
			{
				// local is local for evey thread that save according to the thread id inside the combinable

				// NOTE: local() is a rather expensive operation, and ideally we would only call it once and
				// then use it for a number of iterations. In this case, we don't have the luxury of this
				// optimization because each loop body only runs one iteration.
				++primes.local();
			}
		});

		// version 1
		int total_count = 0;
		primes.combine_each([&](int local_count) { total_count += local_count; });

		//version 2
		primes.combine(std::plus<>{});

	}
}