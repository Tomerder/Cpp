/**************************************************************************************
    Author: Marianna Shvartsman
    Creation date :      2013-11-10
    Last modified date: 2013-11-10
    Description : Sheared pointer implementation
***************************************************************************************/
#include <iostream>
#include <string>
#include "sharedptr.h"
using namespace std;
using namespace m7;


class Person
{
	public:
		Person (const string& _name);
		virtual ~Person ();

		virtual void	SayHello()const;
	protected:
		string m_name;
};


class Student: public Person 
{
	public:
		Student (const string& _name, size_t _grade);
		virtual ~Student ();

		virtual void	SayHello()const;
	private:
		size_t m_grade;
};

Person::Person(const string& _name): m_name(_name)
{
	cout << "Person\t" << m_name << "\tcreated"<< endl;
}

Person::~Person()
{
	cout << "Person\t" << m_name <<"\t\tdestroyed" << endl;
}

void Person::SayHello()const
{
	cout << "Hello I'm person\t"<< m_name <<endl;
}

Student::Student(const string& _name, size_t _grade):Person(_name), m_grade(_grade) {}

Student::~Student()
{
	cout << "Student\t" << m_name <<"\tgrade\t"<< m_grade <<"\tdestroyed" << endl;
}

void Student::SayHello()const
{
	cout << "Hello I'm student\t"<< m_name << "\tmy grade is "<< m_grade << endl;
}


int main()
{
	SharedPtr<Person> personPtr1 (new Person ((string("Marianna"))));
	SharedPtr<Person> personPtr2(personPtr1);
	SharedPtr<Person> personPtr3(new Person (string("Emily")));
	personPtr1 = personPtr3;
	personPtr1->SayHello();
	(*personPtr2).SayHello();
	cout << "Is shared " << personPtr1.IsShared() << endl;
	SharedPtr<Person> studentPtr1(new Student(string ("Pavel"),98));
	personPtr1 = studentPtr1;
	SharedPtr<Student> studentPtr2(new Student(string("Dor"),95));
	SharedPtr<Person> personPtr4(studentPtr2);
	return 0;
}

