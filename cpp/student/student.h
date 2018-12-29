/**************************************************************************************
    Author : Tomer Dery
    Creation date :      28.12.13
    Date last modified : 28.12.13
    Description : student.h 
***************************************************************************************/
#ifndef __STUDENT_H__
#define __STUDENT_H__


class Student{

private: 
	int m_age;
	const int m_faculty;
	char* m_name;
		
	static int m_nStudents;
	
	/*creates m_name from parameter*/
	void createName(const char* _str);
		
public: 
	Student();  
	~Student();
	
	Student(const char* _str);	
	Student(const char* _str, int _faculty);

	Student(const Student& _StudentToCpy);
	
	const Student& operator=(const Student& _student);
	
	bool operator==(const Student& _student) const;
	
	static int getnStudents();

	void setAge(int _age);
	int getAge() const;

	int getFaculty() const;	
};


	
#endif /*__STUDENT_H__*/


