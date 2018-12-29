#pragma once

#include <future>
#include <thread>
#include <memory>

struct calculator
{
	int value_;
	void set_value(int value)
	{
		value_ = value;
	}
	void calculate()
	{
		std::this_thread::sleep_for(std::chrono::seconds(value_));
	}
};

void calculate_async()
{
	std::unique_ptr<calculator> ptr(new calculator);
	ptr->set_value(2);

	// The lambda takes the object by moving. Copying is prohibited for smart_ptr, and
	// we can't take a reference because it's a local object and will die before the 
	// lambda completes.
	std::thread t([ptr = std::move(ptr)]() {
		ptr->calculate();
	});
	t.detach();
}

void calculate_async_cpp11()
{
	std::unique_ptr<calculator> ptr(new calculator);
	ptr->set_value(17);

	std::thread t(std::bind([](std::unique_ptr<calculator> const& ptr) 
	{
		ptr->calculate();
	}, std::move(ptr)));
	t.detach();
}
