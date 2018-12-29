#pragma once

#include <iostream>
#include <vector>
#include <list>
#include <string>

namespace is_same
{

	template <typename T, typename S> // base template
	struct is_same
	{
		static const bool value = false;  // need to be const so static_assert can take it in complie time
	};

	template <typename T> // specialization
	struct is_same<T, T>
	{
		static const bool value = true;
	};


	void test_is_same()
	{
		static_assert(is_same<int, int>::value, "");
		static_assert(is_same<int, int>::value, "");
		static_assert(!is_same<int, double>::value, "");

		// standard libary trait
		static_assert(!std::is_same<int, double>::value, "");

	}

}
namespace print_traits
{

	template <typename T>
	struct is_pointer
	{
		static const bool value = false; // need to be const so static_assert can take it in complie time
	};

	template <typename T>
	struct is_pointer<T*>
	{
		static const bool value = true;
	};

	template <typename T, bool>
	struct print_helper
	{
		static void print(T const& t)
		{
			std::cout << t << std::endl;
		}
	};

	template <typename T>
	struct print_helper<T, true>
	{
		static void print(T const& t)
		{
			std::cout << *t << std::endl;
		}
	};

#ifdef VARIABLE_TEMPLATE_SUPPORTED
	template <typename T>
	bool is_pointer_v = is_pointer<T>::value;

	template <typename T>
	void print(T const& t)
	{
		using helper_t = print_helper<T, is_pointer_v<T>>;

		helper_t::print(t);
	}
#else
	template <typename T>
	void print(T const& t)
	{
		using helper_t = print_helper<T, is_pointer<T>::value>;

		helper_t::print(t);
	}
#endif


	void test_print()
	{
		int x = 42;
		print(x);
		print(&x);

		static_assert(!is_pointer<int>::value, "");
		static_assert(is_pointer<int*>::value, "");
		static_assert(is_pointer<void*>::value, "");
		static_assert(!is_pointer<void>::value, "");
		static_assert(!is_pointer<int const>::value, "");
		static_assert(!is_pointer<int&>::value, "");
		static_assert(is_pointer<const void*>::value, "");
			
		//static_assert(is_pointer<void* const>::value, "");  // what is the problem? What with volatile?

		
	}
}

// using standard libary traits
namespace tag_dispatch
{
	template <typename T>
	void print_helper(std::false_type, T const& t)
	{
		std::cout << t << std::endl;
	}

	template <typename T>
	void print_helper(std::true_type, T const& t)
	{
		std::cout << *t << std::endl;
	}

	template <typename T>
	void print(T const& t)
	{
		print_helper(typename std::is_pointer<T>::type{}, t);
	}

	void test_print()
	{
		int x = 42;
		print(x);
		print(&x);
	}
}

// copy iterarotr type and arrays

// arrya version
template <typename InIt, typename OutIt>
OutIt optimized_copy_helper(InIt first, InIt last, OutIt out, std::true_type)
{
	size_t count = last - first;
	std::memmove(reinterpret_cast<void*>(out), reinterpret_cast<void const*>(first), sizeof(*first) * count);
	return out + count;
}

// container version
template <typename InIt, typename OutIt>
OutIt optimized_copy_helper(InIt first, InIt last, OutIt out, std::false_type)
{
	while (first != last)
	{
		*out++ = *first++;
	}
	return out;
}

// the template
template <typename InIt, typename OutIt>
OutIt optimized_copy(InIt first, InIt last, OutIt out)
{
	using is_safe_to_optimize_t =
		std::integral_constant<bool
							  ,  std::is_pointer<InIt>::value
							  && std::is_pointer<OutIt>::value
							  && std::is_trivially_copyable<std::decay_t<decltype(*first)>>::value
		>;
	std::cout << "optimized copy with InIt = " << typeid(InIt).name() << ", was optimized? " << is_safe_to_optimize_t{} << "\n";
	return optimized_copy_helper(first, last, out, is_safe_to_optimize_t{});
}

void optimized_copy_test()
{
	std::vector<int> v1{ 1,2,3 };
	std::vector<int> v2(v1.size());
	optimized_copy(v1.begin(), v1.end(), v2.begin());

	std::list<int> l1{ 1,2,3 };
	optimized_copy(l1.begin(), l1.end(), v2.begin());

	int a1[] = { 1,2,3 };
	int a2[3];
	optimized_copy(&a1[0], &a1[3], &a2[0]);
}

namespace outputtable_trait
{

	// only if this type is exist, we go to test with this version
	// this type save us from writing it inside the test version, and its more clear this way.
	template <typename T>
	using print_result_type = decltype(
		std::cout << std::declval<T const&>() // decval will create "instance" even without default constructor
		);

	template <typename T>
	struct is_outputtable
	{
		template <typename S> static std::false_type test(...);

		template <typename S, typename = print_result_type<S>>  // default paremeter without a name, we don't need  a name
		static std::true_type test(S*);

		using type = decltype(test<T>(nullptr)); // std::true_type or std::false_type
		static const bool value = type::value;

	};


	void test_is_outputtable()
	{
		struct A {};

		static_assert(is_outputtable<std::string>::value, "");
		static_assert(is_outputtable<int>::value, "");
		static_assert(is_outputtable<double>::value, "");
		static_assert(!is_outputtable<std::vector<int>>::value, "");
		static_assert(!is_outputtable<A>::value, "");

	}
}