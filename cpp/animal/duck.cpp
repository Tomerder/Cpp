#include <string.h>
#include <iostream>

#include "duck.h"

using namespace std;


/*--------------------------------------------------------------------------------*/

int Duck::m_numOfDucks = MIN_ID;

/*--------------------------------------------------------------------------------*/

Duck::Duck()       //private ctor - will never be called !!!
{
}


Duck::~Duck()    //dtor
{   		  	 
}


Duck::Duck(const char* _name, int _id) : Animal(_name, _id)   //private ctor
{	
	m_numOfLittleDucks = 0;
}

Duck::Duck(const char* _name, int _id, int _numOfLittleDucks) : Animal(_name, _id)   //private ctor
{	
	m_numOfLittleDucks = _numOfLittleDucks;
}

Duck::Duck(const Duck& _cowToCpy) : Animal(_cowToCpy)   //private copy ctor - will never be called !!!
{
}

/*--------------------------------------------------------------------------------*/


void Duck::Show() const
{
	cout << "DUCK =>";  
	Animal::Show();
	cout << "    number of little ducks : " <<  m_numOfLittleDucks << endl; 
}

/*--------------------------------------------------------------------------------*/

void Duck::MakeSound() const
{
	cout << "Gaaaaaaaaa Gaaaaaaaaaa" << endl;
}		
	
	
/*--------------------------------------------------------------------------------*/


Duck* Duck::createInstance(const char* _name)
{
	if( m_numOfDucks > MAX_ID ){
		cout << "can not create anymore Ducks !!!!!" << endl;
		return NULL;
	}	
	
	Duck* duck = new Duck(_name, m_numOfDucks++ );
	return duck;
}
	
	

Duck* Duck::createInstance(const char* _name, int _numOfLittleDucks)
{
	if( m_numOfDucks > MAX_ID ){
		cout << "can not create anymore Ducks !!!!!" << endl;
		return NULL;
	}	
	
	Duck* duck = new Duck(_name, m_numOfDucks++ , _numOfLittleDucks);
	return duck;
}
	
/*--------------------------------------------------------------------------------*/		
	
	
	
	
	
	

