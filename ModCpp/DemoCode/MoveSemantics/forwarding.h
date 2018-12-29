#pragma once

#include "smart_ptr.h"

#include <string>
#include <vector>

template <typename T>
smart_ptr<T> make_smart()
{
	return smart_ptr<T>(new T);
}

template <typename T, typename Arg1>
smart_ptr<T> make_smart(Arg1 const& arg1)
{
	return smart_ptr<T>(new T(arg1));
}
template <typename T, typename Arg1>
smart_ptr<T> make_smart(Arg1& arg1)
{
	return smart_ptr<T>(new T(arg1));
}

template <typename T, typename Arg1, typename Arg2>
smart_ptr<T> make_smart(Arg1 const& arg1, Arg2 const& arg2)
{
	return smart_ptr<T>(new T(arg1, arg2));
}
template <typename T, typename Arg1, typename Arg2>
smart_ptr<T> make_smart(Arg1& arg1, Arg2 const& arg2)
{
	return smart_ptr<T>(new T(arg1, arg2));
}
template <typename T, typename Arg1, typename Arg2>
smart_ptr<T> make_smart(Arg1 const& arg1, Arg2& arg2)
{
	return smart_ptr<T>(new T(arg1, arg2));
}
template <typename T, typename Arg1, typename Arg2>
smart_ptr<T> make_smart(Arg1& arg1, Arg2& arg2)
{
	return smart_ptr<T>(new T(arg1, arg2));
}

struct employee
{
	employee(std::string name, int id)
	{
	}
	employee(std::vector<employee>& reports)
	{
	}
	employee(employee&& rhs)
	{
	}
};

void make_cpp98()
{
	using namespace std::string_literals;

	auto p1 = make_smart<employee>("Dave"s, 1);	// make_smart<employee, std::string const&, int const&>
	
	std::vector<employee> reports{};
	auto p2 = make_smart<employee>(reports);	// make_smart<employee, std::vector<employee>&>

	// And this one doesn't compile at all, because we're not preserving the rvalue reference.
	// We're trying to call employee::employee(employee const&) here.
	// auto p3 = make_smart<employee>(std::move(*p2));
}

template <typename T, typename Arg1>
smart_ptr<T> make_smarter(Arg1&& arg1)
{
	return smart_ptr<T>(new T(std::forward<Arg1>(arg1)));
}

template <typename T, typename Arg1, typename Arg2>
smart_ptr<T> make_smarter(Arg1&& arg1, Arg2&& arg2)
{
	return smart_ptr<T>(new T(std::forward<Arg1>(arg1), std::forward<Arg2>(arg2)));
}

void make_cpp11()
{
	using namespace std::string_literals;

	auto p1 = make_smarter<employee>("Dave"s, 1);		// make_smarter<employee, std::string, int>(std::string&&, int&&)

	std::vector<employee> reports{};
	auto p2 = make_smarter<employee>(reports);			// make_smarter<std::vector<employee>&>(std::vector<employee>&)

	auto p3 = make_smarter<employee>(std::move(*p2));	// make_smarter<employee>(employee&&)
}