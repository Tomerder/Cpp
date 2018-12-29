#pragma once

#include <iostream>

void print(int* p)
{
	if (!p) return;
	std::cout << *p << std::endl;
}

void print(int n)
{
	std::cout << n << std::endl;
}

void using_nullptr()
{
	print(0);		// calls print(int)
	print(nullptr);	// calls print(int*)
}