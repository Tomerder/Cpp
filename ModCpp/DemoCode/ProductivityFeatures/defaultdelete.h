#pragma once

#include <iostream>

template <typename T>
class smart_ptr
{
private:
	T* ptr_;
public:
	smart_ptr(T* ptr) : ptr_(ptr)
	{
	}
	smart_ptr(smart_ptr const&) = delete;
	smart_ptr& operator=(smart_ptr const&) = delete;
	T* operator->()
	{
		return ptr_;
	}
	T& operator*()
	{
		return *ptr_;
	}
	T const& operator*() const
	{
		return *ptr_;
	}
	~smart_ptr()
	{
		delete ptr_;
	}
};

struct complex
{
	double real_ = 0.0, imag_ = 0.0;
	
	complex(double r, double i) : real_(r), imag_(i)
	{
	}
	complex() = default;
	complex operator+(complex const& rhs)
	{
		complex temp(*this);
		temp.real_ += rhs.real_;
		temp.imag_ += rhs.imag_;
		return temp;
	}

private:
	// Copyable, but only from within the class
	complex(complex const&) = default;
	complex& operator=(complex const&) = default;
};

void defaulted_and_deleted_ctors()
{
	smart_ptr<int> p(new int(0));
	*p = 42;

	// error C2280: 'smart_ptr<int>::smart_ptr(const smart_ptr<int> &)': attempting to reference a deleted function
	// smart_ptr<int> p2(p);
}

void print(long);
void print(short) = delete;

template <typename T>
void print_ptr(T* ptr)
{
	std::cout << *ptr << std::endl;
}

template <>
void print_ptr<void>(void*) = delete;

void print_something()
{
	int x = 42;
	int* p = &x;
	print_ptr(p);

	void* p2 = p;
	// error C2280: 'void print_ptr<void>(void *)': attempting to reference a deleted function
	// print_ptr(p2);
}