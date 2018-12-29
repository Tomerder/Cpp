/**************************************************************************************
    Author : Tomer Dery
    Creation date :      28.12.13
    Date last modified : 28.12.13
    Description : animals 
***************************************************************************************/
#ifndef __ANIMAL_H__
#define __ANIMAL_H__


class Animal{

private: 
	const int m_id;
	char* m_name;
	
	/*creates m_name from parameter*/
	void createName(const char* _name);
	
protected:
	const char* getName() const {return m_name;}
	int getId() const {return m_id;}
		
	Animal();  	 //Ctors will be called only from derived classes
	Animal(const char* _name, int _id);
	Animal(const Animal& _AnimalToCpy);	
	Animal& operator=(const Animal& _animal);
public: 
	
	virtual ~Animal();	
	
	void setName(const char* _name);
	
	bool operator==(const Animal& _animal) const;
	bool operator>(const Animal& _animal) const;

	virtual void Show() const;
	virtual void MakeSound() const;	
	
	virtual int getNumOfAnimalsCreated() const {return 0;}  //=0
	virtual int getNumOfAnimalsLeftToCreate() const{return 0;}  //=0
};


	
#endif /*__ANIMAL_H__*/


