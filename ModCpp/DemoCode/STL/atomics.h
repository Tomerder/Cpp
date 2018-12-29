#pragma once

#include <atomic>
#include <array>
#include <thread>
#include <iostream>

void no_atomics()
{
	constexpr size_t COUNT = 10000000;
	constexpr size_t THREADS = 4;

	size_t counter{ 0 }; // NOT THREAD-SAFE!
	auto incrementer = [&] {
		for (size_t i = 0; i < COUNT; ++i)
		{
			++counter;
		}
	};

	std::array<std::thread, THREADS> threads;
	std::generate_n(threads.begin(), threads.size(), [&] {return std::thread{ incrementer }; });
	std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
	std::cout << "counter = " << counter << "\n";
}

void basic_atomics()
{
	constexpr size_t COUNT = 10000000;
	constexpr size_t THREADS = 4;

	std::atomic<size_t> counter{ 0 };
	auto incrementer = [&] {
		for (size_t i = 0; i < COUNT; ++i)
		{
			++counter;
		}
	};

	std::array<std::thread, THREADS> threads;
	std::generate_n(threads.begin(), threads.size(), [&] {return std::thread{ incrementer }; });
	std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
	std::cout << "counter = " << counter << "\n";
}

// Thread-safe version of a *= b, returning result and modifying a
size_t atomic_multiply(std::atomic<size_t>& a, size_t b)
{
	size_t old_a = a.load();
	size_t result;
	do
	{
		result = old_a * b;
	} while (!a.compare_exchange_weak(old_a, result));
	return result;
}


class nonblocking_counter 
{
	std::atomic<unsigned> count;
public:
	nonblocking_counter() : count(0) {}
	// Increment the count
	unsigned increment() 
	{
		unsigned old_count;
		bool success;
		do 
		{
			// Get old value and calculate new value for counter
			old_count = count.load();
			unsigned new_count = old_count + 1;
			// Atomically increment the counter.
			success = count.compare_exchange_weak(old_count, new_count);
			// Someone else changed the counter first -- start over.
		} while (!success);
		return old_count;
	}
	// Get the current count
	unsigned get() 
	{
		return count.load();
	}
};

template <typename T>
class lock_free_stack
{
private:
	struct node
	{
		node* next_;
		T data_;

		node(node* next, T const& data) : next_{ next }, data_{ data }
		{
		}
	};
	std::atomic<node*> head_{ nullptr };

public:
	size_t size() const
	{
		auto head = head_.load();
		size_t count = 0;
		while (head != nullptr)
		{
			++count;
			head = head->next_;
		}
		return count;
	}
	void push(T const& data)
	{
		// put the current value of head into new_node
		auto new_node = new node{ head_.load(), data };

		// now make new_node the new head, but if the head
		// is no longer what's stored in new_node->next
		// (some other thread must have inserted a node just now)
		// then put that new head into new_node->next and try again
		while (!head_.compare_exchange_weak(new_node->next_, new_node))
		{
		}
	}
	bool pop(T& data)
	{
		auto head = head_.load();
		node* new_head;

		do
		{
			if (head == nullptr)
			{
				return false;
			}
			try
			{
				new_head = head->next_;
			}
			catch (...)
			{
				// If we see an error here, it means the head node was
				// destroyed by some other thread while we were at it.
				// This is OK -- it just means we need to spin through
				// another iteration. The CAS will fail and we will
				// get an updated new_head. Note that this doesn't solve
				// the ABA problem in and of itself.
			}
		} while (!head_.compare_exchange_weak(head, new_head));
		
		data = head->data_;

		// If we delete the node here, we become subject to the ABA problem.
		// Therefore, for expository purposes, this line is commented out.
		/* delete head; */
		
		return true;
	}
	~lock_free_stack()
	{
		auto head = head_.load();
		while (head != nullptr)
		{
			auto temp = head;
			head = head->next_;
			delete temp;
		}
		head_ = nullptr;
	}
};

void test_lock_free_stack()
{	
	constexpr size_t THREADS = 4;
	constexpr size_t OPERATIONS = 100000;

	lock_free_stack<int> ls;
	auto worker = [&] {
		for (size_t i = 0; i < OPERATIONS; ++i)
		{
			ls.push(42);
			ls.push(37);
			
			int x;
			ls.pop(x);
			ls.pop(x);
		}
	};

	std::array<std::thread, THREADS> threads;
	std::generate_n(threads.begin(), threads.size(), [&] {return std::thread{ worker }; });
	std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
	
	std::cout << "stack size at end = " << ls.size() << "\n";
}