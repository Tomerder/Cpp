/**************************************************************************************
    Author: Marianna Shvartsman
    Creation date :      2013-12-10
    Last modified date: 2013-12-10 
    Description : Serialize
***************************************************************************************/
#ifndef __SERIALIZE_FACTORY_H__
#define __SERIALIZE_FACTORY_H__

#include <iostream>
#include <map>
#include <memory>

//DESCRIPTION: class Factory provide service of serialization and deserialization of objects to stream:
//			   creates objects of type T by the given (istream) input,
//			   serialize objects to the stream
//USAGE EXAMPLE:
//				Factory f;
//				Person p;
//				Person* stud = new Student;
//				f.Add<Student>();
//				fstream file;
//				f.Serialize(stud, file);
//				shared_ptr<Person> studentBackUp = f.Create(file);

//****************************************************************
//	DEFINITION
//****************************************************************
template <class T>
class Factory
{
public:
	shared_ptr<T> Create (std::istream& _s);
	template <class C>
	void Add(shared_ptr<T> (*_creator)(std::istream&) = Creator<C>) ;

	void Serialize(T* _t, std::ostream& _o);
private:
	map<string, shared_ptr<T> (*)(std::istream&)>  m_map;

	template <class A>
	static shared_ptr<T> Creator<A>(std::istream& _o);

};

//*****************************************************************
//	Implementation
//*****************************************************************
template <class T>
template <class A>
shared_ptr<T> Factory<T>::Creator<A>(std::istream& _o)
{
	shared_ptr<T> ptr(new A(_o));
	return ptr;
}

template <class T>
shared_ptr<T> Factory<T>::Create (std::istream& _s);

template <class T>
template <class C>
void Factory<T>::Add(shared_ptr<T> (*_creator)(std::istream&) = Creator<C>);

template <class T>
void Factory<T>::Serialize(T* _t, std::ostream& _o)
{
	string name = type_id(*_t).name();
	_o << name.size() << ";" << name << ";" << *_t;
}

#endif //__SERIALIZE_FACTORY

