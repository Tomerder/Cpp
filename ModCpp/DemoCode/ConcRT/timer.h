#pragma once

#include <string>
#include <chrono>

class timer
{
public:
	timer(std::string description);
	~timer();
private:
	std::chrono::high_resolution_clock::time_point start_;
	std::string description_;
};