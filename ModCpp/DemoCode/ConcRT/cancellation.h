#pragma once

#include <ppl.h>
#include <ppltasks.h>

#include <Windows.h>

#include <chrono>

namespace groups
{
	template <typename Function>
	void run_with_timeout(Function fn, unsigned timeout)
	{
		concurrency::task_group group;
		group.run(fn);
		auto status = group.run_and_wait([&] {
			concurrency::wait(timeout);
			group.cancel();
		});
		switch (status)
		{
		case concurrency::task_status::completed:
			std::cout << "task ran to completion\n";
			break;
		case concurrency::task_status::canceled:
			std::cout << "task canceled\n";
			break;
		case concurrency::task_status::not_complete:
			std::cout << "task not complete (shouldn't happen!)\n";
			break;
		}
	}

	void test_timeout()
	{
		run_with_timeout([] {
			for (int i = 0;; ++i)
			{
				Sleep(10); // non-interruptible; if we called any ConcRT API, we would have been interrupted either way
				if (concurrency::is_current_task_group_canceling())
				{
					std::cout << "interrupted after " << i << " iterations\n";
					break;
				}
			}
		}, 500u);
	}
}

namespace tasks
{


	void simple_cancelation_token()
	{
		concurrency::cancellation_token_source cts;
		concurrency::cancellation_token ct = cts.get_token();
		concurrency::task<int> retruningInt([&ct] {

			int counter = 0;
			for (int i = 0; i < 10000; ++i)
			{
				concurrency::wait(200);
				++counter;
				std::cout << "Task is progressing, counter = " << counter << std::endl;
				if (ct.is_canceled()) // asked me to cancel via token
				{
					// will throw an exapceion, we will get it when we will try to call get from the canceled task
					// stack will be unwind, destructors etc
					concurrency::cancel_current_task(); 
				}
			}

			return counter;

		}, ct);

		getchar();
		cts.cancel();
		getchar();

		try {
			retruningInt.get();
		}
		catch (std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}

	}




	template <typename Function>
	void run_with_timeout(Function fn, unsigned timeout)
	{
		concurrency::cancellation_token_source cts;
		concurrency::task<void> t(fn, cts.get_token());
		t.then([] { // completion-based continuation, invoked only if not timed out
			std::cout << "task completed successfully\n";
		});
		concurrency::create_task([=] {
			concurrency::wait(timeout);
			cts.cancel();
		});
	}

	void test_timeout()
	{
		run_with_timeout([] {
			for (int i = 0;; ++i)
			{
				Sleep(10); // non-interruptible; if we called any ConcRT API, we would have been interrupted either way

				// FIXME: VC14 doesn't have is_task_cancellation_requested, and the is_current_task_group_canceling method
				// doesn't catch cancellation of individual tasks. This must be fixed by RTM.
#if (_MSC_VER == 1900)
				if (concurrency::is_current_task_group_canceling())
#else
				if (concurrency::is_task_cancellation_requested())
#endif
				{
					std::cout << "interrupted after " << i << " iterations\n";
					concurrency::cancel_current_task(); // completion-based continuations will not run
					break;
				}
			}
		}, 500u);
		getchar();
	}
}
