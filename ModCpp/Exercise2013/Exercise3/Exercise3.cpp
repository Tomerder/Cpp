#include <vector>
#include <map>

struct employee
{
	std::string name;
	std::vector<double> salary_history;

	employee()
	{
	}
	employee(employee const& rhs) : name(rhs.name), salary_history(rhs.salary_history)
	{
	}
	employee(employee&& rhs) : name(std::move(rhs.name)), salary_history(std::move(rhs.salary_history))
	{
	}
	employee& operator=(employee const& rhs)
	{
		if (this != &rhs)
		{
			name = rhs.name;
			salary_history = rhs.salary_history;
		}
		return *this;
	}
	employee& operator=(employee&& rhs)
	{
		if (this != &rhs)
		{
			name = std::move(rhs.name);
			salary_history = std::move(rhs.salary_history);
		}
		return *this;
	}
};

// TODO 1
//	Follow the example of the 'employee' class and add move construction and move assignment
//	support to the 'company' class. Remove the ability to copy or copy-assign the 'company'
//	class, so that it's only moveable and not copyable.
struct company
{
	company() {}
	company(company& other) = delete;
	company& operator=(company& other) = delete;

	company& operator=(company&& rhs)
	{
		if (this != &rhs)
		{
			employees = std::move(rhs.employees);
			salaries = std::move(rhs.salaries);
		}
		return *this;
	}

	company(company&& rhs)
	{
		*this = std::move(rhs);
	}


	std::vector<employee> employees;
	std::map<employee, double> salaries;
};

// TODO 2
//	Follow the example of the 'employee' class and add a copy ctor, copy assignment operator,
//	move constructor, and move assignment operator to the 'director' class. Note that the 'bonus'
//	field is a double, and doesn't have to be moved.
struct director
{
	std::string name;
	double bonus;

	director()
	{
	}
	director(director const& rhs) : name(rhs.name), bonus(rhs.bonus)
	{
	}

	director(director&& rhs) : name(std::move(rhs.name)), bonus(rhs.bonus)
	{
	}
	director& operator=(director const& rhs)
	{
		if (this != &rhs)
		{
			name = rhs.name;
			bonus = rhs.bonus;
		}
		return *this;
	}
	director& operator=(director&& rhs)
	{
		if (this != &rhs)
		{
			name = std::move(rhs.name);
			bonus = std::move(rhs.bonus); /* no need for move, but better readbility */
		}
		return *this;
	}
};

// TODO 3
//	Add move construction and move assignment support to the 'public_company' class.
//	Make sure to invoke the move constructor and move assignment operator of the base class,
//	'company'. This class should also prevent copy construction and copy assignment, like
//	the base class 'company'.
struct public_company : public company
{
	public_company() {}

	public_company(public_company& other) = delete;
	public_company& operator=(public_company& other) = delete;

	public_company(public_company&& rhs) : company(std::move(rhs))
	{
		*this = std::move(rhs);
	}

	public_company& operator=(public_company&& rhs)
	{
		if (this != &rhs)
		{
			company::operator=(std::move(rhs));
			directors = std::move(rhs.directors);
		}
		return *this;
	}

	std::vector<director> directors;
};

struct stock_exchange
{
	std::map<std::string, public_company> registered_companies;

	void register_company(std::string const& name, public_company comp)
	{
		// TODO 4
		//	Insert 'comp' to the map of registered companies. Note that because 'public_company'
		//	is not copyable, you'd have to move it into the map instead of copying.

		registered_companies[name] = std::move(comp);
	}
};

int main()
{
	return 0;
}