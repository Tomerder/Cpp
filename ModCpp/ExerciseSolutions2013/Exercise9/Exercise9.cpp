#include <tuple>
#include <utility>

namespace withclassictmp
{
	template <typename...>
	struct count : std::integral_constant<int, 0>
	{
	};

	template <typename T, typename... Tail>
	struct count<T, T, Tail...> : std::integral_constant<int, 1 + count<T, Tail...>::value>
	{
	};

	template <typename T, typename Head, typename... Tail>
	struct count<T, Head, Tail...> : std::integral_constant<int, count<T, Tail...>::value>
	{
	};

	template <typename...>
	struct find1;

	template <typename X, typename Y>
	struct find1<X, Y> : std::integral_constant<int, -1>
	{
	};

	template <int I, typename T, typename... Tail>
	struct find1<std::integral_constant<int, I>, T, T, Tail...> : std::integral_constant<int, I>
	{
	};

	template <int I, typename T, typename Head, typename... Tail>
	struct find1<std::integral_constant<int, I>, T, Head, Tail...>
		: std::integral_constant<int, find1<std::integral_constant<int, I+1>, T, Tail...>::value>
	{
	};

	template <typename... Types>
	using find = find1<std::integral_constant<int, 0>, Types...>;

	template <typename T, typename... Types>
	T& get_by_type(std::tuple<Types...>& tup)
	{
		static_assert(count<T, Types...>::value == 1, "T must appear exactly once");
		return std::get<find<T, Types...>::value>(tup);
	}

	void test()
	{
		static_assert(count<int, float, int, bool>::value == 1, "");
		static_assert(count<int, float, double, bool>::value == 0, "");
		static_assert(count<int, int, int, bool>::value == 2, "");

		static_assert(find<int, float, int, bool>::value == 1, "");
		static_assert(find<int, float, double, bool>::value == -1, "");
		static_assert(find<int, int, int, bool>::value == 0, "");

		auto tup = std::make_tuple(1, 'a', 3.0f);
		get_by_type<int>(tup) = 2;
		get_by_type<char>(tup) = 'b';
		get_by_type<float>(tup) = 4.0f;
		// get_by_type<double>(tup) = 4.0; // doesn't compile
	}
}

namespace withconstexpr
{
	template <typename T>
	constexpr int count()
	{
		return 0;
	}

	template <typename T, typename Head, typename... Tail>
	constexpr int count()
	{
		return (std::is_same<T, Head>::value ? 1 : 0) + count<T, Tail...>();
	}

	template <typename T>
	constexpr int find(int)
	{
		return -1;
	}

	template <typename T, typename Head, typename... Tail>
	constexpr int find(int depth = 0)
	{
		return std::is_same<T, Head>::value ? depth : find<T, Tail...>(depth + 1);
	}

	template <typename T, typename... Types>
	T& get_by_type(std::tuple<Types...>& tup)
	{
		static_assert(count<T, Types...>() == 1, "T must appear exactly once");
		return std::get<find<T, Types...>()>(tup);
	}

	void test()
	{
		static_assert(count<int, float, int, bool>() == 1, "");
		static_assert(count<int, float, double, bool>() == 0, "");
		static_assert(count<int, int, int, bool>() == 2, "");

		static_assert(find<int, float, int, bool>() == 1, "");
		static_assert(find<int, float, double, bool>() == -1, "");
		static_assert(find<int, int, int, bool>() == 0, "");

		auto tup = std::make_tuple(1, 'a', 3.0f);
		get_by_type<int>(tup) = 2;
		get_by_type<char>(tup) = 'b';
		get_by_type<float>(tup) = 4.0f;
		// get_by_type<double>(tup) = 4.0; // doesn't compile
	}
}

int main()
{
	withclassictmp::test();
	withconstexpr::test();
	return 0;
}