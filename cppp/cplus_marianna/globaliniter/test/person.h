/**************************************************************************************
    Author: Marianna Shvartsman
    Creation date :      2013-11-15
    Last modified date: 2013-11-15
    Description : Person declaration
***************************************************************************************/
#ifndef __PERSON_H__
#define __PERSON_H__
#include <iostream>

class Person
{
	
public:
	void	GetName() { std::cout << "My name "<< m_name << std::endl; }
	void	SetName(const std::string& _name){ m_name = _name;}
	Person():m_name("Marianna"){ std::cout << "Person created" << std::endl;}
private:
	std::string m_name;

	Person(const Person&);
};

#endif

