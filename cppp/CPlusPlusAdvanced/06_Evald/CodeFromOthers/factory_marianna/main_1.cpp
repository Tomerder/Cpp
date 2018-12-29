/**************************************************************************************
    Author: Marianna Shvartsman
    Creation date :      2013-12-10
    Last modified date: 2013-12-10 
    Description : Serialize Factory
***************************************************************************************/
#include <fstream>
#include <iostream>
#include <string>
#include "factory.h"
using namespace std;

//DEFINITIONS
class Person 
{
public:
	Person(char* _name, size_t _age);
	Person(istream& _s);
	virtual void PrintPerson()const;
	
private:
	string m_name;
	size_t m_age;

	friend ostream& operator<<(ostream& _o, const Person& _p);
};


class Student: public Person
{
public:
	Student(char* _name, size_t _age,char* _school);
	Student(iostream _s);
	
	virtual void PrintPerson()const;
private:
	string m_school;

	friend ostream& operator<<(ostream& _o,const Student& _s);
};

ostream& operator<<(ostream& _o, const Person& _p);
ostream& operator<<(ostream& _o,const Student& _s);


//IMPLEMENTATION
Person::Person(char* _name, size_t _age):
m_name(_name), m_age(_age){}

Person::Person(istream& _s)
{
	_s >> m_name;
	_s.get();
	_s >> m_age;
	_s.get();
}

void Person::PrintPerson()const
{
	cout << "Name " << m_name << "\tage " << m_age << endl ;

}
ostream& operator<<(ostream& _os, const Person& _p)
{
cout << _p.m_name.size() << endl;
	return _os << _p.m_name << '\n'
			   << _p.m_age << '\n';
}


Student::Student(char* _name, size_t _age,char* _school):
Person(_name, _age), m_school(_school){}

Student::Student(iostream _s):Person(_s)
{
	_s >> m_school;
	_s.get();
}


void Student::PrintPerson()const
{
	Person::PrintPerson();
	cout << "\tschool " << m_school << endl; 
}


ostream& operator<<(ostream& _o,const Student& _stud)
{
	
	operator<<(_o,static_cast<Person>(_stud));
	_o << _stud.m_school << '\n';

}


int main()
{
	Factory<Person> f;
	Person p("Marianna",28);
	p.PrintPerson();
	filebuf fb;
	fb.open ("test.txt",std::ios::out);
	ostream os(&fb);
	f.Serialize(&p,os);
	fb.close();
	fb.open ("test.txt",std::ios::in);
	istream is(&fb);	
	shared_ptr<Person> m = f.Create(is);
	fb.close();

	m->PrintPerson();
	system("pause");
	return 0;
}