#pragma once

#include <Windows.h>
#include <functional>
#include <future>
#include <iostream>
#include <string>


namespace simple_future_promise
{
	void test_promise()
	{
		std::promise<std::string> promise;
		std::thread my_thread([&promise]
		{
			std::this_thread::sleep_for(std::chrono::seconds(3));
			promise.set_value("Result");
		});

		my_thread.detach();

		std::future<std::string> future = promise.get_future();
		std::string thread_result = future.get();
		std::cout << thread_result << std::endl;

	}
}


namespace async_call
{
	template <typename Function>
	auto async_call(Function function) -> std::future<decltype(function())>
	{
		using return_t = decltype(function());

		auto promisePtr = new std::promise<return_t>();
		std::future<return_t> future = promisePtr->get_future();
		std::thread the_thread([promisePtr, function] //  we are not taking reference - be aware - threads and scopes
		{
			auto ret = function(); //what with exception?
			
			promisePtr->set_value(ret);

			delete promisePtr;
		});
		
		the_thread.detach();
		return future;
	}

	std::string my_function()
	{
		std::this_thread::sleep_for(std::chrono::seconds(3));
		return "hello";
	}

	void test_async_call()
	{
		auto future = async_call(my_function);
		std::cout << future.get() << std::endl;
	}
		
}

namespace async_call_exception_support
{
	template <typename Function>
	auto async_call(Function function) -> std::future<decltype(function())>
	{
		using return_t = decltype(function());

		auto promisePtr = new std::promise<return_t>();
		std::future<return_t> future = promisePtr->get_future();
		std::thread the_thread([promisePtr, function] 
		{
			try
			{
				auto ret = function();
				promisePtr->set_value(ret);
			}
			catch(...)
			{
				promisePtr->set_exception(std::current_exception()); // every exeption that was trown, std or not
			}
			
			delete promisePtr;
		});

		the_thread.detach();
		return future;
	}

	std::string my_function()
	{
		std::this_thread::sleep_for(std::chrono::seconds(3));
		throw std::runtime_error("somthing bad happened");

		return "hello";
	}

	void test_async_call()
	{
		try
		{
			auto future = async_call(my_function); //use can also use the build it std::async(my_function);
			std::cout << future.get() << std::endl; // get will rethrow the exception
		}
		catch(std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}

	}

}



template <typename Function>
struct tp_context
{
	using result_t = decltype(std::declval<Function>()());
	
	std::function<result_t()> fn_;
	std::promise<result_t> promise_;

	tp_context(Function fn) : fn_{ fn }
	{
	}
};

template <typename Function, typename = std::enable_if_t<!std::is_void<decltype(std::declval<Function>()())>::value>>
auto do_threadpool(Function fn)
{
	auto context = new tp_context<Function>{ fn };
	QueueUserWorkItem([](PVOID c) {
		auto ctx = reinterpret_cast<tp_context<Function>*>(c);
		try
		{
			ctx->promise_.set_value(ctx->fn_());
		}
		catch (std::exception&)
		{
			ctx->promise_.set_exception(std::current_exception());
		}
		return static_cast<DWORD>(0);
	}, context, 0);
	return context->promise_.get_future();
}

void promise_future()
{
	// This is like std::async, but uses the Win32 thread pool
	auto fut = do_threadpool([] {
		Sleep(1000);
		return 42;
	});
	fut.get();
	auto fut2 = do_threadpool([] {
		throw std::exception("bad!");
		return 42;
	});
	try
	{
		fut2.get();
	}
	catch (std::exception&)
	{
		// Caught it
	}
}