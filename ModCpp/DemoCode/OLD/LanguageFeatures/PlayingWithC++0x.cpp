
#pragma region Includes and Usings

#include <windows.h>

#include <cstdlib>
#include <cmath>
#include <map>
#include <list>
#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <type_traits>
#include <vector>
#include <new>

using std::sqrt;
using std::rand;
using std::map;
using std::list;
using std::cout;
using std::endl;
using std::ostream;
using std::string;
using std::for_each;
using std::find_if;
using std::function;
using std::vector;
using std::nothrow;

#pragma endregion

#pragma region Auto Variables

class base {};
class derived1 : public base {};
class derived2 : public base {};

//auto keyword: http://msdn.microsoft.com/en-us/library/dd293667(VS.100).aspx
void auto_variables()
{
	int i = 10;
	auto j = i + 20;
	auto k = j < rand() ? i : j;
	//auto m = j > rand() ? 0.5 : "Hello";
	//auto *p = j > rand() ? new derived2() : new derived1();
	auto *p = j > rand() ? (base*)new derived2() : new derived1();
	auto &r = *new derived1();
	auto q = i, *s = &j, &t = k;
	const auto x = s;
	auto *y = new auto(i + 20);
	auto self = auto_variables;

	list<map<int,double>> oh_my;
	auto iter = oh_my.begin();
}

#pragma endregion

#pragma region ForEach

template <typename T>
class my_array
{
private:
	int size_;
	T* items_;
public:
	typedef T* iterator;
	typedef const T* const_iterator;
	
	my_array(int size) : size_(size), items_(new T[size]) {}
	~my_array() { delete[] items_; }
	
	iterator begin() { return &items_[0]; }
	iterator end() { return &items_[size_]; }
	const_iterator begin() const { return &items_[0]; }
	const_iterator end() const { return &items_[size_]; }
};

//for_each, in statement: http://msdn.microsoft.com/en-us/library/ms177202(VS.100).aspx
void for_each_in()
{
	map<int,list<double>> values;
	values[5].push_back(20);
	values[5].push_back(30);
	values[4].push_back(12);

	auto iter = values.begin();
	for (; iter != values.end(); ++iter)
	{
		cout << iter->first << endl;
		for each (auto val in iter->second)
			cout << '\t' << val << endl;
	}

	int numbers[] = {1,2,3,4,5};
	for each (int n in numbers)
		cout << n << ' ';
	cout << endl;

	my_array<float> arr(10);
	const auto &ref_arr = arr;
	for each (float flt in ref_arr)//access through const_iterator
		cout << flt << ' ';
	cout << endl;
}

#pragma endregion

#pragma region DeclType

struct Complex
{
	double real;
	double imag;
	double abs_plus(double d) { return sqrt(real*real+imag*imag)+d; }
};
ostream& operator<<(ostream& os, Complex& c)
{
	os << c.real << ' ' << c.imag;
	return os;
}

//This can be more properly rewritten using std::forward<T> and r-value references. See below.
template <typename T, typename S>
auto add(const T& t, const S& s) -> decltype(t+s)
{
	return t+s;
}

//decltype operator: http://msdn.microsoft.com/en-us/library/dd537655(VS.100).aspx
void decl_type_operator()
{
	float arr[15];
	decltype(arr) another_arr = {1,2,3};
	decltype(arr[0]) a_float_ref = arr[9];//float&
	decltype(arr[1]+7) a_float = 42.0f;//float

	decltype(rand()) number = rand();

	Complex i = { 0.0, 1.0 };
	const Complex* j = &i;
	decltype(i.real) real_val = 16.0;//double
	decltype((i.real)) real_val_ref = i.real;//double&
	real_val_ref++;
	//decltype((i.abs_plus)) fptr = &Complex::abs_plus;	//doesn't compile
	decltype((j->imag)) imag_val_ref = j->real;//const double&
	decltype(j->imag) imag_val = j->imag;//double
	imag_val++;
	cout << i << endl;

	decltype(add(5,42.4)) sum = add(5,42.4);
	string str = add(string("Goodbye, old "),'C');
	cout << sum << ' ' << str << endl;
}

#pragma endregion

#pragma region Lambda Functions

template <typename T, typename Iterator>
struct enumerable
{
	Iterator begin_, end_;
	enumerable(Iterator begin, Iterator end) : begin_(begin), end_(end) {}
	operator bool() { return begin_ != end_; }
	enumerable& operator++() { if (*this) { ++begin_; } return *this; }
	T& operator*() { return *begin_; }

