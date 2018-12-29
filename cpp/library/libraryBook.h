/**************************************************************************************
    Author : Tomer Dery
    Creation date :      16.01.14
    Date last modified : 16.01.14 
    Description : Library 
***************************************************************************************/
#ifndef __LIBRARY_BOOK_H__
#define __LIBRARY_BOOK_H__

#include "book.h"
/*#include "borrower.h"*/
class Borrower;

typedef enum{AVAILABLE ,OUT , MAINTENANCE} LIBRARY_BOOK_STATUS;

/*------------------------------------------------------------------------------------*/	

class LibraryBook : public Book{ 

private: 	
	const unsigned int m_callNum;
	static unsigned int m_count;
	LIBRARY_BOOK_STATUS m_status; 
	Borrower* m_curBorrower;
	
	/*not allowed*/
	LibraryBook(const LibraryBook& _book);	
	LibraryBook& operator=(const LibraryBook& _book);	

public: 		
	LibraryBook(const Book& _book) :
		    Book(_book) ,
		    m_callNum(m_count++) , m_status(AVAILABLE)   , m_curBorrower(0)  {}
		
	virtual ~LibraryBook() { /*--m_count;*/ }	
	
	unsigned int getCallNum() const {return m_callNum;}
	static unsigned int getCount() {return m_count;}
	LIBRARY_BOOK_STATUS getStatus() const {return m_status;}
	const Borrower* getCurBorrower() const {return m_curBorrower;}

	void setStatus(LIBRARY_BOOK_STATUS _status) {m_status = _status;} 
	void setCurBorrower(Borrower* _borrower) {m_curBorrower = _borrower;} 

	virtual void Print() const { Book::Print(); cout << "LIB BOOK- callNum: " <<  m_callNum << " , status: " <<  m_status << endl ;  } 
	void PrintWithOwner() const;
};

/*------------------------------------------------------------------------------------*/	

#endif /*__LIBRARY_BOOK_H__*/

