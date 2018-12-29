#include "Modernizing4.h"

#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

// In this lab, try to focus on converting loops and other constructs to STL algorithms
// and lambda functions if necessary.

void average_printer()
{
	// Read 5 numbers from the input, print the positive ones,
	// and print the average of all the numbers.
	int number;
	std::vector<int> numbers;
	for (int i = 0; i < 5; ++i) {
		std::cin >> number;
		numbers.push_back(number);
	}
	double sum = 0.0;
	for (int i = 0; i < 5; ++i) {
		if (i > 0) {
			std::cout << numbers[i] << std::endl;
		}
		sum += numbers[i];
	}
	std::cout << "average = " << (sum / 5) << std::endl;
}
// Hints: copy_n, istream_iterator, back_inserter, copy_if, ostream_iterator, accumulate

std::string common_prefix(std::string const& a, std::string const& b) {
	std::string result = "";
	size_t shorter = std::min(a.size(), b.size());
	for (size_t i = 0; i < shorter; ++i) {
		if (a[i] == b[i]) {
			result += a[i];
		}
		else {
			break;
		}
	}
	return result;
}
// Hint: std::mismatch

