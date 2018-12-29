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

struct company
{
	std::vector<employee> employees;
	std::map<employee, double> salaries;

	company() = default;
	company(company&& rhs) :
		employees(std::move(rhs.employees)),
		salaries(std::move(rhs.salaries))
	{
	}
	company(company const&) = delete;
	company& operator=(company&& rhs)
	{
		if (this != &rhs)
		{
			employees = std::move(rhs.employees);
			salaries = std::move(rhs.salaries);
		}
		return *this;
	}
	company& operator=(company const&) = delete;
};

struct director
{
	std::string name;
	double bonus;

	director() = default;
	director(director const&) = default;
	director(director&& rhs) :
		name(std::move(rhs.name)),
		bonus(rhs.bonus)
	{
	}
	director& operator=(director const&) = default;
	director& operator=(director&& rhs)
	{
		if (this != &rhs)
		{
			name = std::move(rhs.name);
			bonus = rhs.bonus;
		}
		return *this;
	}
};

struct public_company : public company
{
	std::vector<director> directors;

	public_company() = default;
	public_company(public_company&& rhs) :
		company(std::move(rhs)),
		directors(std::move(rhs.directors))
	{
	}
	public_company(public_company const&) = delete;
	public_company& operator=(public_company&& rhs)
	{
		if (this != &rhs)
		{
			company::operator=(std::move(rhs));
			directors = std::move(rhs.directors);
		}
		return *this;
	}
	public_company& operator=(public_company const&) = delete;
};

struct stock_exchange
{
	std::map<std::string, public_company> registered_companies;

	void register_company(std::string const& name, public_company comp)
	{
		registered_companies[name] = std::move(comp);
	}
};

int main()
{
	return 0;
}