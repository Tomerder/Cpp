#pragma once

struct employee
{
	virtual void work()
	{
	}
};

struct manager : public employee
{
	virtual void work() override
	{
	}

	// error C3668: 'manager::sleep': method with override specifier 'override' did not override any base class methods
	// virtual void sleep() override {}
};

struct big_boss final : public manager
{
	virtual void work() override
	{
	}
};

// error C3246: 'ceo': cannot inherit from 'big_boss' as it has been declared as 'final'
// struct ceo : public big_boss
// {
// };

struct director : public manager
{
	virtual void work() override final
	{
	}
};

struct hr_director : public director
{
	// error C3248: 'director::work': function declared as 'final' cannot be overridden by 'hr_director::work'
	// virtual void work() override {}
};