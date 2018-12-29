#pragma once

#include <string.h>
#include <stdlib.h>

#include <utility>

class my_string
{
private:
	char* buffer_  = nullptr;
	size_t length_ = 0;
public:
	my_string() = default;
	my_string(char const* pstr) : buffer_(_strdup(pstr)), length_(strlen(pstr))
	{
	}
	my_string(my_string const& rhs)
	{
		*this = rhs;
	}
	my_string(my_string&& rhs)
	{
		*this = std::move(rhs);
	}

	my_string& operator=(my_string const& rhs)
	{
		if (this != &rhs)
		{
			destroy_buffer();
			buffer_ = _strdup(rhs.buffer_);
			length_ = rhs.length_;
		}
		return *this;
	}
	my_string& operator=(my_string&& rhs)
	{
		// This is a more compact version of what is presented on the slides.
		// We can use std::swap here because the destructor deletes the buffer
		// anyway. Effectively, we steal the buffer from the temporary and give
		// the temporary our buffer -- which will be freed very soon because
		// the temporary is about to die. If you are uncomfortable with this,
		// go ahead and use the slightly more verbose version, commented below.
		std::swap(buffer_, rhs.buffer_);
		std::swap(length_, rhs.length_);

		/*
		if (this != &rhs)
		{
			destroy_buffer();
			buffer_ = rhs.buffer_;
			length_ = rhs.length_;
			rhs.buffer_ = nullptr;
			rhs.length_ = 0;
		}
		*/

		return *this;
	}

	char operator[](size_t index) const
	{
		return buffer_[index];
	}
	char& operator[](size_t index)
	{
		return buffer_[index];
	}
	size_t length() const
	{
		return length_;
	}
	char const* str() const
	{
		return buffer_;
	}

	~my_string()
	{
		destroy_buffer();
	}
private:
	void destroy_buffer()
	{
		if (buffer_ != nullptr)
		{
			free(buffer_);
			buffer_ = nullptr;
			length_ = 0;
		}
	}
};

my_string get_name()
{
	return "Dave";
}

void strings()
{
	my_string s1{ "Hello" };
	my_string s2{ "World" };

	my_string s3{ s1 };				// copy
	my_string s4{ get_name() };		// move
	my_string s5{ std::move(s2) };	// forced move, don't use s2 anymore

	s1 = s3;			// copy
	s1 = get_name();	// move
	s5 = std::move(s1);	// forced move, don't use s1 anymore
}