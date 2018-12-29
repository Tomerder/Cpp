#pragma once

#include <functional>

int add(int a, int b)
{
	return a + b;
}

struct binaryadd
{
	int operator()(int a, int b) const
	{
		return a + b;
	}
};

struct unaryadd
{
	int const b_;

	unaryadd(int b) : b_(b)
	{
	}

	int operator()(int a) const
	{
		return a + b_;
	}
};

void stdfunction()
{
	std::function<int(int, int)> f = add;
	f(5, 3);	// returns 8

	f = binaryadd();
	f(5, 3);	// returns 8

	std::function<int(int)> g = unaryadd(42);
	g(5);		// returns 47
}
