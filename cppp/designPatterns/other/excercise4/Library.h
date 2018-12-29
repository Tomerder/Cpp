/***************************************************************************
    Author: Stav Ofer
    Creation date:  		2013-11-10    
    Last modified date:		2013-11-14
    Description: 	Library Management System - design
    
    				Notes:
					
    				- for the purpose of this excercise, it is assumed that book
    				titles are unique, so all books with the same title are copies
    				of the same book.
    				- search for a specific copy is by id, search for a book 
    				is by title
****************************************************************************/

#ifndef __LIBRARY_H__
#define __LIBRARY_H__

#include <string>
#include <map>
#include <vector>

#include "observer.h"
#include "subject.h"


namespace library
{

//=======================================================================//
//		Definitions & class foreward declaration
//=======================================================================//

using std::size_t;
using std::vector;
using std::map;
using std::string;

typedef enum BookSubject
{
	HISTORY,
	SCIENCE,
	ROMANCE,
	THRILLER
} BookSubject;

class BookRecord_t;
class Library_t;
class Borrower_t;


//=======================================================================//
//		BOOK - can't exist without a record
//=======================================================================//
class Book_t
{
public:
	// generated DTOR
		
	// get data from book record
	const string& 		GetTitle() const;
	const string& 		GetAuthor() const;
	const BookSubject   GetSubject() const;
	
	bool  Borrow();
	void  Return();
	bool  IsAvailable() const;
	const BookRecord_t* GetRecord();
	
private:
	BookRecord_t* const 	m_record;
	bool 					m_borrowed;
	size_t					m_borrowerID;
	
	vector<int>	m_history;	// list of past borrowers
	
	static size_t BOOK_ID;
	
	// CTOR, copy CTOR - only by BookRecord
	explicit Book_t(BookRecord_t* _record);
	Book_t(const Book_t& _other); // copy - only ptr to record
	
	friend class BookRecord_t;
	
	// no assignment - one book can't turn into another
	void operator =(const Book_t&);
};



//=======================================================================//
//	BOOK RECORD - 	a proxy for all of the same book's copies
//					a subject of observers = borrowers
//=======================================================================//
class BookRecord_t : public Subject_t
{
public:
	// DTOR - destroy all copies
	virtual ~BookRecord_t();
	// CTOR non explicit on purpose - can accept e.g. char*
	BookRecord_t(string _title, string _author, BookSubject _subject, Library_t* _lib);
	
	// copy - can copy author & subject, not title
	BookRecord_t(const BookRecord_t& _other, string _title);
	
	// get/set data fields
	void  			  SetTitle(string _title);
	const string& 	  GetTitle() const;
	void  			  SetAuthor(string _author);
	const string& 	  GetAuthor() const;
	void  			  SetSubject(BookSubject _subject);
	const BookSubject GetSubject() const;
	
	Book_t* Borrow	(Borrower_t* _borrower);
	void    Return	(Book_t* _book);
	
	void AddCopy();
	void RemoveCopy();
	bool IsAvailable() const; // are there available copies
	
	
	// inherited
//	virtual void Attach(Observer_t*);	// func for observers to call
//  virtual void Detach(Observer_t*);
//	virtual void Notify(void* _params, char* _txt=0);	// NOTIFY
	
protected:
	Library_t* m_lib;	// ptr to library where book belongs
	
	string m_title;
	string m_author;
	BookSubject m_subject;
	size_t 		m_availableCopies;
	size_t		m_numCopies;
	
	vector<Book_t*> m_copies;
	
	Book_t* GetAvailableCopy();
	
	// inherited
//	vector<Observer_t*> m_obs;	// vector of observers = borrowers
	
	// no assignment - record for one book can't change to record of another
	BookRecord_t& operator =(const BookRecord_t& _other);
};





//=======================================================================//
//			BORROWER - an observer (of multiple subjects)
//=======================================================================//
class Borrower_t : public Observer_t
{
public:
	// DTOR - return all books & deregister
	virtual ~Borrower_t();
	// CTOR non expliciton purpose - can accept e.g. char*
			Borrower_t(string _name, string _address, string _phone);
	
	// copy/assignment - can copy address & phone, not name (or ID)
	Borrower_t(const Borrower_t& _other, string _name);
	Borrower_t& operator =(const Borrower_t& _other);
	
	// get/set data fields
	void  SetName(string _name);
	const string& GetName() const;
	void  SetAddress(string _address);
	const string& GetAddress() const;
	void  SetPhone(string _phone);
	const string& GetPhone() const;
	
	
	virtual bool LibraryRegister();
	virtual void LibraryDeregister();
	
