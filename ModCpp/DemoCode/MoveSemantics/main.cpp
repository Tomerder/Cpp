#include "mystring.h"
#include "moving.h"
#include "generalized_capture.h"
#include "forwarding.h"
#include "more_urefs.h"
#include "parampassing.h"
#include "this_ref_qualifiers.h"

int main()
{
	strings();
	using_toolbar();
	forwarding_lambda();
	calculate_async();
	calculate_async_cpp11();
	make_cpp11();
	forwarding_lambda();
	param_passing();
	using_counter();

	return 0;
}