#include <string.h>
#include <iostream>

#include "animal.h"

using namespace std;

/*--------------------------------------------------------------------------------*/


Animal::Animal() : m_id(0)      //ctor
{
	createName("");
}


Animal::~Animal()    //dtor
{   		  	
	delete[](m_name);
	m_name = NULL;   
}


Animal::Animal(const char* _name, int _id) :  m_id(_id)   //ctor
{
	createName(_name);
}


Animal::Animal(const Animal& _animalToCpy) : m_id(_animalToCpy.m_id)   //copy ctor
{
	createName( _animalToCpy.m_name  );
}


Animal& Animal::operator=(const Animal& _animal)   //operator= 
{	
	if(&_animal != this){	
		//m_id = _animal.m_id;
		
		delete[] m_name;	
		createName(_animal.m_name);
	}
	
	return *this;
}


/*--------------------------------------------------------------------------------*/


void Animal::createName(const char* _str)    //private method 
{		
	if(_str){
		m_name = new char[ strlen(_str) + 1]; 
		strcpy(m_name, _str);
	}else{
		m_name = new char[1];
		*m_name = '\0';
	}
}



/*--------------------------------------------------------------------------------*/


bool Animal::operator==(const Animal& _toComp) const
{
	if ( m_id == _toComp.m_id){
		return true;
	}else{
		return false;
	}
}



bool Animal::operator>(const Animal& _toComp) const
{
	if ( m_id > _toComp.m_id){
		return true;
	}else{
		return false;
	}
	
}

/*--------------------------------------------------------------------------------*/


void Animal::Show() const
{
	cout << " name : " << m_name << "   id : " << m_id ;
}

/*--------------------------------------------------------------------------------*/

void Animal::MakeSound() const
{
	cout << "baaaaaaaaaaaaaaaa" << endl;
}		
	
	
/*--------------------------------------------------------------------------------*/

	
void Animal::setName(const char* _name)
{
	delete[] m_name;
	createName(_name);
}
	
/*--------------------------------------------------------------------------------*/	
	

	
	
	
	
	
	
	
	

