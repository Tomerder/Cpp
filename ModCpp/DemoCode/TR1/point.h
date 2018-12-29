#pragma once

#include <cmath>

class point
{
private:
	int x_, y_;
public:
	point(int x, int y) : x_(x), y_(y)
	{
	}
	bool is_less(point const& other) const
	{
		return x_ < other.x_;
	}
	double distance_from(point const& other) const
	{
		double dx = x_ - other.x_;
		double dy = y_ - other.y_;
		return std::sqrt(dx*dx + dy*dy);
	}
	void set_x(int x)
	{
		x_ = x;
	}
};
