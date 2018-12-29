#pragma once

#include <string>
#include <unordered_map>
#include <map>
#include <regex>
#include <iostream>

struct employee_record
{
	int id_;
	std::string name_;
	std::string department_;
};

namespace std
{
	template <>
	struct hash<employee_record>
	{
		size_t operator()(employee_record const& emp) const
		{
			return emp.id_;
		}
	};

	template <>
	struct equal_to<employee_record>
	{
		bool operator()(employee_record const& lhs, employee_record const& rhs) const
		{
			return lhs.id_ == rhs.id_;
		}
	};


	// for map
	template <>
	struct less<employee_record>
	{
		bool operator()(employee_record const& lhs, employee_record const& rhs) const
		{
			return lhs.id_ < rhs.id_;
		}
	};
}

void hashers()
{
	std::unordered_map<employee_record, double> salaries;


	employee_record dave;
	salaries[dave] = 12000.0;


	std::map<employee_record, double> salaries_map;

	employee_record bill;
	salaries_map[bill] = 8.000;
}

void regexes()
{
	// Source: http://www.regexlib.com/REDetails.aspx?regexp_id=981
	std::regex r{ R"(^(([0-1]?[0-9])|([2][0-3])):([0-5]?[0-9])(:([0-5]?[0-9]))?$)" };
	std::initializer_list<std::string> test_cases{
		"12:15",
		"13:00:05",
		"24:10",
		"11:02:60"
	};
	for (auto const& test : test_cases)
	{
		std::cout << test << (std::regex_match(test, r) ? " matches" : " doesn't match") << "\n";
	}
}