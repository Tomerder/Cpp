#ifdef __clang__
#define VARIABLE_TEMPLATES_SUPPORTED
#define EXPRESSION_SFINAE_SUPPORTED
#define CONSTEXPR_WORKS_REALLY_WELL
#endif

#include "specialization.h"
#include "traits.h"
#include "is_container.h"
#include "has_push_back.h"
#include "concept.h"
#include "variadics.h"
#include "tuple_tests.h"
#include "tuple_cat.h"

int main()
{
	dimov1::specialization_overloading();
	dimov2::specialization_overloading();
	dimov3::specialization_overloading();
	test_smaller();
	print_traits::test_print();
	tag_dispatch::test_print();
	optimized_copy_test();
	cpp98::test_is_container();
	cpp11::test_is_container();
	voidt::test_print();
	outputtable_trait::test_is_outputtable();
	withdecltype::test_has_push_back();
	withconstexpr::test_has_push_back();
	test_full_container();
	make_unique::test_create_unique();
	make_unique::test_create_unique_smarter();
	adder::test_adder();
	count::test_count();
	print::test_simple_print();
	varmax::test_varmax();
	safeprintf::test_printf();
	run_all_tuple_tests();
	tuple_cat_perf();


	return 0;
}