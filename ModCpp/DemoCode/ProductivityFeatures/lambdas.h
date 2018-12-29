#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <numeric>
#include <random>
#include <iterator>
#include <future>

#pragma region STL is great


void stl_is_great1()
{
	std::vector<int> ints;
	std::copy(
		std::istream_iterator<int>(std::cin),
		std::istream_iterator<int>(),
		std::back_inserter(ints)
		);
	std::copy(
		ints.begin(), ints.end(),
		std::ostream_iterator<int>(std::cout, "\n")
		);
}

// stl_is_great2
int range_sum(std::set<int> const& s, int start, int end) {
	return std::accumulate(
		s.lower_bound(start),
		s.upper_bound(end),
		0
		);
}

void stl_is_great3a()
{
	std::vector<std::string> cards { "Jack of Spades", "8 of Hearts", "3 of Diamonds", "Queen of Hearts" };
	std::random_shuffle(cards.begin(), cards.end());
}

// stl_is_great3b
bool is_palindrome(std::string s) {
	return std::equal(
		s.begin(),
		s.begin() + s.size() / 2,
		s.rbegin()
		);
}

// stl_is_great4
template <typename InputIterator>
bool is_sorted(InputIterator first, InputIterator last) {
	return std::adjacent_find(
		first, last,
		std::greater<decltype(*first)>()
		) == last.end();
}

#pragma endregion

#pragma region Lambda		

void stateless_lambdas()
{
	std::vector<int> numbers(100);
	std::mt19937 rng(std::random_device{}());
	std::generate(numbers.begin(), numbers.end(), rng);

	std::count_if(numbers.begin(), numbers.end(),
		[](int n) { return n < 17; }
		);

	// AS IF
	struct lambda_count_if
	{
		bool operator()(int n) const
		{
			return n < 17;
		}
	};
	std::count_if(numbers.begin(), numbers.end(), lambda_count_if{});

	std::vector<int> squares;
	std::transform(numbers.begin(), numbers.end(), std::back_inserter(squares),
		[](int n) { return n * n; }
		);


	// AS IF
	struct lambda_transform
	{
		int operator()(int n) const
		{
			return n * n;
		}
	};

	std::transform(numbers.begin(), numbers.end(), std::back_inserter(squares), lambda_transform{});


	int x = 17;
	auto lambda = [x]() mutable { ++x; };
	lambda();
	lambda();

	// AS IF
	struct lambda_17
	{
		int x_;

		lambda_17(int x):x_(x){}
		void operator()() 
		{
			++x_;
		}
	};


}

#pragma endregion

#pragma region parallel_invoke machinery

bool is_prime(unsigned n)
{
	if (n % 2 != 0)
	{
		auto root = static_cast<unsigned>(std::sqrt(static_cast<double>(n)));
		for (auto d = 3u; d <= root; d += 3)
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

void parallel_invoke()
{
}

template <typename F1, typename... Fs>
void parallel_invoke(F1&& f1, Fs&&... fs)
{
	auto fut = std::async(std::forward<F1>(f1));
	parallel_invoke(fs...);
	fut.wait();
}

#pragma endregion

#pragma region stateful_lambdas

void stateful_lambdas()
{
	std::vector<int> numbers(100);
	std::mt19937 rng(std::random_device{}());
	std::generate(numbers.begin(), numbers.end(), rng);

	int less_than_what;
	std::cin >> less_than_what;
	std::count_if(numbers.begin(), numbers.end(),
		[less_than_what](int n) { return n < less_than_what; }
	);

	// AS if
	struct lambda_less_than_what
	{
		int _less_than_what;
		lambda_less_than_what(int less_than_what) :_less_than_what{ less_than_what } {}
		bool operator()(int n) { return n < _less_than_what; }

	};

	less_than_what = 0;
	auto lm = lambda_less_than_what{ less_than_what };
	std::count_if(numbers.begin(), numbers.end(), lm);



	std::atomic<size_t> primes{ 0 };
	auto l1 = [&primes]() {
		for (auto n = 2u; n < 100000u; ++n)
		{
			if (is_prime(n))
			{
				++primes;
			}
		}
	};

	// AS if
	struct lambda1
	{
		std::atomic<size_t>& _primes;
		lambda1(std::atomic<size_t>& primes) :_primes{ primes } {}
		void operator()() { _primes++; }

	};

	auto l2 = [&primes]() {
		for (auto n = 100000u; n < 200000u; ++n)
		{
			if (is_prime(n))
			{
				++primes;
			}
		}
	};
	parallel_invoke(l1, l2);
}

template <typename Iter>
auto product(Iter first, Iter last)
{
	auto initial = *first;
	return std::accumulate(
		++first, last,
		initial,
		[](auto x, auto y) { return x * y; }
	);
}

void generic_lambdas()
{
	std::vector<int> numbers{ 1,2,3,4,5 };
	std::cout << product(numbers.begin(), numbers.end()) << std::endl;
}

#pragma endregion