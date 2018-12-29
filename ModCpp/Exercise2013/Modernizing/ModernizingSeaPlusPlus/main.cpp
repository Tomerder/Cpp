#include "Modernizing4.h"
#include "Modernizing5.h"

#include <iostream>
#include <vector>

int main()
{
	// Ignore me -- I'm just here for the #5 lab so you can make sure
	// your changes work correctly.

	primes_vector primes;
	find_primes(2, 100, primes, 4);

	// Ignore me -- I'm just here for the #4 lab so you can make sure
	// your changes work correctly.

	average_printer();
	std::cout << common_prefix("catnip", "cats") << std::endl;

	std::vector<int> v1{ 1, 4, 7, 10, 13 };
	std::vector<int> v2{ 1, 4, 3, 7, 10 };
	std::vector<int> v3{ 1, 4, 7, 10, 14 };
	std::cout << std::boolalpha << is_arithmetic_series(v1.begin(), v1.end()) << std::endl;
	std::cout << std::boolalpha << is_arithmetic_series(v2.begin(), v2.end()) << std::endl;
	std::cout << std::boolalpha << is_arithmetic_series(v3.begin(), v3.end()) << std::endl;

	return 0;
}