	template <typename Ftor> void apply(Ftor ftor)
	{
		while (*this)
		{
			ftor(**this);
			++(*this);
		}
	}
	template <typename Ftor, typename Filter> void apply(Ftor ftor, Filter flt)
	{
		while (*this)
		{
			if (flt(**this))
				ftor(**this);
			++(*this);
		}
	}
};

template <typename _Iterator>
static auto make_enumerable(_Iterator begin, _Iterator end) 
	-> enumerable<decltype(*begin),_Iterator>
{
	return enumerable<decltype(*begin),_Iterator>(begin,end);
}

template <typename G>
auto generator(G next) -> list<decltype(next(NULL))>
{
	list<decltype(next(NULL))> lst;
	bool has_more;
	decltype(next(NULL)) val = next(&has_more);
	while (has_more)
	{
		lst.push_back(val);
		val = next(&has_more);
	}
	return lst;
}

template <typename Iterator, typename Combiner>
auto aggregate(
	Iterator begin,
	Iterator end,
	Combiner comb,
	decltype(comb(*begin,*begin)) initial)
		-> decltype(comb(*begin,*begin))
{
	decltype(comb(*begin,*begin)) result = initial;
	for (; begin != end; ++begin)
	{
		result = comb(result,*begin);
	}
	return result;
}

function<int(void)> prime_number_generator(int start)
{
	return [start]() mutable -> int {
		while (true) {
			if (start == 2) {
				return start++;
			}
			if (start%2 != 0) {
				int root = (int)std::sqrt((double)start) + 1;
				bool stop = false;
				for (int n = 3; n <= root && !stop; n += 2) {
					if (start%n == 0)
						stop = true;
				}
				if (!stop)
					return start++;
			}
			++start;
		}
	};
}

//Note: 'this' can be captured implicitly or explicitly like any other variable.

//lambda functions: http://msdn.microsoft.com/en-us/library/dd293608(VS.100).aspx
void lambda_functions()
{
	int generated = 0;//captured by reference and mutated inside the lambda
	list<int> numbers = generator([&generated](bool* has_next)->int { *has_next = ++generated < 100; return generated; });
	for_each(numbers.begin(), numbers.end(), [](int n) { if (n%7==0) cout << n << ' '; });
	cout << endl;

	int result = aggregate(numbers.begin(), numbers.end(), [](int curr,int next)->int { return curr-next; }, 1000);
	cout << result << endl;

	auto my_enum = make_enumerable(numbers.begin(), numbers.end());
	my_enum.apply(
		[](int n) { cout << n << ' '; },//functor
		[](int n) { return n%13==0; }); //filter
	cout << endl;

	auto add_f = [](int a,int b) { return a+b; };
	auto something = aggregate(numbers.begin(),numbers.end(),add_f,0);
	cout << something << endl;

	//the following is a lambda that takes a lambda and returns a lambda. it's a high-order function.
	auto curry = [](const function<int(int,int)>& f, int a) ->function<int(int)> { return [=](int b) { return f(b,a); }; };
	auto add_5 = curry(add_f, 5);
	cout << "Curry? " << add_5(13) << endl;

	int x = 12;
	auto checker = [x](int n) { return n!=0 && n!=x && n%x==0; };
	auto divisible_by = *find_if(numbers.begin(), numbers.end(), checker);
	cout << divisible_by << endl;
	x = 13;
	divisible_by = *find_if(numbers.begin(), numbers.end(), checker);//nothing changes - x is captured by value
	cout << divisible_by << endl;
	
	auto checker2 = [&x](int n) { return n!=0 && n!=x && n%x==0; };
	divisible_by = *find_if(numbers.begin(), numbers.end(), checker2);
	cout << divisible_by << endl;
	x = 17;
	divisible_by = *find_if(numbers.begin(), numbers.end(), checker2);//works - x is captured by reference
	cout << divisible_by << endl;

	int fib1 = 1, fib2 = 1;
	auto next_step = [&]() { int temp = fib2; fib2 = fib2 + fib1; fib1 = temp; };//capture by reference
	for (int i = 0; i < 20; ++i)
		next_step();
	cout << fib2 << endl;

	int howmany = 25;
	auto next_num = [=](int prev) mutable ->int		//mutable lambda
		{ return (--howmany > 0) ? prev+1 : 0; };
	int curr = 1;
	while (curr != 0)
	{
		curr = next_num(curr);
		cout << curr << ' ';
	}
	cout << endl;

	auto primes_from_100 = prime_number_generator(100);
	for (int i = 0; i < 10; ++i)
		std::cout << primes_from_100() << ' ';
	std::cout << endl;
}

