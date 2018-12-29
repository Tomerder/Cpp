#include <string.h>
#include <iostream>

#include "chicken.h"

using namespace std;


/*--------------------------------------------------------------------------------*/

int Chicken::m_numOfChickens = MIN_ID;

/*--------------------------------------------------------------------------------*/

Chicken::Chicken()       //private ctor - will never be called !!!
{
}


Chicken::~Chicken()    //dtor
{   		  	 
}


Chicken::Chicken(const char* _name, int _id) : Animal(_name, _id)   //private ctor
{	
	m_numOfEggs = 0;
}

Chicken::Chicken(const char* _name, int _id, int _numOfEggs) : Animal(_name, _id)   //private ctor
{	
	m_numOfEggs = _numOfEggs;
}

Chicken::Chicken(const Chicken& _chickenToCpy) : Animal(_chickenToCpy)   //private copy ctor - will never be called !!!
{
}

/*--------------------------------------------------------------------------------*/


void Chicken::Show() const
{
	cout << "CHICKEN =>";  
	Animal::Show();
	cout << "    number of eggs : " <<  m_numOfEggs << endl; 
}

/*--------------------------------------------------------------------------------*/

void Chicken::MakeSound() const
{
	cout << "KoooooKorikoooooo KoooooKorikoooooo" << endl;
}		
	
	
/*--------------------------------------------------------------------------------*/


Chicken* Chicken::createInstance(const char* _name)
{
	if( m_numOfChickens > MAX_ID ){
		cout << "can not create anymore Chickens !!!!!!!!!!!!!!!!!!!!!!" << endl;
		return NULL;
	}	
	
	Chicken* chicken = new Chicken(_name, m_numOfChickens++ );
	return chicken;
}
	


Chicken* Chicken::createInstance(const char* _name, int _numOfEggs )
{
	if( m_numOfChickens > MAX_ID ){
		cout << "can not create anymore Chickens !!!!!!!!!!!!!!!!!!!!!!" << endl;
		return NULL;
	}	
	
	Chicken* chicken = new Chicken(_name, m_numOfChickens++ ,_numOfEggs );
	return chicken;
}
	
/*--------------------------------------------------------------------------------*/		
	
	
	
	
	
	
	

