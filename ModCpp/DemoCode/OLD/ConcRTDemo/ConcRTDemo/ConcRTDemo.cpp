
#include "stdafx.h"

#include <Windows.h>
#include <concrt.h>
#include <ppl.h>
#include <concurrent_queue.h>
#include <concurrent_vector.h>
#include <iostream>
#include <random>
#include <array>

const int END_WORK = -42;

//---- PRODUCER_CONSUMER ----

void producer_consumer() {

	using namespace Concurrency;

	concurrent_queue<int> work;
	structured_task_group group;
	auto producer = make_task([&work] {
		for (int i = 0; i < 10000; ++i) {
			work.push(i);
			if (i % 47 == 0)
				wait(10);
		}
		work.push(END_WORK);
		std::cout << GetCurrentThreadId() << "-Producer done." << std::endl;
	});
	auto consumer = make_task([&work] {
		int n;
		do {
			bool result = work.try_pop(n);
			if (!result)
				wait(10);
		} while (n != END_WORK);
		std::cout << GetCurrentThreadId() << "-Consumer done, last value was: " << n << std::endl;
	});
	group.run(producer);
	group.run(consumer);
	group.wait();
}

//---- SORTING ----
//Adapted from http://msdn.microsoft.com/en-us/library/dd728066.aspx.

template <class Function>
__int64 time_call(Function&& f)
{
   __int64 begin = GetTickCount();
   f();
   return GetTickCount() - begin;
}

const bool INCREASING = true;
const bool DECREASING = false;

template <class T>
void compare(T* items, int i, int j, bool dir)
{
   if (dir == (items[i] > items[j]))
   {
	  std::swap(items[i], items[j]);
   }
}

// Sorts a bitonic sequence in the specified order.
template <class T>
void bitonic_merge(T* items, int lo, int n, bool dir)
{
   if (n > 1)
   {
	  int m = n / 2;
	  for (int i = lo; i < lo + m; ++i)
	  {
		 compare(items, i, i + m, dir);
	  }
	  bitonic_merge(items, lo, m, dir);
	  bitonic_merge(items, lo + m, m, dir);
   }
}

// Sorts the given sequence in the specified order.
template <class T>
void bitonic_sort(T* items, int lo, int n, bool dir)
{
   if (n > 1)
   {
	  // Divide the array into two partitions and then sort 
	  // the partitions in different directions.
	  int m = n / 2;
	  bitonic_sort(items, lo, m, INCREASING);
	  bitonic_sort(items, lo + m, m, DECREASING);

	  // Merge the results.
	  bitonic_merge(items,lo, n, dir);
   }
}

// Sorts the given sequence in increasing order.
template <class T>
void bitonic_sort(T* items, int size)
{
	bitonic_sort(items, 0, size, INCREASING);
}

// Sorts a bitonic sequence in the specified order. (Parallel version.)
template <class T>
void parallel_bitonic_merge(T* items, int lo, int n, bool dir)
{   
   // Merge the sequences concurrently if there is sufficient work to do.
   if (n > 500)
   {
	  int m = n / 2;
	  for (int i = lo; i < lo + m; ++i)
	  {
		 compare(items, i, i + m, dir);
	  }

	  // Use the parallel_invoke algorithm to merge the sequences in parallel.
	  Concurrency::parallel_invoke(
		 [&items,lo,m,dir] { parallel_bitonic_merge(items, lo, m, dir); },
		 [&items,lo,m,dir] { parallel_bitonic_merge(items, lo + m, m, dir); }
	  );
   }
   // Otherwise, perform the work serially.
   else if (n > 1)
   {
	  bitonic_merge(items, lo, n, dir);
   }   
}

// Sorts the given sequence in the specified order.
template <class T>
void parallel_bitonic_sort(T* items, int lo, int n, bool dir)
{   
   if (n > 1)
   {
	  // Divide the array into two partitions and then sort 
	  // the partitions in different directions.
	  int m = n / 2;

	  // Sort the partitions in parallel.
	  Concurrency::parallel_invoke(
		 [&items,lo,m] { parallel_bitonic_sort(items, lo, m, INCREASING); },
		 [&items,lo,m] { parallel_bitonic_sort(items, lo + m, m, DECREASING); }
	  );

	  // Merge the results.
	  parallel_bitonic_merge(items, lo, n, dir);
   }
}

// Sorts the given sequence in increasing order.
template <class T>
void parallel_bitonic_sort(T* items, int size)
{
   parallel_bitonic_sort(items, 0, size, INCREASING);
}

