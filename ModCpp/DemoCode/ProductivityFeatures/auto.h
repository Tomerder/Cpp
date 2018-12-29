#pragma once

#include <map>
#include <string>
#include <iostream>

void examples_and_type_deduction()
{
	std::map<std::string, double> salaries{ {"Dave", 90000}, {"Mike", 45000}, {"Kate", 120000} };
	for (auto it = salaries.begin(); it != salaries.end(); ++it)
	{
		// 'it' is std::map<std::string, double>::iterator
		it->second *= 1.03;
	}

	auto mike = *salaries.find("Mike");
	// 'mike' is std::pair<std::string const, double>, so we're modifying an object outside the map
	mike.second *= 1.06;

	// error C2440: 'initializing': cannot convert from 'std::pair<const _Kty,_Ty>' to 'std::pair<std::string,double> &'
	// std::pair<std::string, double>& p = *salaries.find("Mike");

	// The following compiles, but the pair is copied into 'p'!
	std::pair<std::string, double> const& p = *salaries.find("Mike");

	auto& dave = *salaries.find("Dave");
	// 'dave' is std::pair<std::string const, double>&
	dave.second *= 1.08;

	auto const& kate1 = *salaries.find("Kate");
	
	const auto& kate = *salaries.find("Kate");
	// 'kate' is std::pair<std::string const, double> const&
	std::cout << kate.second << std::endl;

}

template <typename Iter, typename T>
size_t count_all(Iter first, Iter last, T const& val)
{
	size_t count = 0;
	while (first != last)
	{
		// 'temp' is 'typename Iter::value_type'
		auto temp = *first;
		if (temp == val)
		{
			++count;
		}
		++first;
	}
	return count;
}