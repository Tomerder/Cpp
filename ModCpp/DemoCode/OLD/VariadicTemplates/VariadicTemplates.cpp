#include <iostream>
#include <type_traits>
#include <string>
#include <map>
#include <assert.h>

// --- tuples: complex example ---

template <typename... Ts>
struct tuple {}; //Empty base case

template <typename T, typename... Ts>
struct tuple<T,Ts...> : public tuple<Ts...> {
	T head_;
	tuple(T&& head, Ts&&... tail) :
		tuple<Ts...>(std::forward<Ts>(tail)...), head_(head)
	{}
};

template <size_t k, typename>
struct tuple_element;

template <typename T, typename... Ts>
struct tuple_element<0,tuple<T,Ts...>> {
	typedef T type;
};

template <size_t k, typename T, typename... Ts>
struct tuple_element<k,tuple<T,Ts...>> {
	typedef typename tuple_element<k-1,tuple<Ts...>>::type type;
};

//Compared to Alexandrescu, I removed the enable_if here because
//when k==0, this specialization is preferred to the second one.
template <size_t k, typename... Ts>
// typename std::enable_if<
// 		k==0,
// 		typename tuple_element<0,tuple<Ts...>>::type&
// 	>::type
typename tuple_element<0,tuple<Ts...>>::type&
get(tuple<Ts...>& tup) {
	return tup.head_;
}

template <size_t k, typename T, typename... Ts>
typename std::enable_if<
		k!=0, //Necessary to prevent recursing indefinitely
		typename tuple_element<k,tuple<T,Ts...>>::type&
	>::type
get(tuple<T,Ts...>& tup) {
	tuple<Ts...>& rbase = tup;
	return get<k-1>(rbase);
}

// --- syntax only ---
/* //Does not compile in gcc 4.6.2
template <typename... Ts>
void make_map() {
  std::map<Ts...> m;
}
*/

// --- simple examples ---

template <typename T1, typename T2>
bool assertContained(T1&& v1, T2&& v2) {
  return v1 == v2;
}

template <typename T1, typename T2, typename... Ts>
bool assertContained(T1&& v1, T2&& v2, Ts&&... vs) {
  return (v1 == v2 || assertContained(v1, vs...));
}

template <typename T>
void print(T&& v) {
	std::cout << v << std::endl;
}

template <typename... Ts>
void print_many(Ts&&... vs) {
	//Empty base case. The compiler will choose this function
	//only when the parameter list is empty.
}

template <typename T, typename... Ts>
void print_many(T&& v, Ts&&... vs) {
	print(v);
	print_many(vs...);
}

int main() {
	print_many(14, "Hello World", 42.0f);
	tuple<int,float,double> tup(42,43.0f,44.0);
	std::cout << get<0>(tup) << " " << get<1>(tup) << " " << get<2>(tup) << std::endl;
	typename tuple_element<0,tuple<int,std::string,double>>::type i = 42.0f;
	typename tuple_element<1,tuple<int,std::string,double>>::type f = "Hi";
	std::cout << i << " " << f;
	assert(assertContained(1, 4, 2, 1, 4, 5));
	//make_map<int,int>();
	return 0;
}