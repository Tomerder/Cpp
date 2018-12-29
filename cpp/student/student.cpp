#include <string.h>


#include "student.h"


/*--------------------------------------------------------------------------------*/

int Student::m_nStudents = 0;

/*--------------------------------------------------------------------------------*/

Student::Student() : m_age(0) , m_faculty(0)     //ctor
{
	createName("");
	
	m_nStudents++;
}


Student::~Student()    //dtor
{   		  	
	delete[](m_name);
	m_name = NULL;   
	
	m_nStudents--;
}


Student::Student(const char* _str) :  m_age(0) , m_faculty(0)   //ctor
{
	createName(_str);
	
	m_nStudents++;
}



Student::Student(const char* _str, int _faculty) :  m_age(0) , m_faculty(_faculty)   //ctor
{
	createName(_str);
	
	m_nStudents++;
}


Student::Student(const Student& _studentToCpy) : m_age(_studentToCpy.m_age) , m_faculty(_studentToCpy.m_faculty)    //copy ctor
{
	createName( _studentToCpy.m_name  );
	
	m_nStudents++;
}


const Student& Student::operator=(const Student& _student)   //operator= 
{	
	if(&_student != this){	
		m_age = _student.m_age;
			
		delete[] m_name;	
		createName(_student.m_name);
	}
	
	return *this;
}


/*--------------------------------------------------------------------------------*/

void Student::createName(const char* _str)    //private method 
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


bool Student::operator==(const Student& _toComp) const
{
	if ( !strcmp(m_name, _toComp.m_name)  && m_age == _toComp.m_age && m_faculty == _toComp.m_faculty   ){
		return true;
	}else{
		return false;
	}
	
}

/*--------------------------------------------------------------------------------*/


int Student::getnStudents(){
	return Student::m_nStudents;
}

/*--------------------------------------------------------------------------------*/


void Student::setAge(int _age){
	if( _age > 0){	
		m_age = _age;
	}
}
	
int Student::getAge() const{
	return m_age;
}

/*--------------------------------------------------------------------------------*/

int Student::getFaculty() const{
	return m_faculty;
}

/*--------------------------------------------------------------------------------*/





