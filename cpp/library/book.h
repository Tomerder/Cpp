/**************************************************************************************
    Author : Tomer Dery
    Creation date :      16.01.14
    Date last modified : 16.01.14 
    Description : Library 
***************************************************************************************/
#ifndef __BOOK_H__
#define __BOOK_H__

#include <string>
#include <iostream>
using namespace std;

typedef enum{GENERAL ,MISTORY , ADVANTURE , COMPUTERS} BOOK_SUBJECT;

class Book{ 

private: 	
	const unsigned int m_isbn;
	const string m_title;
	const string m_author;
	const BOOK_SUBJECT m_subject;
	unsigned int m_cost;
	
	/*not allowed*/
	Book& operator=(const Book& _book);	

protected:
	Book(const Book& _book)
			:m_isbn(_book.m_isbn), m_title(_book.m_title), m_author(_book.m_author), m_subject(_book.m_subject), m_cost(_book.m_cost)  {}	

public: 	
	Book(unsigned int _isbn, const string& _title, const string& _author, BOOK_SUBJECT _subject, unsigned int _cost=0) :  	
			  		 m_isbn(_isbn) , m_title(_title) , m_author(_author) , m_subject(_subject) , m_cost(_cost)  {}
		
	virtual ~Book() {}	
	
	unsigned int getIsbn() const {return m_isbn;}
	const string& getTitle() const {return m_title;}
	const string& getAuthor() const {return m_author;}
	BOOK_SUBJECT  getSubject() const {return m_subject;}
	unsigned int  getCost() const {return m_cost;}

	void setCost(unsigned int _cost) {m_cost = _cost;} 
	
	virtual void Print() const {cout << "BOOK- isbn: " <<  m_isbn << " , title: " <<  m_title << endl ;} 
};
	
#endif /*__BOOK_H__*/


