#pragma once

#include <iostream>
#include <type_traits>
#include <vector>
#include <set>
#include <string>

template <typename T>
struct voider
{
	using type = void;
};

template<typename T>
using void_t = typename voider<T>::type;

template <typename T, typename = void>
struct is_printable : std::false_type
{
};

template <typename T>
struct is_printable<T, void_t<decltype(std::declval<std::ostream&>() << std::declval<T>())>> : std::true_type
{
};

template <typename T, typename = void>
struct is_container : std::false_type
{
};

template <typename T>
struct is_container<T, void_t<typename T::iterator>> : std::true_type
{
};

template <typename T>
typename std::enable_if<!is_container<T>::value || is_printable<T>::value>::type print(
	T const& scalar, size_t indent = 0)
{
	std::cout << std::string(indent, '\t');
	std::cout << typeid(T).name() << " = ";
	std::cout << scalar << std::endl;
}

template <typename T>
typename std::enable_if<is_container<T>::value && !is_printable<T>::value>::type print(
	T const& container, size_t indent = 0)
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

int main()
{
	std::vector<int> v{ 1, 2, 3 };
	print(v);

	int x = 42;
	print(x);
	print(7);

	print(std::set<std::vector<std::string>>{ { "a", "b" }, { "c" } });

	// NOTE: this may require access to a compiler that fully supports
	// expression SFINAE. If Visual C++ doesn't manage to build your code
	// properly, try one of the online gcc/clang compilers, such as the
	// http://ideone.com website (free, no registration required).
	print(std::string{ "Hello, World" });

	return 0;
}