#pragma endregion

#pragma region Static Assert

template <int N>
struct fibo
{
	enum { value = fibo<N-1>::value + fibo<N-2>::value };
};
template <>
struct fibo<1>
{
	enum { value = 1 };
};
template <>
struct fibo<0>
{
	enum { value = 1 };
};

template <typename T>
class exceptionsafe_stack
{
private:
	int size_;
	T* stack_;
	int top_;
public:
	exceptionsafe_stack(int size) throw()
		: size_(size), stack_(new (nothrow) T[size]), top_(-1)
	{
		static_assert(std::tr1::has_nothrow_assign<T>::value, "T must have nothrow assignment operator");
		static_assert(std::tr1::has_nothrow_constructor<T>::value, "T must have nothrow constructor");
	}
	~exceptionsafe_stack() throw()
	{
		delete[] stack_;
	}
	bool pop(T& value) throw()
	{
		if (top_ == -1)
			return false;
		value = stack_[top_];
		--top_;
		return true;
	}
	bool push(const T& value) throw()
	{
		if (stack_ == nullptr || top_ == size_ - 1)
			return false;
		++top_;
		stack_[top_] = value;
		return true;
	}
private:
	exceptionsafe_stack& operator=(const exceptionsafe_stack&);
	exceptionsafe_stack(const exceptionsafe_stack&);
};

class just_some_type
{
public:
	just_some_type() {}
};

template <typename T>
void write_out(ostream& os, const T& value)
{
	static_assert(
		(std::tr1::is_array<T>::value && std::tr1::is_arithmetic<std::tr1::remove_extent<T>::type>::value) ||
		std::tr1::is_arithmetic<T>::value, "T must be an arithmetic type or a 1-dimensional array of such");

	//Proceed to write out the value in some way
}

//static_assert declaration: http://msdn.microsoft.com/en-us/library/dd293588(VS.100).aspx
void static_assertions()
{
	int arr[] = {42,42,43,0,17};
	write_out(cout, arr);
	//The following won't compile because of the static_assert.
	/*
	derived1 arr2[10];
	write_out(cout, arr2);
	write_out(cout, derived2());
	*/

	static_assert(fibo<0>::value == 1, "Definition for 0 is missing or wrong");
	static_assert(fibo<1>::value == 1, "Definition for 1 is missing or wrong");
	static_assert(fibo<2>::value == 2, "Definition for 2 is wrong");
	static_assert(fibo<3>::value == 3, "Definition for 3 is wrong");
	static_assert(fibo<4>::value == 5, "Definition for 4 is wrong");
	static_assert(fibo<5>::value == 8, "Definition for 5 is wrong");

	static_assert(sizeof(long) == sizeof(int), "What compiler are you using?? Your ints aren't long!");

	static_assert(std::tr1::is_pod<long>::value, "A long isn't a Plain Old Data type.");
	static_assert(std::tr1::is_compound<list<int>>::value, "A list<int> isn't a compound type.");
	static_assert(std::tr1::is_empty<derived2>::value, "derived2 isn't an empty class.");
	static_assert(std::tr1::is_base_of<base,derived1>::value, "base isn't the base of derived2.");
	static_assert(std::tr1::is_convertible<int,char>::value, "char isn't convertible to int.");
	//and so on. see <type_traits>: http://msdn.microsoft.com/en-us/library/bb982077.aspx

	exceptionsafe_stack<int> es_int(10);
	exceptionsafe_stack<derived1> es_class(10);
	//exceptionsafe_stack<just_some_type> es_type(10);	//won't compile because ctor is not throw()
}

#pragma endregion

#pragma region Rvalue References

class my_string_old
{
private:
	char* str_;
	int len_;
public:
	explicit my_string_old(const char* str)
	{
		if (str == nullptr)
		{
			len_ = 0;
			str_ = nullptr;
		}
		else
		{
			len_ = strlen(str) + 1;
			str_ = new char[len_];
			strcpy_s(str_, len_, str);
		}
	}
	explicit my_string_old(int len)
	{
		len_ = len;
		str_ = new char[len_];
		str_[0] = '\0';
	}
	my_string_old(const my_string_old& that)
	{
		len_ = that.len_;
		if (that.str_ == nullptr)
		{
			str_ = nullptr;
		}
		else
		{
			str_ = new char[len_];
			strcpy_s(str_, len_, that.str_);
		}
	}
	my_string_old& operator=(const my_string_old& that)
	{
		if (this == &that)
			return *this;

		if (str_ != nullptr)
			delete[] str_;
		
		str_ = nullptr;
		len_ = that.len_;
		if (that.str_ != nullptr)
		{
			str_ = new char[len_];
			strcpy_s(str_, len_, that.str_);
		}
	}
	~my_string_old()
	{
		if (str_ != nullptr)
		{
			delete[] str_;
			str_ = nullptr;
		}
		len_ = 0;
	}
};

