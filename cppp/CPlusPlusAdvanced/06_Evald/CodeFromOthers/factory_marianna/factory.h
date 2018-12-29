/**************************************************************************************
    Author: Marianna Shvartsman
    Creation date :      2013-12-10
    Last modified date: 2013-12-10 
    Description : Serialize Factory
***************************************************************************************/
#ifndef __SERIALIZE_FACTORY_H__
#define __SERIALIZE_FACTORY_H__

#include <iostream>
#include <map>
#include <string>
#include <memory>


//DESCRIPTION: class Factory provide service of serialization and deserialization of objects:
//			   creates objects of type T by the given (istream) input,
//			   or serialize objects to the stream
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
//REQUIREMENTS to T class:
//				CTOR from istream
//				Public CTOR or Factory class should be friend
//				operator <<()
//				
template <class T> 
class Factory
{
public:
	typedef T* (*CreatorFunc)(std::istream&);

	shared_ptr<T> Create(std::istream& _s);
	template <class C> //C is Derived class T
	void Add(CreatorFunc _cFunc = Creator<C>) ;

	void Serialize(T* _t, std::ostream& _o)const;
private:
	typedef std::map<string,CreatorFunc> RecognizeMap; 
	
	RecognizeMap m_map;

	template <class C>
	static T* Creator(std::istream& _o);
	
	static std::string TypeRecognizer(std::iostream& _s);

};

//*****************************************************************
//	Implementation
//*****************************************************************

template <class T>
shared_ptr<T> Factory<T>::Create(std::istream& _s)
{

	string type = TypeRecognizer(_s);

	typename RecognizeMap::iterator itr = m_map.find(type);

	if(itr == m_map.end())
	{
		throw "Trying to build object by Factory whith wrong type";
	}
	shared_ptr<T> shp(itr->second(_s));
	return shp;
}
//-------------------------------------------------------------
template <class T>
template <class C>
void Factory<T>::Add(CreatorFunc _cFunc = Creator<C>)
{
	T t;
	m_map.insert(type_id(t).name(), _cFunc );
}
//-------------------------------------------------------------
template <class T>
void Factory<T>::Serialize(T* _t, std::ostream& _o)const
{
	assert(_t);

	std::string type = type_id(*_t).name();
	_o << type.size() << "\n" << type << "\n" << *_t;
}
//-------------------------------------------------------------

template <class T>
template <class C>
T* Factory<T>::Creator(std::istream& _o)
{	
	return new C(_o);
}
//-------------------------------------------------------------

template <class T>
std::string Factory<T>::TypeRecognizer(std::iostream& _s)
{

	int size;
	_s >> size;
	if(_s.fail())
	{
		throw "Can't create, bad serialization";
	}
	_s.get(); //skip delimiter
	string type(size,0);
	_s >> type;
	if(_s.fail())
	{
		throw "Can't create, bad serialization";
	}
	_s.get(); //skip delimiter
		
	return string(type);
}
//-------------------------------------------------------------

#endif //__SERIALIZE_FACTORY

