#pragma once

#include <type_traits>
#include <chrono>
#include <iostream>
#include <thread>

template <typename Fn>
auto get_timed_invoker(Fn&& fn)
{
	return [f = std::forward<Fn>(fn)](auto&&... args) mutable
	{
		auto begin = std::chrono::high_resolution_clock::now();
		std::forward<decltype(f)>(f)(std::forward<decltype(args)>(args)...);
		auto end = std::chrono::high_resolution_clock::now();
		auto duration_us = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
		std::cout << "elapsed time: " << duration_us << " us" << std::endl;
	};
}

void forwarding_lambda()
{
	using namespace std::chrono_literals;

	auto timer = get_timed_invoker([](std::chrono::milliseconds delay) { std::this_thread::sleep_for(delay); });
	timer(3000ms);
}