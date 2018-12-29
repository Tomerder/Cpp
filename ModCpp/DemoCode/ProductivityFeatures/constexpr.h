#pragma once

#include <type_traits>
#include <iostream>

constexpr unsigned long long factorial(unsigned long long n)
{
	return n <= 1 ? 1 : n*factorial(n - 1);
}

// Makes sure that the value is indeed known at compile-time
template <unsigned long long N>
struct evaluator : std::integral_constant<unsigned long long, N>
{
};

template <typename T, size_t N>
constexpr size_t ARRAYSIZE(T(&)[N])
{
	return N;
}

void using_constexpr()
{
	std::cout << "factorial(18) = " << evaluator<factorial(18)>::value << std::endl;

	char const name[] = "Michael Douglas";
	std::cout << ARRAYSIZE(name) << std::endl;
}
