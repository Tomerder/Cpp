#pragma once

#include <ppl.h>
#include <ppltasks.h>
#include <concurrent_queue.h>

#include <string>
#include <iostream>

#include "text_file.h"

const int END_WORK = -42;


void producer_consumer() 
{
	concurrency::concurrent_queue<int> work;
	concurrency::structured_task_group group;
	auto producer = concurrency::make_task([&work] 
	{
		for (int i = 0; i < 10000; ++i) 
		{
			work.push(i);
			if (i % 47 == 0)
				concurrency::wait(10); //same as sleep
		}
		work.push(END_WORK);
		std::cout << GetCurrentThreadId() << "-Producer done." << std::endl;
	});

	auto consumer = concurrency::make_task([&work] 
	{
		int n;
		do 
		{
			bool result = work.try_pop(n);
			if (!result)
				concurrency::wait(10);
		} while (n != END_WORK);
		std::cout << GetCurrentThreadId() << "-Consumer done, last value was: " << n << std::endl;
	});

	group.run(producer); 	group.run(consumer);

	group.wait();
}


// taken from wikipedia
void parallel_quicksort_tasks(int arr[], int left, int right)
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


	/* recursion */
	concurrency::task<void> left_sort([=] {parallel_quicksort_tasks(arr, left, j); });
	concurrency::task<void> right_sort([=] {parallel_quicksort_tasks(arr, i, right); });

	left_sort.wait(); right_sort.wait();


}

