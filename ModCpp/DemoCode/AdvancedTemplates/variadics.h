#pragma once

#include <memory>
#include <algorithm>
#include <string>
#include <iostream>


namespace	make_unique
{

	template <typename T, typename... Args>
	std::unique_ptr<T> create_unique(Args... args)
	{
		return std::unique_ptr<T>(new T((args)...));
	}

	void test_create_unique()
	{
		auto p1 = create_unique<int>(42);
		auto p2 = create_unique<std::string>("hello");

	}






	// better version with universal reference
	template <typename T, typename... Args>
	std::unique_ptr<T> create_unique_smarter(Args&&... args)
	{
		return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
	}

	void test_create_unique_smarter()
	{
		struct s1
		{
			s1(int) {}
		};
		struct s2
		{
			s2(int&&) {}
		};
		struct s3
		{
			s3(int&) {}
		};

		struct s4
		{
			s4(int&, int&) {}
		};

		int x = 42;

		auto p1 = create_unique_smarter<s1>(42);
		auto p2 = create_unique_smarter<s1>(x);
		auto p3 = create_unique_smarter<s2>(std::move(x));
		auto p4 = create_unique_smarter<s2>(42);
		auto p5 = create_unique_smarter<s3>(x);
		auto p6 = create_unique_smarter<s4>(x, x);
	}

}

namespace adder
{
	template<typename T>
	T adder(T v) 
	{
		return v;
	}

	template<typename T, typename... Args>
	T adder(T first, Args... args) 
	{
		// sizeof...(args) // number of elemnts. maybe the correct name is countof...
		//std::cout << __FUNCSIG__ << std::endl;
		return first + adder(args...);
	}

	void test_adder()
	{
		int result = adder(1, 19, 25, 33, 21);

		std::string s1 = "x", s2 = "aa", s3 = "bb", s4 = "yy";
		std::string ssum = adder(s1, s2, s3, s4);

	}

}

namespace count
{

	template<typename... list>
	struct count;

	template<> 
	struct count<> 
	{
		static const int value = 0;
	};

	template<typename head, typename... tail>
	struct count<head, tail...> 
	{
		static const int value = 1 + count<tail...>::value;
	};

	void test_count()
	{
		int n = count<int, char, long>::value; // returns 3
	}
}


namespace print
{


	void simple_print()
	{
	}

	template <typename Head, typename... Tail>
	void simple_print(Head&& head, Tail&&... tail)
	{
		std::cout << head << "\n";
		simple_print(tail...);
	}

	void test_simple_print()
	{
		simple_print(1, "hello", 42.3);
	}

}

namespace varmax
{

	template <typename T>
	struct is
	{
		using type = T;
	};

	template <typename...>
	struct largest_t; // undefined

	template <typename T>
	struct largest_t<T> : is<T>
	{
	};

	template <typename T1, typename T2, typename... Rest>
	struct largest_t<T1, T2, Rest...>
		: std::conditional < (sizeof(T1) < sizeof(T2))
		, typename largest_t<T2, Rest...>::type
		, typename largest_t<T1, Rest...>::type
		>
	{
	};


	template <template <class> class Op>
	constexpr bool and_f()
	{
		return true;
	}

	template <template <class> class Op, typename T, typename... Types>
	constexpr bool and_f()
	{
		return Op<T>::value && and_f<Op, Types...>();
	}

	template <typename... Types, typename = std::enable_if_t<and_f<std::is_integral, Types...>()>>
	auto varmax(Types... args)
	{
		using largest = typename largest_t<Types...>::type;
		std::initializer_list<largest> list{ static_cast<largest>(args)... };
		return *std::max_element(list.begin(), list.end());
	}

	void test_varmax()
	{
		auto m = varmax(1u, 32ull, 'a');
		std::cout << m << " of type " << typeid(decltype(m)).name() << "\n";
	}

}


namespace safeprintf
{



	constexpr char FORMAT_SPECIFIER = '%';

	void safe_printf(std::string const& format)
	{
		if (format.find(FORMAT_SPECIFIER) != std::string::npos)
		{
			throw std::invalid_argument("too many format specifiers in format string");
		}
		std::cout << format;
	}

	template <typename Head, typename... Tail>
	void safe_printf(std::string const& format, Head const& head, Tail const&... tail)
	{
		auto pct_pos = format.find(FORMAT_SPECIFIER);
		if (pct_pos == std::string::npos)
		{
			throw std::invalid_argument("too many arguments provided for format string");
		}
		std::cout << format.substr(0, pct_pos);
		std::cout << head;
		safe_printf(format.substr(pct_pos + 1), tail...);
	}

#ifdef CONSTEXPR_WORKS_REALLY_WELL

	struct compile_time_string
	{
		char const* str_;
		size_t size_;

		template <size_t N>
		constexpr compile_time_string(char const(&str)[N])
			: str_(str), size_(N)
		{
		}

		constexpr int count(char ch, size_t offset = 0) const
		{
			return (offset >= size_) ? 0 : ((str_[offset] == ch ? 1 : 0) + count(ch, offset + 1));
		}
	};

	template <typename... Types>
	constexpr auto tl_length(Types&&...)
	{
		return sizeof...(Types);
	}

#define SAFE_PRINTF(format, ...) \
	static_assert(compile_time_string(format).count(FORMAT_SPECIFIER) == tl_length(__VA_ARGS__), "number of parameters to SAFE_PRINTF doesn't match"); \
	safe_printf(format, ##__VA_ARGS__);

	void compile_time_tests()
	{
		// Should not compile:
		SAFE_PRINTF("%");
		SAFE_PRINTF("% %", 42);
		SAFE_PRINTF("%", 42, 42);

		// OK:
		SAFE_PRINTF("%", 42);
	}

#endif

	void test_printf()
	{
		using namespace std::string_literals;

		safe_printf("Today is %, % %\n", "Tuesday", "December"s, 30);

		try
		{
			safe_printf("% %", 42);
		}
		catch (std::invalid_argument& e)
		{
			std::cout << "caught exception: " << e.what() << "\n";
		}
		try
		{
			safe_printf("%", 42, 42);
		}
		catch (std::invalid_argument& e)
		{
			std::cout << "caught exception: " << e.what() << "\n";
		}
	}

}