void measure_sort()
{  
   // For this example, the size must be a power of two.
   const int size = 0x200000;

   // Create two large arrays and fill them with random values.
   int* a1 = new int[size];
   int* a2 = new int[size];

   std::mt19937 gen(42);
   for(int i = 0; i < size; ++i)
   {
	  a1[i] = a2[i] = gen();
   }

   __int64 elapsed;

   // Perform the serial version of the sort.
   elapsed = time_call([&] { bitonic_sort(a1, size); });
   std::wcout << L"serial time: " << elapsed << std::endl;

   // Now perform the parallel version of the sort.
   elapsed = time_call([&] { parallel_bitonic_sort(a2, size); });
   std::wcout << L"parallel time: " << elapsed << std::endl;

   delete[] a1;
   delete[] a2;
}

//---- FILTER_SQUARES ----

void filter_squares() {
	
	using namespace Concurrency;

	concurrent_vector<int> squares;
	Concurrency::parallel_for(3, 200000, [&squares](int n) {
		for (int i = 1; i < n; ++i) {
			if (i * i == n)
				squares.push_back(n);
		}
	});

	std::cout << "Total squares found: " << squares.size() << std::endl;
}

//---- COUNT_ODD_ELEMENTS

void count_odd_elements() {
	
	using namespace Concurrency;

	std::vector<int> elements(1000000,0);
	int n = 1;
	std::generate(elements.begin(), elements.end(), [&n]() { return ++n; });

	combinable<int> count([]() { return 0; });
	parallel_for_each(elements.begin(), elements.end(), [&count](int n) {
		count.local() += (n % 2 == 0) ? 0 : 1;
	});
	std::cout << "Total odd elements: " << count.combine(std::plus<int>()) << std::endl;
}

//---- TREE_TRAVERSAL ----

template <typename T>
struct tree_node {
	T data;
	tree_node *left, *right;
	tree_node(T dt) : data(dt), left(0), right(0) {}
	tree_node(T dt, tree_node* l, tree_node* r) : data(dt), left(l), right(r) {}
};

template <typename T, typename Fn>
tree_node<T>* build_tree(int depth, Fn generator) {
	if (depth == 0)
		return new tree_node<T>(generator());
	
	tree_node<T>* me = new tree_node<T>(generator());
	me->left = build_tree<T,Fn>(depth-1, generator);
	me->right = build_tree<T,Fn>(depth-1, generator);
	return me;
}

template <typename T, typename Pred, typename Out>
void match_tree_serial(tree_node<T>* root, Pred pred, Out out) {
	if (root == NULL)
		return;
	if (pred(root->data)) {
		*out = root->data;
		++out;
	}
	match_tree_serial(root->left, pred, out);
	match_tree_serial(root->right, pred, out);
}

template <typename T, typename Pred, typename Out>
void match_tree_parallel(tree_node<T>* root, Pred pred, Out out) {
	
	//TODO: As an optimization, stop creating tasks at a certain
	//		depth, where parallelization of work no longer yields
	//		any effect and the overhead comes into play.
	
	using namespace Concurrency;
	
	if (root == NULL)
		return;
	
	structured_task_group tg;
	auto left = make_task([&]() {
		match_tree_parallel(root->left, pred, out);
	});
	auto right = make_task([&]() {
		match_tree_parallel(root->right, pred, out);
	});
	tg.run(left);
	tg.run(right);
	if (pred(root->data)) {
		*out = root->data;//Assumes that the output iterator is thread-safe
		++out;
	}
	tg.wait();
}

void tree_traversal() {
	int n = 0;
	tree_node<int>* tree = build_tree<int>(24, [&n] {return n++;});
	auto predicate = [](int n) {return log(exp((float)n))<sqrt(exp(cos((float)n)));};
	std::cout << "serial: " << 
		time_call([&] {
			match_tree_serial(tree, predicate, std::ostream_iterator<int>(std::cout, "\n"));
		}) << std::endl;
	std::cout << "parallel: " <<
		time_call([&] {
			match_tree_parallel(tree, predicate, std::ostream_iterator<int>(std::cout, "\n"));
		}) << std::endl;
}

//---- MAIN ----

//For more information about ConcRT, see http://msdn.microsoft.com/en-us/library/dd504870.aspx.
//See also http://code.msdn.microsoft.com/concrtextras for more ConcRT examples.
int wmain(int argc, wchar_t* argv[])
{
	//producer_consumer();
	//measure_sort();
	//filter_squares();
	//count_odd_elements();
	//tree_traversal();

	return 0;
}