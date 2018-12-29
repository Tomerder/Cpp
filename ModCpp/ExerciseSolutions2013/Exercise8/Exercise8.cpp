#include <tuple>
#include <iostream>

template <typename Tuple>
void print(std::ostream&, Tuple const&, std::integral_constant<int, -1>)
{
}

template <typename Tuple, int I>
void print(std::ostream& os, Tuple const& tup, std::integral_constant<int, I>)
{
	print(os, tup, std::integral_constant<int, I - 1>{});
	os << std::get<I>(tup) << (std::tuple_size<Tuple>::value - 1 == I ? "" : ", ");
}

template <typename... Types>
std::ostream& operator<<(std::ostream& os, std::tuple<Types...> const& tup)
{
	os << "( ";
	print(os, tup, std::integral_constant<int, sizeof...(Types)-1>{});
	os << " )";
	return os;
}

int main()
{
	std::cout << std::boolalpha << std::make_tuple("This is C++ in", 2015, "...and is it fun?", true) << "\n";
	return 0;
}