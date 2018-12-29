#pragma once

#include <string>

void average_printer();

std::string common_prefix(std::string const& a, std::string const& b);

template <typename InputIterator>
bool is_arithmetic_series(InputIterator first, InputIterator last) {
	if (first == last) {
		return true; // A sequence with no elements is an arithmetic series
	}
	typename InputIterator::value_type previous = *first;
	++first;
	if (first == last) {
		return true; // A sequence with one element is an arithmetic series
	}
	typename InputIterator::value_type difference = *first - previous;
	while (first != last) {
		previous = *first;
		++first;
		if (first == last)
			return true;
		typename InputIterator::value_type temp = *first - previous;
		if (temp != difference) {
			return false;
		}
	}
	return true;
}
// Hint: std::adjacent_difference or std::adjacent_find

