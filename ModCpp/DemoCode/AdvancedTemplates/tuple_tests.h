#pragma once

#include "tuple.h"

#include <string>
#include <iostream>
#include <set>

namespace tests
{

    using namespace library;

    tuple<int, int> get_values()
    {
        return make_tuple(1, 2);
    }

    struct printer
    {
        static int moves;
        static int copies;

        printer()
        {
        }

        printer(printer&&)
        {
            ++moves;
        }

        printer(printer const&)
        {
            ++copies;
        }

        printer& operator=(printer const&)
        {
            ++copies;
            return *this;
        }

        printer& operator=(printer&&)
        {
            ++moves;
            return *this;
        }
    };

    int printer::moves = 0;
    int printer::copies = 0;

    void assert_true(bool condition, std::string const& message)
    {
        if (!condition)
        {
            std::cerr << "assertion failed: " << message << "\n";
        }
    }

    void test_from_pair()
    {
        std::set<int> ints;
        ints.insert(4);

        bool inserted;
        tie(ignore, inserted) = ints.insert(4);

        assert_true(!inserted, "inserted duplicate");
    }

    void test_less_than()
    {
        auto smalltup = make_tuple(1, 34ull);
        auto bigtup = make_tuple(1, 420);

        assert_true(smalltup < bigtup, "operator< failed");
    }

    void test_movable()
    {
        {
            auto printabletup = make_tuple(printer{});
            auto printabletup2 = printabletup;
            auto printabletup3 = std::move(printabletup2);
        }

        assert_true(printer::copies == 1, "made more than one copy");
        assert_true(printer::moves == 2, "made more than two moves");
    }

    void test_equality()
    {
        auto tcmp1 = make_tuple(1, 4u);
        auto tcmp2 = make_tuple(1u, 4ull);

        assert_true(tcmp1 == tcmp2, "equality failed");
    }

    void test_tie()
    {
        int r1, r2;
        tie(r1, r2) = get_values();
        assert_true(r1 == 1 && r2 == 2, "tie failed");

        int r3;
        tie(ignore, r3) = get_values();
        assert_true(r3 == 2, "tie failed");
    }

    void test_construction()
    {
        tuple<long long, long long> tll{get_values()};
        assert_true(get<0>(tll) == 1ll && get<1>(tll) == 2ll, "construction failed");

        tuple<int> const tc(17);
        assert_true(get<0>(tc) == 17, "get on const failed");
    }

    void test_get()
    {
		tuple<int, int, int> t1;
        tuple<int> t2;
		// Just make sure it can be instantiated; the make_unique is there
		// to avoid an unreferenced local variable warning.
		std::make_unique<tuple<>>();

        get<0>(t1) = 42;
        assert_true(get<0>(t1) == 42, "set through get<> failed");

        tuple<int, double, std::string> t4;
        get<2>(t4) = "hello, world";
        assert_true(get<2>(t4) == "hello, world", "set through get<> failed");

        tuple<int> t5(42);
        assert_true(get<0>(t5) == 42, "construction from rvalue failed");

        int x = 42;
        tuple<int&> t6(x);
        x = 56;
        assert_true(get<0>(t6) == 56, "tuple doesn't maintain lvalue reference");
    }

    void test_make_tuple()
    {
        int x = 56;
        auto t = make_tuple(x, "hello");
        x = 42;
        assert_true(get<0>(t) == 56, "make_tuple maintained reference incorrectly");

        // Note: explicit library:: qualification required because ADL makes the
        // call ambiguous since std::make_tuple is in std::ref's namespace.
        auto t2 = library::make_tuple(std::ref(x));
        x = 56;
        assert_true(get<0>(t) == 56, "make_tuple ignored std::ref parameter");
    }

    void test_move_only()
    {
        struct move_only
        {
            move_only(move_only&&) = default;

            move_only(move_only const&) = delete;
        };

        auto t = make_tuple(move_only{});
        auto& mo = get<0>(t);
        // If this compiles OK, we're good
    }

    void test_swap()
    {
        auto t1 = library::make_tuple(42, std::string{"hello"});
        auto t2 = library::make_tuple(17, std::string{"goodbye"});
        t1.swap(t2);
        assert_true(get<0>(t1) == 17, "swap failed");
        assert_true(get<0>(t2) == 42, "swap failed");
        assert_true(get<1>(t1) == "goodbye", "swap failed");
        assert_true(get<1>(t2) == "hello", "swap failed");
    }

