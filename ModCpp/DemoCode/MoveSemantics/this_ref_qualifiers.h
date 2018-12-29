#pragma once

#include <iostream>

class counter
{
private:
	size_t count_;
public:
	counter& operator++() &
	{
		++count_;
		return *this;
	}
	counter operator++(int)
	{
		auto copy(*this);
		++count_;
		return copy;
	}
	explicit operator size_t() const
	{
		return count_;
	}
};

counter get_counter()
{
	counter c;
	++c;
	return c;
}

void using_counter()
{
	std::cout << static_cast<size_t>(get_counter()) << std::endl;

	// error C2678: binary '++': no operator found which takes a left-hand operand of type 'counter' (or there is no acceptable conversion)
	// ++get_counter();
}
