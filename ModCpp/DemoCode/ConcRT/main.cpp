#include "groups.h"
#include "tasks.h"
#include "cancellation.h"
#include "datapar.h"
#include "await.h"

int main()
{
	//test_sort();


	//producer_consumer();
	//get_from_task();

	//test_files();
	//test_when_any();
	//test_when_all();
	//groups::test_timeout();
	//tasks::simple_cancelation_token();
	tasks::test_timeout();
	//primes_count();
	//primes_sum();
	//primes_combinable();
	
	// FIXME: Currently there seems to be some bad codegen with resumable functions,
	// so this should be tested again when VC++ 2015 reaches RTM or a more stable state.
	// test_await();

	return 0;
}