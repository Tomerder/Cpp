#include "timer.h"

#include <iostream>

timer::timer(std::string description) : description_(std::move(description))
{
	start_ = std::chrono::high_resolution_clock::now();
}

timer::~timer()
{
	auto end_ = std::chrono::high_resolution_clock::now();
	std::cout << "[" << description_ << "] elapsed " << std::chrono::duration_cast<std::chrono::microseconds>(end_ - start_).count() << " us\n";
}
