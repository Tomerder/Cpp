#pragma once

#include "tuple.h"

#include <chrono>
#include <vector>
#include <complex>

namespace library
{
	// Simple recursive implementation of tuple_cat. The recursive version concats the first
	// two tuples and then calls "itself" recursively.
	namespace direct
	{
		template <size_t... Ix1, typename LeftTuple, size_t... Ix2, typename RightTuple>
		auto concat_two(LeftTuple&& left, RightTuple&& right, index_sequence<Ix1...>, index_sequence<Ix2...>)
		{
			return library::make_tuple(
				library::get<Ix1>(std::forward<LeftTuple>(left))...,
				library::get<Ix2>(std::forward<RightTuple>(right))...
				);
		}

		template <typename HeadTuple>
		HeadTuple&& tuple_cat(HeadTuple&& head)
		{
			return std::forward<HeadTuple>(head);
		}

		template <typename Head1Tuple, typename Head2Tuple, typename... TailTuples>
		auto tuple_cat(Head1Tuple&& head1, Head2Tuple&& head2, TailTuples&&... tail)
		{
			return tuple_cat(
				concat_two(
					std::forward<Head1Tuple>(head1),
					std::forward<Head2Tuple>(head2),
					make_index_sequence<tuple_size<typename std::decay<Head1Tuple>::type>::value>{},
					make_index_sequence<tuple_size<typename std::decay<Head2Tuple>::type>::value>{}
				),
				std::forward<TailTuples>(tail)...
			);
		}
	}

	namespace twodimensional
	{
		template <typename Tuples, size_t... Ix, size_t... Jx>
		auto cat2d_all(Tuples&& tuples, index_sequence<Ix...>, index_sequence<Jx...>)
		{
			// 'tuples' is a tuple of tuples, and the index sequences help index into that
			// tuple of tuples two-dimensionally.
			// If originally provided with n tuples with E(k) elements each, then Ix and Jx
			// are two index sequences (of the same length) with the following structure:
			// Ix = 0, 0, ..., 0     , 1, 1, ...,  1     , ......, n-1, n-1, ..., n-1 
			// Jx = 0, 1, ..., E(1)-1, 0, 1, ...,  E(2)-1, ......, 0  , 1  , ..., E(n-1)-1
			return library::make_tuple(
				library::get<Jx>(library::get<Ix>(std::forward<Tuples>(tuples)))...
				);
		}

		// Concatenates any number of index sequences into a single index sequence
		template <typename... Sequences>
		struct cat_index_sequence;

		template <size_t... Indices>
		struct cat_index_sequence<index_sequence<Indices...>> : index_sequence<Indices...>
		{
		};

		template <size_t... Indices1, size_t... Indices2>
		struct cat_index_sequence<index_sequence<Indices1...>, index_sequence<Indices2...>>
			: index_sequence<Indices1..., Indices2...>
		{
		};

		template <size_t... Indices1, size_t... Indices2, typename... Sequences>
		struct cat_index_sequence<index_sequence<Indices1...>, index_sequence<Indices2...>, Sequences...>
			: cat_index_sequence<index_sequence<Indices1..., Indices2...>, cat_index_sequence<Sequences...>>
		{
		};

		// Make a sequence (I, ..., I) of size Length
		template <size_t I, size_t Length>
		struct make_repeated_sequence : cat_index_sequence<index_sequence<I>, typename make_repeated_sequence<I, Length - 1>::type>
		{
		};

		template <size_t I>
		struct make_repeated_sequence<I, 1> : index_sequence<I>
		{
		};

		// Generates an index sequence that, for each i from 0 to sizeof...(Lengths)-1, k(i) in Lengths...,
		// is a sequence of i repeated k(i) times
		template <typename, size_t... Lengths>
		struct repeating_index_sequence;

		template <size_t I, size_t Length>
		struct repeating_index_sequence<std::integral_constant<size_t, I>, Length>
			: make_repeated_sequence<I, Length>
		{
		};

		template <size_t I, size_t Length, size_t... TailLengths>
		struct repeating_index_sequence<std::integral_constant<size_t, I>, Length, TailLengths...>
			: cat_index_sequence<typename make_repeated_sequence<I, Length>::type
							   , typename repeating_index_sequence<std::integral_constant<size_t, I + 1>, TailLengths...>::type>
		{
		};

