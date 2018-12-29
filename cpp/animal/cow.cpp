#include <string.h>
#include <iostream>

#include "cow.h"

using namespace std;


/*--------------------------------------------------------------------------------*/

int Cow::m_numOfCows = MIN_ID;

/*--------------------------------------------------------------------------------*/

Cow::Cow()       //private ctor - will never be called !!!
{
}


Cow::~Cow()    //dtor
{   		  	 
}


Cow::Cow(const char* _name, int _id) : Animal(_name, _id)   //private ctor
{	
	m_milkAllowed = 0;
}

Cow::Cow(const char* _name, int _id, int _milkAllowed ) : Animal(_name, _id)   //private ctor
{	
	m_milkAllowed = _milkAllowed;
}


Cow::Cow(const Cow& _cowToCpy) : Animal(_cowToCpy)   //private copy ctor - will never be called !!!
{
}

/*--------------------------------------------------------------------------------*/


void Cow::Show() const
{
	cout << "COW =>"; 
	Animal::Show();
	cout << "    quantity of milk allowed : " <<  m_milkAllowed  << endl; 
}

/*--------------------------------------------------------------------------------*/

void Cow::MakeSound() const
{
	cout << "Moooooooo Mooooooooo" << endl;
}		
	
	
/*--------------------------------------------------------------------------------*/


Cow* Cow::createInstance(const char* _name)
{
	if( m_numOfCows > MAX_ID ){
		cout << "can not create anymore Cows !!!!!!!!!!!!!!!!!" << endl;
		return NULL;
	}	
	
	Cow* cow = new Cow(_name, m_numOfCows++ );
	return cow;
}
	
	
Cow* Cow::createInstance(const char* _name, int _milkAllowed)
{
	if( m_numOfCows > MAX_ID ){
		cout << "can not create anymore Cows !!!!!!!!!!!!!!!!!" << endl;
		return NULL;
	}	
	
	Cow* cow = new Cow(_name, m_numOfCows++ , _milkAllowed);
	return cow;
}	
	
/*--------------------------------------------------------------------------------*/	
	
	
	
	

