#include "nullptr.h"
#include "nsdmi.h"
#include "ctors.h"
#include "defaultdelete.h"
#include "overridefinal.h"
#include "auto.h"
#include "decltype.h"
#include "rangefor.h"
#include "initialization.h"
#include "literals.h"
#include "constexpr.h"
#include "lambdas.h"
#include "lambdas_interop.h"

int main()
{
	//using_nullptr();
	//use_stack(); // nsdmi
	//print_something(); //default delete
	//apply_examples(); //decltype
	//use_get_at();
	//use_reduce();
	//use_stack_range_for(); //range for
	simple_initialization();
	use_initializer_list();
	using_constexpr();
	stateless_lambdas();
	stateful_lambdas();


	return 0;
}