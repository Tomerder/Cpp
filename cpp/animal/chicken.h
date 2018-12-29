/**************************************************************************************
    Author : Tomer Dery
    Creation date :      28.12.13
    Date last modified : 28.12.13
    Description : animals 
***************************************************************************************/
#ifndef __CHICKEN_H__
#define __CHICKEN_H__

#include "animal.h"


class Chicken : public Animal {

private: 
	enum{MIN_ID=1001, MAX_ID=2000};
	static int m_numOfChickens;	

	int m_numOfEggs; 
protected:		
	Chicken();    //private Ctor
	Chicken(const char* _name, int _id);   //private Ctor
	Chicken(const char* _name, int _id, int _numOfEggs);   //private Ctor
	Chicken(const Chicken& _chickenToCpy);   //private Copy Ctor
	Chicken& operator=(const Chicken& _chicken);  
	
public: 	
	virtual ~Chicken();
	
	static Chicken* createInstance(const char* _name);  //method of creating objects
	static Chicken* createInstance(const char* _name, int _numOfEggs); 
	
	virtual void Show() const;
	virtual void MakeSound() const;	
	
	virtual int getNumOfAnimalsCreated() const{    return ( m_numOfChickens - MIN_ID);   } 
	virtual int getNumOfAnimalsLeftToCreate() const{    return ( MAX_ID - m_numOfChickens + 1);   } 
	
	
	void setNumOfEggs(int _numOfEggs) {m_numOfEggs = _numOfEggs;}
	int getNumOfEggs() const {return m_numOfEggs;}
};


	
#endif /*__CHICKEN_H__*/


