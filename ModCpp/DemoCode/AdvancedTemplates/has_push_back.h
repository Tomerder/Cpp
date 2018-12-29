#pragma once

#include <vector>
#include <list>
#include <set>
#include <string>

namespace withdecltype
{
	template <typename T, typename E>
	struct has_push_back
	{
        // The template parameter replacement with T1 = T and E1 = E is strictly necessary.
        // If we use T and E in the decltype directly, it's not a substitution failure but
        // rather a hard error when there is no push_back member. Curiously, this actually
        // compiles on VC++ but doesn't work in clang or gcc, which means it's likely non-
        // standard behavior on VC++ behalf.
		template <typename U, typename T1 = T, typename E1 = E>
		static auto test(U*) -> decltype(
			std::declval<T1&>().push_back(std::declval<E1>()), int()
			);

		static char test(...);

		static const bool value = (sizeof(test((T*)0)) == sizeof(int));
	};

	void test_has_push_back()
	{
		static_assert(has_push_back<std::vector<int>, int>::value, "");
		static_assert(has_push_back<std::list<int>, int&&>::value, "");
		static_assert(!has_push_back<std::set<int>, int>::value, "");
		static_assert(!has_push_back<std::vector<int>, std::string>::value, "");
	}
}


namespace withdecltype_version2
{
	template <typename Container, typename Element>
	using has_push_back = decltype(
		std::declval<Container>().push_back(std::declval<Element>()));

	template <typename Container, typename Element>
	struct is_pushbackable
	{
		template <typename S1, typename S2>
		static std::false_type test(...);

		template <typename S1, typename S2, typename = has_push_back<S1, S2>>
		static std::true_type test(S1*);

		using type = decltype(test<Container, Element>(nullptr));

		static const bool value = type::value;

	};

	void test_has_push_back()
	{
		static_assert(is_pushbackable<std::vector<int>, int>::value, "");
		static_assert(is_pushbackable<std::list<int>, int&&>::value, "");
		static_assert(!is_pushbackable<std::set<int>, int>::value, "");
		static_assert(!is_pushbackable<std::vector<int>, std::string>::value, "");
	}
}

namespace withconstexpr
{   
	// This doesn't compile with VC++, but there is an alternative shown below that works
	// with all compilers.
	//template <typename T, typename E>
	//constexpr auto f(int) -> decltype(
	//	std::declval<T&>().push_back(std::declval<E>()), bool()
	//	)
	//{
	//	return true; // If necessary, do return type checking here
	//}

	template <typename T, typename E,
		typename = decltype(std::declval<T&>().push_back(std::declval<E>()))> // declaval with & will return a lvalue instead of rvalue. not a must in this case, only to demonstrate.
	constexpr bool f(int)
	{
		return true;
	}

	template <typename T, typename E>
	constexpr bool f(...) { return false; }

	template <typename T, typename E>
	using has_push_back = std::integral_constant<bool, f<T, E>(0)>;

	void test_has_push_back()
	{
		static_assert(has_push_back<std::vector<int>, int>::value, "");
		static_assert(has_push_back<std::list<int>, int&&>::value, "");
		static_assert(!has_push_back<std::set<int>, int>::value, "");
		static_assert(!has_push_back<std::vector<int>, std::string>::value, "");
	}
}

namespace withvoidt
{
#ifdef EXPRESSION_SFINAE_SUPPORTED

	template <typename T> using void_t = void;

	template <typename T, typename E>
	using push_back_t = decltype(
		std::declval<T&>().push_back(std::declval<E>())
		);

	template <typename T, typename E, typename R, typename = void>
	struct has_push_back : std::false_type
	{
	};

	template <typename T, typename E, typename R>
	struct has_push_back<T, E, R, void_t<push_back_t<T, E>>>
		: std::is_same<push_back_t<T, E>, R>
	{
	};

#endif

	void test_has_push_back()
	{
#ifdef EXPRESSION_SFINAE_SUPPORTED
		static_assert(has_push_back<std::vector<int>, int, void>::value, "");
		static_assert(!has_push_back<std::vector<int>, int, bool>::value, "");
		static_assert(has_push_back<std::list<int>, int&&, void>::value, "");
		static_assert(!has_push_back<std::set<int>, int, void>::value, "");
		static_assert(!has_push_back<std::vector<int>, std::string, void>::value, "");
#endif
	}
}