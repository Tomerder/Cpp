#pragma once

#include <vector>
#include <algorithm>
#include <functional>
#include <iterator>



template <typename Container>
decltype(std::declval<Container>()[size_t()]) get_at2(Container& container, size_t index)
{
	return container[index];
}




template <typename Fn, typename Arg>
auto apply(Fn fn, std::vector<Arg> const& args) -> std::vector<decltype(fn(args[0]))>
{
	std::vector<decltype(fn(args[0]))> results;
	for (size_t i = 0; i < args.size(); ++i)
	{
		results.push_back(fn(args[i]));
	}
	return results;
}

template <typename Fn, typename Arg>
std::vector<decltype(std::declval<Fn>()(std::declval<Arg>()))> apply2(Fn fn, std::vector<Arg> const& args)
{
	std::vector<decltype(std::declval<Fn>()(std::declval<Arg>()))> results;
	for (size_t i = 0; i < args.size(); ++i)
	{
		results.push_back(fn(args[i]));
	}
	return results;
}

template <typename Fn, typename Arg>
std::vector<typename std::result_of<Fn(Arg)>::type> apply3(Fn fn, std::vector<Arg> const& args)
{
	std::vector<typename std::result_of<Fn(Arg)>::type> results;
	for (size_t i = 0; i < args.size(); ++i)
	{
		results.push_back(fn(args[i]));
	}
	return results;
}

template <typename Fn, typename Arg>
auto apply4(Fn fn, std::vector<Arg> const& args)
{
	// This is the most accurate option, because if 'fn' returns a reference,
	// we can't create a vector of references. The decay_t invocation will 
	// remove reference qualifiers, among other things.
	using result_t = std::decay_t<decltype(fn(args[0]))>;
	std::vector<result_t> results;
	for (size_t i = 0; i < args.size(); ++i)
	{
		results.push_back(fn(args[i]));
	}
	return results;
}

// A function for testing apply4 (returns a reference)
int& get_int(int input)
{
	static int static_val;
	static_val = input;
	return static_val;
}

void apply_examples()
{
	using namespace std::placeholders;

	std::vector<int> v{ 1,2,3,4,5 };

	// Add 1 to each element
	auto fn = std::bind(std::plus<int>(), _1, 1);

	auto v2 = apply(fn, v);
	auto v3 = apply2(fn, v);
	auto v4 = apply3(fn, v);

	std::vector<decltype(fn(v[0]))> v5;
	std::transform(v.begin(), v.end(), std::back_inserter(v5), fn);

	auto v6 = apply4(get_int, v);
	// auto v7 = apply3(get_int, v); // doesn't compile because vector<int&> isn't allowed
}

template <typename FwdIter, typename Combiner>
auto reduce(FwdIter first, FwdIter last, Combiner combiner) -> decltype(combiner(*first, *first))
{
	auto accumulator = *first;
	++first;
	while (first != last)
	{
		accumulator = combiner(accumulator, *first);
		++first;
	}
	return accumulator;
}

void use_reduce()
{
	std::vector<int> v{ 1,2,3,4,5 };
	int sum = reduce(v.begin(), v.end(), std::plus<int>());
}

auto fibonacci(unsigned n)
{
	if (n == 1 || n == 2)
	{
		return 1;
	}
	return fibonacci(n - 1) + fibonacci(n - 2);
}



// c++ 98 
template <typename Container>
typename Container::value_type get_at(Container& container, size_t index)
{
	return container[index];
}

//c++ 11
template <typename Container>
 auto get_at(Container& container, size_t index) -> decltype(container[index])
{
	return container[index];
}


// c++ 14
template <typename Container>
auto get_at3(Container& container, size_t index)
{
	return container[index];
}

// c++ 14
template <typename Container>
decltype(auto) get_at4(Container& container, size_t index)
// equivalent to: auto ... -> decltype(container[index])
{
	return container[index];
}

void use_get_at()
{
	std::vector<int> v{ 1,2,3 };

	// error C2106: '=': left operand must be l-value
	// get_at3(v, 2) = 4;

	get_at4(v, 2) = 4;

	int x = 42;
	int& r = x;
	auto a = r;				// a is 'int'
	decltype(auto) b = r;	// b is 'int&'
}