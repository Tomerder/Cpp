/**************************************************************************************
    Author : Tomer Dery
    Creation date :      28.12.13
    Date last modified : 28.12.13
    Description : animals
***************************************************************************************/
#ifndef __COW_H__
#define __COW_H__

#include "animal.h"


class Cow : public Animal {

private: 
	enum{MIN_ID=1, MAX_ID=1000};
	static int m_numOfCows;	
	
	int m_milkAllowed; 

protected:	
	Cow();    //private Ctor
	Cow(const char* _name, int _id);   //private Ctor
	Cow(const char* _name, int _id, int _milkAllowed);   //private Ctor
	Cow(const Cow& _cowToCpy);   //private Copy Ctor
	Cow& operator=(const Cow& _cow);  
	
public: 	
	virtual ~Cow();
	
	static Cow* createInstance(const char* _name);  //method of creating objects
	static Cow* createInstance(const char* _name, int m_milkAllowed);
	
	virtual void Show() const;
	virtual void MakeSound() const;	
	
	virtual int getNumOfAnimalsCreated() const{    return (m_numOfCows - MIN_ID);   }
	virtual int getNumOfAnimalsLeftToCreate()   const{    return ( MAX_ID - m_numOfCows + 1);   }
	
	
	void setMilkAllowed(int _milkAllowed) {m_milkAllowed = _milkAllowed;}
	int getMilkAllowed() const {return m_milkAllowed;}
};


	
#endif /*__COW_H__*/