// supprt exepction like future
void get_from_task()
{

	concurrency::task<int> the_task([] 
	{
		throw std::exception("somthing went wrong");
		return 42; 
	});

	try
	{
		int result = the_task.get();
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

}



void task_continue()
{

	concurrency::task<int> the_task([]
	{
		//throw std::exception("somthing went wrong");
		return 42;
	});

	// same type as the task return
	// callback will be executed on the same thread
	the_task.then([](int result) 
	{
		std::cout << result << std::endl;
	});

	getchar();

}


void task_continue_exception()
{

	concurrency::task<int> the_task([]
	{
		throw std::exception("somthing went wrong");
		return 42;
	});

	// happy flow
	// will be called only if no exception
	the_task.then([](int result) 
	{
		std::cout << result << std::endl;
	});

	// exception flow
	// will be called always
	the_task.then([](concurrency::task<int> task) 
	{
		try
		{
			task.wait();
		}
		catch (std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	});


	// as many callbacks as I want!

	getchar();

}


namespace files_async
{

	concurrency::task<HANDLE> open_file_async(std::string const& filename)
	{
		return concurrency::task<HANDLE>([=] {
			return CreateFileA(filename.c_str(), GENERIC_READ | GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, 0, nullptr);
		});
	}

	concurrency::task<int> write_file_async(HANDLE hFile, std::string const& text)
	{
		return concurrency::task<int>([=] {
			DWORD written;
			WriteFile(hFile, text.c_str(), (DWORD)text.size(), &written, nullptr);
			return static_cast<int>(written);
		});
	}


	concurrency::task<void> close_file_async(HANDLE hFile)
	{
		return concurrency::task<void>([=] {
			CloseHandle(hFile);
		});
	}

	void open_files_async_test()
	{
		auto t1 = open_file_async("hello.txt");
		t1.then([](HANDLE hFile)
		{
			auto t2 = write_file_async(hFile, "Hello World");
			t2.then([hFile](int written)
			{
				std::cout << "wrote " << written << " bytes" << std::endl;
				auto t3 = close_file_async(hFile);
				t3.then([]
				{
					std::cout << "done" << std::endl;
				});
			});

		});
	}

	void open_files_async_test_chained()
	{
		//open_file_async("hello.txt")
		//.then([](HANDLE hFile)
		//{
		//	return write_file_async(hFile, "Hello World");
		//})
		//.then([hFile](int written)
		//{
		//	std::cout << "wrote " << written << " bytes" << std::endl;
		//	return close_file_async(hFile);

		//})
		//.then([]
		//{
		//	std::cout << "done" << std::endl;
		//});
	}


	void when_any_when_all_sample()
	{

		// lets say openning a file from network drive, takes long time
		std::vector<concurrency::task<HANDLE>> tasks
		{ 
			open_file_async("file1.txt"), 
			open_file_async("file2.txt"),
			open_file_async("file3.txt"),
			open_file_async("file4.txt"),
		};


		// when any
		while (true)
		{
			// size_t is the index. 
			// auto can help here
			concurrency::task<std::pair<HANDLE, size_t>> w =
				concurrency::when_any(tasks.begin(), tasks.end());

			std::pair<HANDLE, size_t> pair = w.get();
			
			// TODO - handle the result - print, scan for viruses , etc

			//  remove tha file that has been take care
			tasks.erase(tasks.begin() + pair.second);
		}

		
		//when all
		concurrency::task<std::vector<HANDLE>> w2 =  concurrency::when_all(tasks.begin(), tasks.end());
		w2.then([](std::vector<HANDLE> const& results)
		{
			// do some file work 
		});
	}
}






void test_files()
{
	auto f1 = std::make_shared<text_file>(L"test.txt", filemode::readwrite, fileshare::none, filedisposition::create);

	f1->write_async("Hello, World!\n", 0)
	.then([](concurrency::task<DWORD> const& t) 
	{
		try
		{
			auto written = t.get();
			std::cout << "wrote " << written << " bytes to file\n";
		}
		catch (std::exception& ex)
		{
			std::cout << ex.what() << "\n";
		}
	})
	.then([=] 
	{
		return f1->read_async(20, 0);
	})
	.then([](std::string const& result)
	{
		std::cout << "read from file: " << result << "\n";
	});
	getchar();
}




template <typename TaskIter, typename Callback>
struct when_any_helper
{
	TaskIter begin_;
	TaskIter end_;
	Callback callback_;

	using task_result_t = std::decay_t<decltype(std::declval<TaskIter>()->get())>;
	using pair_result_t = concurrency::task<std::pair<task_result_t, size_t>>;

	when_any_helper(TaskIter begin, TaskIter end, Callback callback)
		: begin_(begin), end_(end), callback_(std::move(callback))
	{
		if (std::distance(begin, end) > 0)
		{
			concurrency::when_any(begin, end).then([this](pair_result_t const& r) { continuation(r); });
		}
		else
		{
			delete this;
		}
	}
	void continuation(pair_result_t const& t)
	{
		decltype(t.get()) result;
		try
		{
			result = t.get();
			callback_(result);
		}
		catch (std::exception&)
		{
			// FIXME: Decide which exception-handling strategy is most appropriate for you.
			return;
		}

		--end_;
		if (std::distance(begin_, end_) > 0)
		{
			std::swap(*(begin_ + result.second), *end_);
			concurrency::when_any(begin_, end_).then([this](pair_result_t const& r) { continuation(r); });
		}
		else
		{
			delete this;
		}
	}
};

template <typename TaskIter, typename Callback>
void when_any_repeat(TaskIter begin, TaskIter end, Callback&& callback)
{
	// The helper object cleans itself up when done. It has to be a heap allocation because
	// when_any_repeat returns before the callbacks are completed.
	new when_any_helper<TaskIter, Callback>(begin, end, std::forward<Callback>(callback));
}

void test_when_any()
{
	std::vector<text_file> files;
	files.emplace_back(L"test1.txt", filemode::readwrite, fileshare::none, filedisposition::create);
	files.emplace_back(L"test2.txt", filemode::readwrite, fileshare::none, filedisposition::create);
	files.emplace_back(L"test3.txt", filemode::readwrite, fileshare::none, filedisposition::create);
	std::vector<concurrency::task<DWORD>> tasks;
	std::transform(files.begin(), files.end(), std::back_inserter(tasks), [](text_file& tf) {
		return tf.write_async("Hi!", 0);
	});
	when_any_repeat(tasks.begin(), tasks.end(), [](std::pair<DWORD, size_t> result) {
		std::cout << "wrote " << result.first << " bytes\n";
	});
	getchar();
}

void test_when_all()
{
	std::vector<text_file> files;
	files.emplace_back(L"test1.txt", filemode::read, fileshare::none, filedisposition::open);
	files.emplace_back(L"test2.txt", filemode::read, fileshare::none, filedisposition::open);
	files.emplace_back(L"test3.txt", filemode::read, fileshare::none, filedisposition::open);
	std::vector<concurrency::task<std::string>> tasks;
	std::transform(files.begin(), files.end(), std::back_inserter(tasks), [](text_file& tf) {
		return tf.read_async(20, 0);
	});
	concurrency::when_all(tasks.begin(), tasks.end()).then([](std::vector<std::string> const& results) {
		for (auto const& result : results)
		{
			std::cout << result << "\n";
		}
	});
	getchar();
}