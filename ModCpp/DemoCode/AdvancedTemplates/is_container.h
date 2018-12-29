#pragma once

#include <iostream>
#include <type_traits>
#include <vector>
#include <set>
#include <string>

namespace cpp98
{
	template <typename T>
	struct is_container
	{
		// we are using specialization that takes everything (...) or somthing with iterator. (...) is always inferior.
		template <typename S> static char test(...);
		template <typename S> static int  test(typename S::iterator*); // typename sometimes is needed to undestand that its a type

		// only  the test iterator version will be sizeof == int
		static const bool value = (sizeof(test<T>(nullptr)) == sizeof(int));
	};

	void test_is_container()
	{
		static_assert(is_container<std::vector<int>>::value, "");
		static_assert(is_container<std::set<int>>::value, "");
		static_assert(!is_container<double>::value, "");
	}
}

namespace cpp11
{
	// wrapper<T> wraps an T and produces an overload that is not as good
	// as an overload that takes a T directly. This helps avoid writing an
	// overload that takes an ellipsis parameter (...), which is ugly and needs
	// additional explanation.
	template <typename T>
	struct wrapper
	{
		wrapper(T)
		{
		}
	};

	template <typename T> struct is_container_h
	{
		template <typename U, typename = typename U::iterator> // default paremeter, this version is choosen only if type U have ::iteraor
		static std::true_type  test(U&&); // univeral ref

		static std::false_type test(wrapper<T>);

		using type = decltype(test(std::declval<T>())); // declval return an instance - for template use
		static constexpr bool value = type::value;
	};

	template <typename T> struct is_container
		: std::integral_constant<bool, is_container_h<T>::value> // inherit the integral_constant will give us ::value
	{
	};

	void test_is_container()
	{
		static_assert(is_container<std::vector<int>>::value, "");
		static_assert(is_container<std::set<int>>::value, "");
		static_assert(!is_container<int>::value, "");
	}
}

namespace voidt
{
	// This is what we would like to write, but unfortunately it's not standard whether or not
	// it is a substituion failure in this case. So we use the slightly more verbose version.
	// template <typename...>
	// using void_t = void;

	template<typename...>
	struct make_void { typedef void type; };

	template<typename... Ts>
	using void_t = typename make_void<Ts...>::type;

	template <typename T, typename = void>
	struct is_container : std::false_type
	{
	};

	template <typename T>
	struct is_container<T, void_t<typename T::iterator>> : std::true_type
	{
	};

	template <typename T>
	typename std::enable_if<!is_container<T>::value>::type print(T const& scalar, size_t indent = 0)
	{
		std::cout << std::string(indent, '\t');
		std::cout << typeid(T).name() << " = ";
		std::cout << scalar << std::endl;
	}

	template <typename T>
	typename std::enable_if<is_container<T>::value>::type print(T const& container, size_t indent = 0)
	{
		std::cout << std::string(indent, '\t');
		std::cout << typeid(T).name() << " { " << std::endl;
		for (auto const& element : container)
		{
			print(element, indent + 1);
		}
		std::cout << std::string(indent, '\t');
		std::cout << "}" << std::endl;
	}

	void test_print()
	{
		std::vector<int> v{ 1,2,3 };
		print(v);

		int x = 42;
		print(x);
		print(7);

		print(std::set<std::vector<std::string>>{ { "a", "b" }, { "c" } });
	}
}