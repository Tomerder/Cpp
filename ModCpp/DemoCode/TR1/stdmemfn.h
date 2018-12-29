#pragma once

#include <vector>
#include <functional>
#include <algorithm>
#include <map>

#include "point.h"

void sort_points()
{
	std::vector<point> points{ {3, 5}, {1, 2}, {4, 0}, {-2, 5}, {0, 1} };
	
	// error C2064: term does not evaluate to a function taking 2 arguments	
	//std::sort(points.begin(), points.end(), &point::is_less);

}

void sort_points_mem_fn()
{
	std::vector<point> points{ { 3, 5 },{ 1, 2 },{ 4, 0 },{ -2, 5 },{ 0, 1 } };
	
	std::vector<int> pint{ 1,2,3,4 };
 	
	std::sort(points.begin(), points.end(), std::mem_fn(&point::is_less));
}


void count_curious_points()
{
	struct point_cmp : public std::binary_function<point, point, bool>
	{
		bool operator()(point const& a, point const& b) const
		{
			return a.is_less(b);

		}
	};

	std::map<point, bool, point_cmp> points{
		{{1, 1}, true },
		{{3, 5}, false},
		{{0, 0}, true },
		{{-1,3}, false}
	};

	std::count_if(points.begin(), points.end(), std::mem_fn(&std::pair<point const, bool>::second));
}