    void test_forward()
    {
        int x = 42;
        auto t1 = forward_as_tuple(x);
        x = 56;
        assert_true(get<0>(t1) == 56, "forward failed to preserve lvalue reference");
    }

    void test_get_by_type()
    {
        auto t = make_tuple(42, 5.0, 'a');
        assert_true(get<int>(t) == 42, "get<int> failed");
        assert_true(get<double>(t) == 5.0, "get<double> failed");
        assert_true(get<char>(t) == 'a', "get<char> failed");
    }

	void test_assignment()
	{
		tuple<int> tint1;
		tuple<int> tint2(tint1);
		tint2 = tint1;

		tuple<short> tint3;
		tint2 = tint3;

		tuple<std::string, int> tstrint("hello", 123u);
		tstrint = make_tuple("goodbye", -14);
	}

    void test_compile_time_truths()
    {
        static_assert(tuple_size<tuple<int, int>>::value == 2, "");
        static_assert(tuple_size<tuple<int>>::value == 1, "");
        static_assert(tuple_size<tuple<>>::value == 0, "");

        static_assert(std::is_same<typename type_of_element<0, tuple<int, float>>::type, int>::value, "");
        static_assert(std::is_same<typename type_of_element<1, tuple<int, float>>::type, float>::value, "");

        static_assert(std::is_same<int, typename type_at_index<0, int>::type>::value, "");
        static_assert(std::is_same<int, typename type_at_index<0, int, float>::type>::value, "");
        static_assert(std::is_same<float, typename type_at_index<1, int, float>::type>::value, "");
        static_assert(std::is_same<float, typename type_at_index<1, int, float, double>::type>::value, "");

        static_assert(index_sequence<>::length == 0, "");
        static_assert(index_sequence<0>::length == 1, "");
        static_assert(index_sequence<0, 1>::length == 2, "");

        static_assert(std::is_same<index_sequence<0>, make_index_sequence<1>::type>::value, "");
        static_assert(std::is_same<index_sequence<0, 1>, make_index_sequence<2>::type>::value, "");
        static_assert(std::is_same<index_sequence<0, 1, 2>, make_index_sequence<3>::type>::value, "");
        static_assert(std::is_same<index_sequence<0, 1, 2, 3>, make_index_sequence<4>::type>::value, "");

        static_assert(make_index_sequence_for_types<int>::length == 1, "");
        static_assert(make_index_sequence_for_types<int, int>::length == 2, "");
        static_assert(make_index_sequence_for_types<int, int, int>::length == 3, "");
        static_assert(std::is_same<make_index_sequence_for_types<int, int, int>, index_sequence<0, 1, 2>>::value, "");

        static_assert(find_exactly_one<int, float, int, std::string>() == 1, "");
        static_assert(find_exactly_one<float, float, int, std::string>() == 0, "");
        // static_assert(find_exactly_one<int, int, int, std::string>() == 0, ""); // doesn't compile
        // static_assert(find_exactly_one<int, float, std::string>() == -1, ""); // doesn't compile
    }

	template <typename T, size_t... Indices>
	auto array_to_tuple_helper(T* arr, index_sequence<Indices...>)
	{
		return make_tuple(arr[Indices]...);
	}

	template <typename T, size_t N>
	auto array_to_tuple(T(&arr)[N])
	{
		return array_to_tuple_helper(arr, make_index_sequence<N>{});
	}

	void test_array_to_tuple()
	{
		int arr[] = { 4, 18, -12 };
		auto tup = array_to_tuple(arr);
		static_assert(std::is_same<decltype(tup), tuple<int, int, int>>::value, "");
		std::cout << get<2>(tup) << "\n";
	}

}

void run_all_tuple_tests()
{
	using namespace tests;

	test_from_pair();
	test_less_than();
	test_movable();
	test_equality();
	test_tie();
	test_construction();
	test_get();
	test_make_tuple();
	test_move_only();
	test_swap();
	test_forward();
	test_get_by_type();
	test_assignment();
	test_compile_time_truths();
	test_array_to_tuple();
}