class my_string_new
{
private:
	char* str_;
	int len_;
public:
	//standard functions:
	explicit my_string_new(const char* str)
	{
		if (str == nullptr)
		{
			len_ = 0;
			str_ = nullptr;
		}
		else
		{
			len_ = strlen(str) + 1;
			str_ = new char[len_];
			strcpy_s(str_, len_, str);
		}
	}
	explicit my_string_new(int len)
	{
		len_ = len;
		str_ = new char[len_];
		str_[0] = '\0';
	}
	my_string_new(const my_string_new& that)
	{
		len_ = that.len_;
		if (that.str_ == nullptr)
		{
			str_ = nullptr;
		}
		else
		{
			str_ = new char[len_];
			strcpy_s(str_, len_, that.str_);
		}
	}
	my_string_new& operator=(const my_string_new& that)
	{
		if (this == &that)
			return *this;

		if (str_ != nullptr)
			delete[] str_;
		
		str_ = nullptr;
		len_ = that.len_;
		if (that.str_ != nullptr)
		{
			str_ = new char[len_];
			strcpy_s(str_, len_, that.str_);
		}
	}
	~my_string_new()
	{
		if (str_ != nullptr)
		{
			delete[] str_;
			str_ = nullptr;
		}
		len_ = 0;
	}
	//move functions:
	my_string_new(my_string_new&& that)
	{
		*this = std::move(that); //std::move preserves && semantics so operator=(&&) is called
	}
	my_string_new& operator=(my_string_new&& other)
	{
		if (this == &other)
			return *this;//handle self-assignment

		str_ = other.str_;
		len_ = other.len_;
		
		other.str_ = NULL;
		other.len_ = 0;

		return *this;
	}
};

double measure_time(int times, function<void(void)> action)
{
	double total = 0.0;
	action();//discard first measurement to warm up
	for (int i = 0; i < times; ++i)
	{
		DWORD begin = GetTickCount();
		action();
		total += GetTickCount() - begin;
	}
	return total / times;
}

struct A { void act(int&) {} };
struct B { void act(const int&) {} };
struct C { void act(int) {} };

template <typename ACTOR, typename T>
void old_act(const T& t)
{
	ACTOR actor;
	actor.act(t);
}
template <typename ACTOR, typename T>
void old_act(T& t)
{
	ACTOR actor;
	actor.act(t);
}
template <typename ACTOR, typename T>
void new_act(T&& t)
{
	//somewhat surprisingly, t is an lvalue in the method body.
	//std::forward<T> passes T&& to ACTOR::act if it takes an rvalue reference,
	//or passes t (as an lvalue) to ACTOR::act if it takes an lvalue.
	//see also: http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2009/n2951.html

	ACTOR actor;
	actor.act(std::forward<T>(t));
}

void rvalue_references()
{
	int x = 42;
	old_act<A>(x);	//T& version is invoked
	old_act<B>(x);
	old_act<C>(x);
	//old_act<A>(42);	//doesn't compile
	old_act<B>(42);
	old_act<C>(42);

	new_act<A>(x);
	new_act<B>(x);
	new_act<C>(x);
	//new_act<A>(42);	//still doesn't compile, A::act wants a true lvalue
	new_act<B>(42);
	new_act<C>(42);

	const int OUTER_ITERATIONS = 5;
	const int INNER_ITERATIONS = 50000;

	double time = measure_time(OUTER_ITERATIONS, [=]()
	{
		vector<my_string_new> vec;
		for (int i = 0; i < INNER_ITERATIONS; ++i)
			vec.push_back(my_string_new("hello"));
	});
	cout << "with move ctor: " << time << endl;
	time = measure_time(OUTER_ITERATIONS, [=]()
	{
		vector<my_string_old> vec;
		for (int i = 0; i < INNER_ITERATIONS; ++i)
			vec.push_back(my_string_old("hello"));
	});
	cout << "without move ctor: " << time << endl;
}

#pragma endregion

int main()
{
	auto_variables();
	//for_each_in();
	//decl_type_operator();
	//lambda_functions();
	//rvalue_references();

	return 0;
}