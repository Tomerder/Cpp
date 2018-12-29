#pragma once

#include <vector>
#include <map>
#include <string>
#include <initializer_list>
#include <iostream>

class point
{
private:
	int x_, y_;
public:
	point(int x, int y) : x_(x), y_(y)
	{
	}
};

void simple_initialization()
{
	std::vector<int> numbers{ 1,2,3 };

	std::map<std::string, double> salaries{
		{"Dave", 85000}, {"Kate", 105000}
	};

	point origin{ 0,0 };
	std::vector<point> points{ {1,1}, {2,2} };
}

template <typename T>
void print_many(std::initializer_list<T> const& list)
{
	for (auto const& t : list)
	{
		std::cout << t << std::endl;
	}
}

void use_initializer_list()
{
	print_many({ 1,2,3 });
}