#pragma once

#include <vector>
#include <functional>
#include <algorithm>
#include <iterator>
#include <iostream>


#include "point.h"

int add_func(int a, int b)
{
	return a + b;
}

void bind_with_add()
{
	using namespace std::placeholders;

	std::function<int(void)> f = std::bind(add_func, 3, 5);
	f();

	std::bind(add_func, _1, 2)(3);
	std::bind(add_func, _1, _1)(3);
	std::bind(add_func, _1, _2)(2,3);
	std::bind(add_func, _2, _1)(2, 3);
}


bool relation_to_42(int n, bool smaller_than)
{
	if (smaller_than) return n < 42;
	else              return n > 42;
}

void fun_with_numbers()
{

	std::vector<int> numbers{ 13, 45, 0, -11, 89 };

	//std::count_if(numbers.begin(), numbers.end(), relation_to_42);








	using namespace std::placeholders;


	// Counts elements smaller than 42
	std::count_if(numbers.begin(), numbers.end(), std::bind(relation_to_42, _1, true));

	// Alternative, using std::less
	std::count_if(numbers.begin(), numbers.end(), std::bind(std::less<int>(), _1, 42));

	std::vector<int> squares;
	std::transform(numbers.begin(), numbers.end(), std::back_inserter(squares),
		std::bind(std::multiplies<int>(), _1, _1));
}

// bind with memeber function
void more_points()
{
	using namespace std::placeholders;

	std::vector<point> points{ { 3, 5 },{ 1, 2 },{ 4, 0 },{ -2, 5 },{ 0, 1 } };

	point origin{ 0, 0 };
	std::transform(points.begin(), points.end(), std::ostream_iterator<double>(std::cout, "\n"),
		std::bind(&point::distance_from, origin, _1));
}

void byref_and_byval()
{
	using namespace std::placeholders;

	point center{ 0, 0 };
	point p{ 1, 3 };

	std::function<bool(point const&)> pred = std::bind(&point::is_less, _1, center);
	pred(p);	// returns false
	
	center.set_x(3);
	pred(p);	// still returns false, the bound object wasn't modified

	pred = std::bind(&point::is_less, _1, std::cref(center));
	pred(p);	// returns true

	center.set_x(-1);
	pred(p);	// returns false
}