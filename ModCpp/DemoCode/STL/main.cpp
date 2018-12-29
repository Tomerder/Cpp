#include "intel_memory_ordering.h"
#include "atomics.h"
#include "promise_future.h"
#include "threads.h"
#include "synchronization.h"
#include "generic_raii.h"
#include "smart_pointers.h"
#include "pimpl.h"
#include "misc.h"

int main()
{
	reordering_experiment();

	//no_atomics();
	//basic_atomics();
	//test_lock_free_stack();

	//promise_future();
	//async_call::test_async_call();
	//async_call_exception_support::test_async_call();

	//primes_with_threads();
	//primes_with_async();

	//test_bounded_queue();

	//use_raii();
	//unique_ptr_simple::test_unique_ptr();
	//simple_shared_ptr::test_shared_ptr();
	//ref_count_problem::test_ref_count();
	//weak_ptr_solution::weak_explained();
	//use_buffered_log();

	hashers();
	//regexes();

	return 0;
}