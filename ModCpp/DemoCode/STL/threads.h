#pragma once

#include <thread>
#include <future>
#include <cmath>
#include <array>
#include <iostream>

void simple_tread()
{
	int result;
	std::thread t([&result]
	{
		std::this_thread::sleep_for(std::chrono::seconds(5));
		result = 42;
	});
	
	t.join(); // what if we remove this join?
	
	//t.detach();

	std::cout << result << std::endl;
}



bool is_prime(unsigned n)
{
	if (n % 2 != 0)
	{
		unsigned root = static_cast<unsigned>(std::sqrt(static_cast<double>(n)));
		for (unsigned d = 3; d <= root; d += 2)
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

void primes_with_threads()
{
	constexpr unsigned START = 2;
	constexpr unsigned END = 5000000;
	constexpr unsigned THREADS = 4;

	std::atomic<size_t> primes_count{ 0 };
	std::array<std::thread, THREADS> threads;
	for (auto i = 0u; i < threads.size(); ++i)
	{
		auto this_start = i*((END - START) / THREADS);
		auto this_end = (i + 1)*((END - START) / THREADS);
		threads[i] = std::thread([=,&primes_count] {
			for (auto n = this_start; n <= this_end; ++n)
			{
				if (is_prime(n))
				{
					++primes_count;
				}
			}
		});
	}
	for (auto& t : threads)
	{
		t.join();
	}
	std::cout << "primes with threads: " << primes_count << "\n";
}

template <typename Body>
void async_for(size_t start, size_t end, size_t chunks, Body body)
{
	std::vector<std::future<void>> futures;
	size_t chunk_size = (end - start) / chunks;
	for (auto i = 0u; i < chunks; ++i)
	{
		auto this_start = i*chunk_size;
		auto this_end = (i + 1)*chunk_size;
		futures.push_back(std::async([=] {
			for (auto n = this_start; n <= this_end; ++n)
			{
				body(n);
			}
		}));
	}
	for (auto& fut : futures)
	{
		fut.wait();
	}
}

void primes_with_async()
{
	constexpr unsigned START = 2;
	constexpr unsigned END = 5000000;
	constexpr unsigned CHUNKS = 1000;

	std::atomic<size_t> primes_count{ 0 };
	async_for(START, END, CHUNKS, [&](unsigned n) {
		if (is_prime(n))
		{
			++primes_count;
		}
	});
	std::cout << "primes with async: " << primes_count << "\n";
}