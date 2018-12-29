/**************************************************************************************
    Author : Tomer Dery
    Creation date :      28.12.13
    Date last modified : 28.12.13
    Description : animals
***************************************************************************************/
#ifndef __DUCK_H__
#define __DUCK_H__

#include "animal.h"


class Duck : public Animal {

private: 
	enum{MIN_ID=2001, MAX_ID=3000};
	static int m_numOfDucks;
		
	int m_numOfLittleDucks;
protected:	
	Duck();    //private Ctor
	Duck(const char* _name, int _id);   //private Ctor
	Duck(const char* _name, int _id , int _numOfLittleDucks);   //private Ctor
	Duck(const Duck& _cowToCpy);   //private Copy Ctor
	Duck& operator=(const Duck& _duck);  
	
public: 	
	virtual ~Duck();
	
	static Duck* createInstance(const char* _name);  //method of creating objects
	static Duck* createInstance(const char* _name, int _numOfLittleDucks);
		
	virtual void Show() const;
	virtual void MakeSound() const;	
	
	virtual int getNumOfAnimalsCreated() const{    return ( m_numOfDucks - MIN_ID);   } 
	virtual int getNumOfAnimalsLeftToCreate() const{    return ( MAX_ID - m_numOfDucks + 1);   } 
	
		
	void setNumOfLittleDucks(int _numOfLittleDucks) {m_numOfLittleDucks = _numOfLittleDucks;}
	int getNumOfLittleDucks() const {return m_numOfLittleDucks;}
};


	
#endif /*__DUCK_H__*/