	virtual Book_t* Borrow	(string _title);	// borrow a book (returns book ptr or  for failure)
	virtual void Return		(Book_t* _book);			// return book to library
	
	const vector<Subject_t*>& GetBookList() const;
	
	// UPDATE function - get nofifications from subject = books
	virtual void Update(Subject_t* _sbj, char* _txt = 0); 
	
protected:
	Library_t* m_lib;	// ptr to library where borrower is registered, or 0 if not registered
	
	string m_name;
	string m_address;
	string m_phone;
	size_t 		m_id;
	
	// inherited
//	vector<Subject_t*> m_sbj;	// vector of subjects = books
	
	static size_t BORROWER_ID;
};




//=======================================================================//
//	Book Admin - a singleton
//=======================================================================//
class BookAdmin_t
{
public:
	// CTOR is private
	// no copy
	
	//DTOR: not using generated b/c need to destroy all book records
	~BookAdmin_t();
	
	// actions by borrower
	bool Borrow(string _title, Borrower_t* _borrower);	// borrow a book (returns success/fail)
	void Return(Book_t* _book);								// return a book
	
	// actions by library - books
	void AddNewBook		(string _title, string _author, BookSubject _subj);
	bool RemoveBook		(int _id);	// returns success/fail (if book is out)
	Book_t* FindBook	(int _id);	// return 0 if not found
	bool UpdateBook		(string _title);	
	
	bool IsBookBorrowed		(Book_t* _book) const;
	void ReportAllBooks		() const;
	void ReportBookHistory	(int _id) const;
	
private:
	static BookAdmin_t& m_bookAdmin;	// "actual" BookAdmin
	
	static map<string, BookRecord_t*> m_bookRecords; // all bookRecords, searchable by title
	
	static void reportBook(string _title);	// generate a report for a single book 
	
	
	// no public CTOR
	BookAdmin_t();
	// no copy / assignment
	BookAdmin_t(const BookAdmin_t&);
	void operator=(BookAdmin_t&);	
};



//=======================================================================//
//	Borrower Admin - a singleton
//=======================================================================//
class BorrowerAdmin_t
{
public:
	// CTOR is private
	// no copy
	
	//DTOR: not using generated b/c need to destroy all borrower records
	~BorrowerAdmin_t();
	
	int AddBorrower		 (string _name, string _address, string _phone);	// return id
	Borrower_t* FindBorrower (int _id); // return 0 if not found
	bool RemoveBorrower		 (int _id);	// returns success/fail (if borrower has library books)
	void ReportBorrowers	 () const;
	
private:
	static BorrowerAdmin_t& m_borAdmin;	// "actual" BorrowerAdmin
	
	static map<int, Borrower_t*> m_borrowers; // all borrowers, searchable by id
	
	static void reportSingleBorrower(int _id);	// generate a single borrower report
	
	// no public CTOR
	BorrowerAdmin_t();
	// no copy / assignment
	BorrowerAdmin_t(const BorrowerAdmin_t&);
	void operator=(BorrowerAdmin_t&);	
};




//=======================================================================//
//	LIBRARY -	a singleton, and a facade - interface for both book admin &
//				borrower records admin
//=======================================================================//
class Library_t
{
public:
	// CTOR is private
	// no copy
	// use generated DTOR
	
	static Library_t& GetLibrary();
	
	// actions by borrower
	bool Borrow(string _title, Borrower_t* _borrower);	// borrow a book (returns success/fail)
	void Return(Book_t* _book);								// return a book
	
	// actions by library - books
	void BuyNewBook		(string _title, string _author, BookSubject _subj);
	bool RemoveBook		(int _id);	// returns success/fail (if book is out)
	Book_t* FindBook	(int _id);	// return 0 if not found
	bool UpdateBook		(string _title);	
	
	bool IsBookBorrowed		(Book_t* _book) const;
	void ReportAllBooks		() const;
	void ReportBookHistory	(int _id) const;
	
	// actions by library - borrowers
	bool AddBorrower		 (string _name, string _address, string _phone);
	Borrower_t* FindBorrower (int _id); // return 0 if not found
	bool RemoveBorrower		 (int _id);	// returns success/fail (if borrower has library books)
	void ReportBorrowers	 () const;
	
private:
	static Library_t& m_lib;	// "actual" library
	
	static BookAdmin_t&		m_bookAdmin;
	static BorrowerAdmin_t&	m_borrowerAdmin;
	
	// no public CTOR
	Library_t();
	// no copy / assignment
	Library_t(const Library_t&);
	void operator=(Library_t&);	
};


}
//----------------------- END namespace library --------------------------//


#endif /*__LIBRARY_H__ */
