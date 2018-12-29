#pragma once

#include <regex>
#include <iostream>
#include <chrono>

using namespace std::string_literals;

void string_literals()
{
	std::wregex email(LR"((\d|[A-z])+@[A-z]+\.(com|org|net))");
	if (std::regex_search(L"dave55@gmail.com", email))
	{
		std::cout << "match!" << std::endl;
	}

	std::regex quoted_phone(R"**(^\w+\ "(\d+-\d+)"$)**");
	std::smatch results;
	auto input = "Dave \"555-1212\""s;	// std::string literal
	if (std::regex_match(input, results, quoted_phone))
	{
		std::cout << results[1] << std::endl;
	}
}

unsigned long long operator "" _kb(unsigned long long v)
{
	return v * 1024ULL;
}
unsigned long long operator "" _mb(unsigned long long v)
{
	return v * 1024ULL * 1024ULL;
}
unsigned long long operator "" _gb(unsigned long long v)
{
	return v * 1024ULL * 1024ULL * 1024ULL;
}

void user_defined_literals()
{
	std::cout << "fifteen and a half megabytes: " << (15_mb + 512_kb) << " bytes" << std::endl;

	using namespace std::chrono_literals;

	auto break_time = 1h + 15min;
	auto now = std::chrono::system_clock::now();
	now += break_time;
	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count() << std::endl;
}