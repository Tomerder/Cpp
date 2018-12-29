/**************************************************************************************
    Author: Marianna Shvartsman
    Creation date :      2013-11-14
    Last modified date: 2013-11-14#
    Description : singleton main
***************************************************************************************/
#include <iostream>
#include <string>
using namespace std;

#include "singleton.h"
#define	PERSON	Singleton<Person>::Instance()

class Person
{
	friend class Singleton<Person>;
public:
	void	GetName() { cout << "My name "<< m_name << endl; }
	void	SetName(const string& _name){ m_name = _name;}
private:
	string m_name;
	Person():m_name("Marianna"){ cout << "Person created" << endl;}
	Person(const Person&);
};

int main()
{
	Singleton<Person>::Instance().GetName();
	PERSON.GetName();
	return 0;
}

