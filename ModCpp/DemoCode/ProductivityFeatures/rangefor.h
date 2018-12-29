#pragma once

#include <vector>
#include <iterator>
#include <iostream>
#include <map>
#include <string>

void range_for()
{
	std::vector<int> numbers{ 1,2,3 };
	for (int n : numbers)
	{
		std::cout << n << std::endl;
	}
	for (auto n : numbers)
	{
		std::cout << n << std::endl;
	}

	std::map<std::string, double> salaries{ { "Dave", 90000 },{ "Mike", 45000 },{ "Kate", 120000 } };
	for (auto kv : salaries)
	{
		// 'kv' is std::pair<std::string const, double>
	}
	for (auto& kv : salaries)
	{
		// 'kv' is std::pair<std::string const, double>&
		kv.second *= 1.03;
	}
	for (auto const& kv : salaries)
	{
		// 'kv' is std::pair<std::string const, double> const&
		std::cout << kv.second << std::endl;
	}
}

// Imagine that this class is part of a library that you cannot modify
template <typename T>
class simple_stack
{
public:
	struct node
	{
		node* next_;
		T value_;
	};
private:
	node* head_ = nullptr;
public:
	node* head() const
	{
		return head_;
	}
	void push(T const& t)
	{
		node* n = new node;
		n->next_ = head_;
		n->value_ = t;
		head_ = n;
	}
	bool pop(T& t)
	{
		if (head_ == nullptr)
		{
			return false;
		}
		node* n = head_;
		t = n->value_;
		head_ = n->next_;
		delete n;
		return true;
	}
};

// The iterator class and the std::begin/std::end overloads are provided by you
template <typename T>
class stack_iterator : public std::iterator<std::forward_iterator_tag, T>
{
private:
	typedef typename simple_stack<T>::node node_t;
	node_t* current_;
public:
	stack_iterator(node_t* current = nullptr) : current_(current)
	{
	}
	T& operator*()
	{
		return current_->value_;
	}
	stack_iterator& operator++()
	{
		if (current_ != nullptr)
		{
			current_ = current_->next_;
		}
		return *this;
	}
	bool operator!=(stack_iterator const& other) const
	{
		return current_ != other.current_;
	}
};

namespace std
{
	template <typename T>
	stack_iterator<T> begin(simple_stack<T>& stack)
	{
		return stack_iterator<T>(stack.head());
	}
	
	template <typename T>
	stack_iterator<T> end(simple_stack<T>&)
	{
		return stack_iterator<T>();
	}
}

void use_stack_range_for()
{
	simple_stack<int> stack;
	stack.push(1);
	stack.push(2);
	stack.push(3);

	for (auto n : stack)
	{
		std::cout << n << std::endl;
	}
}