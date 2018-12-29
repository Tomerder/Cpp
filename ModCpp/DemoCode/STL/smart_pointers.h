#pragma once

#include <memory>
#include <vector>
#include <iostream>
#include <string>

namespace unique_ptr_simple
{
	std::unique_ptr<std::string> get_name()
	{
		return std::make_unique<std::string>("My Name");
	}


	void test_unique_ptr()
	{
		std::unique_ptr<std::string> ptr(new std::string("hello"));
		ptr->substr(1, 2);

		std::vector<std::unique_ptr<std::string>> v;
		v.push_back(std::move(ptr));
		v.push_back(get_name());

		//error C2280 : : attempting to reference a deleted function	STL	smart_pointers.h
		//std::unique_ptr<std::string> ptr2 = v[0]; 
		std::unique_ptr<std::string> ptr2 = std::move(v[0]); // will move from the vector - be aware


	}

	// std::make_unique supported only in cpp14, so we can have our version 
	template <typename T, typename... Args>
	std::unique_ptr<T> make_unique_cpp11(Args&&... args)
	{
		return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
	}

}

namespace simple_shared_ptr
{
	struct print_when_destructed
	{
		~print_when_destructed()
		{
			std::cout << "destructed" << std::endl;
		}

	};


	void testmove(std::shared_ptr<print_when_destructed> ptr)
	{
	}

	void test_shared_ptr()
	{

		// counter == 0 , pointer will be deleted in the last destructor
		// counter updated is atomic, shared ptr is thread safe 
		std::shared_ptr<print_when_destructed> sp(new print_when_destructed());
		std::vector<std::shared_ptr<print_when_destructed>> vsp;
		vsp.push_back(sp);
		{
			auto sp2(sp);
		}
		sp = nullptr;
		vsp.clear();

		// use make shared to get better performance and use one memory block for your object and share ptr control block
		auto sp3 = std::make_shared<std::string>();
		auto sp4 = std::make_shared<std::string>("hello");
		auto sp5 = std::make_shared<std::string>('a', 7);

		testmove(std::move(sp));

	}
}



namespace ref_count_problem
{
	// forward declaration
	struct manager;

	struct employee
	{
		std::shared_ptr<manager> manager_;
	};

	struct manager
	{
		std::vector<std::shared_ptr<employee>> reports_;
	};

	void test_ref_count()
	{
		{
			// mike ref count 1
			auto mike = std::make_shared<employee>();
			// kate ref count 1
			auto kate = std::make_shared<manager>();

			// kate ref count 2
			kate->reports_.push_back(mike);
			// mike ref count 2
			mike->manager_ = kate;
		}
		//after scope block, kate ref count --, so its 1, same for mike. 
		//We lost the vars and we have dangling rec cout issue
	}
}

namespace weak_ptr_solution
{

	// forward declaration
	struct manager;

	struct employee
	{
		std::weak_ptr<manager> manager_;

		void take_vacation()
		{
			if (manager_.expired())
			{
				// will return it as shared_ptr if exist
				// counter ++, if not expired 
				std::shared_ptr<manager> p = manager_.lock();

				if (p)
				{
					// will work if in cpp file, forward declaration is not enough here.
					// for expository purposes, commented out

					//p->ask_for_vacation();
				}
			}
		}
	};

	struct manager
	{
		void ask_for_vacation()
		{

		}
		std::vector<std::shared_ptr<employee>> reports_;
	};

	void weak_explained()
	{
		auto mike = std::make_shared<employee>();
		auto kate = std::make_shared<manager>();

		kate->reports_.push_back(mike);

		// you can assign shared to weak, there is conversion supported
		mike->manager_ = kate;

		mike = nullptr; // still referenced by kate->reports_
		kate = nullptr; // both objects are reclaimed
	}

}