		// Generates an index sequence that concatenates make_index_sequence<k> for each k in Lengths...
		template <size_t... Lengths>
		struct variable_index_sequence;

		template <size_t Head>
		struct variable_index_sequence<Head> : make_index_sequence<Head>
		{
		};

		template <size_t Head, size_t... Tail>
		struct variable_index_sequence<Head, Tail...>
			: cat_index_sequence<typename variable_index_sequence<Head>::type, typename variable_index_sequence<Tail...>::type>
		{
		};

		template <typename... Tuples>
		auto tuple_cat(Tuples&&... tuples)
		{
			auto ixs = repeating_index_sequence<std::integral_constant<size_t, 0>, tuple_size<typename std::decay<Tuples>::type>::value...>{};
			auto jxs = variable_index_sequence<tuple_size<typename std::decay<Tuples>::type>::value...>{};
			return cat2d_all(library::forward_as_tuple(std::forward<Tuples>(tuples)...), ixs, jxs);
		}
	}
}

namespace tests
{
	using namespace library::twodimensional;

	void compile_time_truths()
	{
		static_assert(std::is_same<
			  index_sequence<0, 1, 0, 1, 2>
			, cat_index_sequence<make_index_sequence<2>::type, make_index_sequence<3>::type>::type
		>::value, "");

		static_assert(std::is_same<
			  index_sequence<0, 1, 0, 1, 2>
			, variable_index_sequence<2, 3>::type
		>::value, "");

		static_assert(std::is_same<
			  index_sequence<0, 0, 0, 0>
			, make_repeated_sequence<0, 4>::type
		>::value, "");

		static_assert(std::is_same<
			  index_sequence<3, 3, 3>
			, make_repeated_sequence<3, 3>::type
		>::value, "");

		static_assert(std::is_same<
			  index_sequence<0, 0, 0, 1, 1, 2, 2, 2, 2>
			, repeating_index_sequence<std::integral_constant<size_t, 0>, 3, 2, 4>::type
		>::value, "");
	}

#ifdef _DEBUG
	constexpr int ITERATIONS = 100000;
#else
	constexpr int ITERATIONS = 10000000;
#endif

	template <typename Catter>
	void measure(std::string const& description, Catter catter)
	{
		{
			std::cout << "simple tuple  ";
			auto tup1 = library::make_tuple(1, 2);
			auto tup2 = library::make_tuple('a', 4.0f);
			auto tup3 = library::make_tuple(3ull, L'c', 17);
			auto tup4 = library::make_tuple(0, 47.0);
			volatile int size = 0;
			auto start = std::chrono::high_resolution_clock::now();
			for (int i = 0; i < ITERATIONS; ++i)
			{
				auto result = catter(tup1, tup2, tup3, tup4);
				size = get<0>(result);
			}
			auto end = std::chrono::high_resolution_clock::now();
			std::cout << "[" << description << "] elapsed " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " us\n";
		}

		{
			std::cout << "complex tuple ";
			auto tup1 = library::make_tuple(17, std::string{ "hello" }, std::complex<double>(14.0, 3.5));
			auto tup2 = library::make_tuple('a', std::vector<int>{1, 2, 3}, 42);
			auto tup3 = library::make_tuple(3ull, L'c', 17);
			volatile int size = 0;
			auto start = std::chrono::high_resolution_clock::now();
			for (int i = 0; i < ITERATIONS; ++i)
			{
				auto result = catter(tup1, tup2, tup3);
				size = get<0>(result);
			}
			auto end = std::chrono::high_resolution_clock::now();
			std::cout << "[" << description << "] elapsed " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " us\n";
		}
	}

}

void tuple_cat_perf()
{
	using namespace tests;

	measure("simple cat  ", [](auto&&... args) { return library::direct::tuple_cat(args...); });
	measure("2d     cat", [](auto&&... args) { return library::twodimensional::tuple_cat(args...); });
	measure("empty loop", [](auto&&... args) { return library::make_tuple(1); });
}
