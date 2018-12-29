#pragma once

#include <ppl.h>

#include <vector>
#include <random>

#include "timer.h"


// taken from wikipedia
void basic_parallel_quicksort(int arr[], int left, int right)
{
	int i = left, j = right;
	int tmp;
	int pivot = arr[(left + right) / 2];

	/* partition */
	while (i <= j) {
		while (arr[i] < pivot)
			i++;
		while (arr[j] > pivot)
			j--;
		if (i <= j) {
			tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
			i++;
			j--;
		}
	};

	concurrency::task_group group;

	/* recursion */
	if (left < j)
		group.run([=] {basic_parallel_quicksort(arr, left, j); });
	if (i < right)
		group.run([=] {basic_parallel_quicksort(arr, i, right); });

	group.wait();
}



constexpr size_t PAR_THRESHOLD = 500;

template <typename RanIt, typename Predicate>
void parallel_quicksort(RanIt first, RanIt last, Predicate predicate)
{
	auto count = last - first;
	if (count <= 1)
	{
		return;
	}
	
	if (count < PAR_THRESHOLD)
	{
		std::sort(first, last, predicate);
		return;
	}
	
	auto mid = first + count / 2;
	auto pivot_val = *mid;

	// std::partition reorders the elements in the range[first, last) in such a way that all elements for which the predicate p returns true precede the elements for which predicate p returns false
	auto pivot = std::partition(first, last, [&](auto const& element) { return predicate(element, pivot_val); });

	concurrency::task_group group;
	group.run([&] { parallel_quicksort(first, pivot, predicate); });
	group.run_and_wait([&] { parallel_quicksort(pivot + 1, last, predicate); });
}

template <typename RanIt>
void parallel_quicksort(RanIt first, RanIt last)
{
	parallel_quicksort(first, last, std::less<>{});
}

std::vector<int> random_vector(size_t size)
{
	std::mt19937 random;
	std::vector<int> result;
	std::generate_n(std::back_inserter(result), size, random);
	return result;
}

void test_sort()
{
	constexpr size_t SIZE = 100000;
	{
		auto vec = random_vector(SIZE);
		timer t{ "sequential" };
		std::sort(vec.begin(), vec.end());
	}
	{
		auto vec = random_vector(SIZE);
		timer t{ "parallel" };
		parallel_quicksort(vec.begin(), vec.end());
	}
}
