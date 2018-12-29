#pragma once

#include <deque>
#include <atomic>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <random>
#include <string>
#include <iostream>


namespace simple_mutex
{
	void try_mutex()
	{
		std::mutex mutex; // non copy, non move, use wrappers

		mutex.lock();

		// do some work in your critical section

		mutex.unlock();
	}


	void try_lock_guard()
	{
		std::mutex mutex;
		{
			std::lock_guard<std::mutex> lock_guard(mutex); // will lock on creation, and will release on destruction
			// this is the critical setion
		}

	}

	void try_unique_lock()
	{
		std::timed_mutex timed_mutex;

		std::unique_lock<std::timed_mutex> unique_lock(timed_mutex);  // movable
		if (unique_lock.try_lock_for(std::chrono::milliseconds(200)))
		{
			// this is the critical setion

			unique_lock.unlock();
		}

	}


}

namespace recursive_mutex
{
	struct Complex_problem 
	{
		std::mutex mutex;
		int i;

		Complex_problem() : i(0) {}

		void mul(int x) 
		{
			std::lock_guard<std::mutex> lock(mutex);
			i *= x;
		}

		void div(int x) 
		{
			std::lock_guard<std::mutex> lock(mutex);
			i /= x;
		}

		void both(int x, int y) 
		{
			std::lock_guard<std::mutex> lock(mutex);
			mul(x);
			div(y);
		}
	};


	struct Complex_recursive_mutex 
	{
		std::recursive_mutex mutex;
		int i;

		Complex_recursive_mutex() : i(0) {}

		void mul(int x)
		{
			std::lock_guard<std::recursive_mutex> lock(mutex);
			i *= x;
		}

		void div(int x) 
		{
			std::lock_guard<std::recursive_mutex> lock(mutex);
			i /= x;
		}

		void both(int x, int y) 
		{
			std::lock_guard<std::recursive_mutex> lock(mutex);
			mul(x);
			div(y);
		}
	};

	// program will run forever, waiting for lock to get free
	void test_compex_problem() 
	{
		Complex_problem complex;
		complex.both(32, 23);
	}

	// this will work as it should
	void test_recursive_compex()
	{
		Complex_recursive_mutex complex;
		complex.both(32, 23);
	}

}

namespace condition_example
{

	void producer_consumer_problem()
	{

		std::deque<std::string> work;
		std::mutex lock;

		std::thread producer([&]()
		{
			for (int i = 0; i < 100; i++)
			{
				std::lock_guard<std::mutex> lg(lock);
				work.push_back(std::string("work") + std::to_string(i));
			}

		});

		std::thread consumer([&]()
		{
			for (int i = 0; i < 100; i++)
			{
				std::lock_guard<std::mutex> lg(lock); // problem is that the vector can be empty at this point
				std::cout << work.front() << std::endl;
				work.pop_front();
			}

		});

		producer.join(); consumer.join();

	}


	void condition_var()
	{

		std::deque<std::string> work;
		std::mutex lock;
		std::condition_variable condtion_not_empty;

		std::thread producer([&]()
		{
			for (int i = 0; i < 100; i++)
			{
				// why its better to have this block?
				{
					std::lock_guard<std::mutex> lg(lock);
					work.push_back(std::string("work") + std::to_string(i));
				}

				condtion_not_empty.notify_one();
			}

		});

		std::thread consumer([&]()
		{
			int count = 0;
			while(count < 100)
			{
				std::unique_lock<std::mutex> ul(lock); 
				// when we get notify, we lock, check the condition, if the condtion is not happen, release the lock and wait for notify.  release the lock while waiting
				// a. do we really need this condtion? not in this case , cause we have only one thread. 
				// we know that we will have somthing in the dequeu when we get notify. but what if we have more threads?
				// we could have use wait only version -> condtion_not_empty.wait(ul);
				condtion_not_empty.wait(ul, [&] { return !work.empty(); }); 
				while (!work.empty())
				{
					std::cout << work.front() << std::endl;
					work.pop_front();
					count++;
				}
			}

		});

		producer.join(); consumer.join();
	}


	void test_condtion_var()
	{
		condition_var();
	}

}


template <typename T>
class bounded_queue
{
private:
	std::atomic<size_t> size_{ 0 };
	size_t capacity_;
	std::deque<T> queue_;
	std::mutex lock_;
	std::condition_variable not_full_;
	std::condition_variable not_empty_;

public:
	bounded_queue(size_t capacity) : capacity_{ capacity }
	{
	}

	void enqueue(T const& data)
	{
		{
		std::unique_lock<std::mutex> lock{ lock_ };
		while (queue_.size() >= capacity_)
		{
			not_full_.wait(lock);
		}
		queue_.push_back(data);
		++size_;
		} // unlock
		
		not_empty_.notify_all();
	}

	T dequeue()
	{
		T result;
		size_t new_size;
		{
			std::unique_lock<std::mutex> lock{ lock_ };
			while (queue_.size() == 0)
			{
				not_empty_.wait(lock);
			}
			result = queue_.front();
			queue_.pop_front();
			new_size = --size_;
		} // unlock

		not_full_.notify_all();
		return result;
	}

	size_t size() const
	{
		return size_;
	}
};

void test_bounded_queue()
{
	bounded_queue<int> queue{ 10 };
	std::mt19937 random;
	std::thread producer([&] {
		for (int i = 0; i < 1000; ++i)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(random() % 10));
			queue.enqueue(i);
		}
	});
	std::thread consumer([&] {
		for (int i = 0; i < 1000; ++i)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(random() % 10));
			queue.dequeue();
		}
	});
	producer.join();
	consumer.join();
	std::cout << "done with queue, size = " << queue.size() << "\n";
}