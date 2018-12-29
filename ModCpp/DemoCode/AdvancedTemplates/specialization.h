#pragma once

#include <iostream>
#include <cstring>

namespace dimov1
{
	template <typename T> void print(T)
	{
		std::cout << "print(T)\n";
	}
	template <> void print(int*)
	{
		std::cout << "print(int*)\n";
	}
	template <typename T> void print(T*)
	{
		std::cout << "print(T*)\n";
	}
	// what version of print will be called?
	void specialization_overloading()
	{
		int x = 42;
		print(&x);
	}
}

namespace dimov2
{
	template <typename T> void print(T)
	{
		std::cout << "print(T)\n";
	}
	template <typename T> void print(T*)
	{
		std::cout << "print(T*)\n";
	}
	template <> void print(int*)
	{
		std::cout << "print(int*)\n";
	}

	// now with different order, the print specialization is for T*
	void specialization_overloading()
	{
		int x = 42;
		print(&x);
	}
}

namespace dimov3
{
	// With helper class, all is well

	template <typename T>
	struct print_helper
	{
		static void print(T)
		{
			std::cout << "print(T)\n";
		}
	};

	template <typename T>
	struct print_helper<T*>
	{
		static void print(T*)
		{
			std::cout << "print(T*)\n";
		}
	};


	// function template
	template <typename T>
	void print(T t)
	{
		print_helper<T>::print(t);
	}

	void specialization_overloading()
	{
		int x = 42;
		print(&x);
	}
}

template <typename T>
struct smaller
{
	bool operator()(T const& a, T const& b) const
	{
		return a < b;
	}
};

// partial specialization
template <typename T>
struct smaller<T*>
{
	bool operator()(T* const& a, T* const& b) const
	{
		return *a < *b;
	}
};

// char * specialization
template <>
struct smaller<char const*>
{
	bool operator()(char const* const& a, char const* const& b) const
	{
		return strcmp(a, b) < 0;
	}
};

void test_smaller()
{
	auto s1 = smaller<int>{}(5, 3);

	int x = 5, y = 3;
	auto s2 = smaller<int*>{}(&x, &y);

	auto s3 = smaller<char const*>{}("aardvark", "abracadabra");
}