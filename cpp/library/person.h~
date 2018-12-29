/**************************************************************************************
    Author : Tomer Dery
    Creation date :      16.01.14
    Date last modified : 16.01.14 
    Description : Library 
***************************************************************************************/
#ifndef __PERSON_H__
#define __PERSON_H__

#include <string>
#include <iostream>
using namespace std;


class Person{ 

private: 	
	const unsigned int m_id;
	string m_name;
	string m_address;	
	unsigned int m_age;
	
	/*not allowed*/
	Person& operator=(const Person& _person);	

protected:
	Person(const Person& _person)
		: m_id(_person.m_id), m_name(_person.m_name), m_address(_person.m_address) , m_age(_person.m_age) {}

public: 	
	Person(unsigned int _id, const string& _name="", const string& _address="", unsigned int _age=0) : 
					m_id(_id), m_name(_name), m_address(_address) ,m_age(_age){}
		
	virtual ~Person() {}	
	
	unsigned int getId() const {return m_id;}
	const string& getAddress() const {return m_address;}
	const string& getName() const {return m_name;}
	unsigned int getAge() const {return m_age;}

	void incAge() {++m_age;} 
	void setName(const string& _name) { m_name = _name;} 
	void setAddress(const string& _address) { m_address = _address;} 
	
	virtual void Print() const {cout << "PERSON- id: " <<  m_id << " , name: " <<  m_name << endl ;} 
};
	
	
#endif /*__PERSON_H__*/


