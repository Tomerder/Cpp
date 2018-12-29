#pragma once

#include <future>
#include <iostream>

#include <pplawait.h>

std::future<int> simple_resumable()
{
	auto f1 = std::async([] { return 42; });
	auto f2 = std::async([] { return 17; });
	int sum = 0;
	sum += __await f1;
	sum += __await f2;
	return sum;
}

concurrency::task<DWORD> write_to_three_files_async()
{
	unsigned sum_written = 0;
	for (int i = 0; i < 3; ++i)
	{
		text_file f{ L"test.txt", filemode::readwrite, fileshare::none, filedisposition::create };
		auto written = __await f.write_async("Hi async!", 0);
		std::cout << "wrote " << written << " bytes to file #" << i << "\n";
		sum_written += written;
	}
	return sum_written;
}

template <typename TaskIter, typename Callback>
concurrency::task<void> when_any_awaitable_repeat(TaskIter first, TaskIter last, Callback callback)
{
	while (first != last)
	{
		auto pair = __await concurrency::when_any(first, last);
		callback(pair);
		--last;
		std::swap(*(first + pair.second), *last);
	}
}

concurrency::task<DWORD> write_to_three_files_at_once_async()
{
	unsigned sum_written = 0;
	std::vector<concurrency::task<DWORD>> tasks;
	for (int i = 0; i < 3; ++i)
	{
		text_file f{ L"test.txt", filemode::readwrite, fileshare::none, filedisposition::create };
		tasks.push_back(f.write_async("Hi async!", 0));
	}
	__await when_any_awaitable_repeat(tasks.begin(), tasks.end(), [&](std::pair<DWORD, size_t> const& pair) {
		std::cout << "wrote " << pair.first << " bytes to file #" << pair.second << "\n";
		sum_written += pair.first;
	});
	return sum_written;
}

void test_await()
{
	simple_resumable().wait();
	write_to_three_files_async().wait();
	write_to_three_files_at_once_async().wait();
}
