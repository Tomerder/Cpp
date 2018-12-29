#ifndef FACTORY_H
#define FACTORY_H

#include <tr1/memory>	//shared_ptr
#include <iostream>
#include <sstream>
#include <map>
#include <typeinfo>

// client must have a CTOR from stream, and a function Serialize().

// Code review(Evald):
// add comments about exceptions


template <class T>
class Factory
{
public:
	typedef std::tr1::shared_ptr<T> SharedT;
	
	SharedT Create(std::istream&);
	
	void Serialize(const T&, std::ostream&);
	
	template <class DERIVED>
	void Add();

private:
	template <class DERIVED>
	static SharedT Creator(std::istream& _name);
	
	std::map<const std::string, SharedT (*)(std::istream&) > m_map;
};

template <class T>
typename Factory<T>::SharedT Factory<T>::Create(std::istream& _is)
{
	int num = 0;
	_is >> num;
	char buffer[64];	//switch to vector<char> buffer(num), and then _is.read(&buffer[0], num).
						// do not do this trick with string. it's not null terminated. c_str() isn't good too
						// even though it's null terminated because it gives const pointer. 
	_is.read(buffer, num);

	typename std::map<const std::string, SharedT (*)(std::istream&) >::iterator it;
	it = m_map.find(buffer );

	if (it == m_map.end() )
	{
		throw "didn't find this type";	// throw something normal
	}
	

	_is >> num;
	// Add here _is.getchar() to get the seperator
	char* buff = new char[num];	// switch to vector - maybe stringstream will throw an exception.
	_is.read(buff, num);

	std::stringstream payload;
	payload.write(buff , num);
	
	delete buff;
	return it->second(payload);
}

template <class T>
void Factory<T>::Serialize(const T& _object, std::ostream& _os)
{
	std::string 		str;	//to measure size
	std::stringstream	stream;	//
	
	// put size of typename and typename into the ostream
	str = typeid(T).name();	
	_os << str.size();
	_os << str;

	// put size of serialize and serialize into the ostream
	_object.Serialize(stream);
	str = stream;
	
	// TODO - add a seperator for the case the client's data begins with a number. Seperate between numbers.
	
	_os << str.size();
	_os << str;
}

template <class T>
template <class DERIVED>
void Factory<T>::Add()
{
	// assert do not add something twice
	m_map.insert(typeid(DERIVED).name(), &Factory::Creator<DERIVED> );
}

template <class T>
template <class DERIVED>
typename Factory<T>::SharedT Factory<T>::Creator(std::istream& _str)
{
	return SharedT (new DERIVED(_str));
}


#endif	//#ifndef FACTORY_H


