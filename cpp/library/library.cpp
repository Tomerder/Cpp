#include <string.h>
#include <iostream>
#include <algorithm>

#include "library.h"

using namespace std;


/*------------------------------------------------------------------------------------*/

Library::~Library() 
{
	/* delete all items on every stl*/
	for(ItrBorrwer itrBorrwer = m_custMap.begin() ; itrBorrwer != m_custMap.end() ; itrBorrwer++){
		delete(itrBorrwer->second);
	}
	m_custMap.clear();

	for(ItrLibBook itrLibBook = m_libBookMap.begin() ; itrLibBook != m_libBookMap.end() ; itrLibBook++){
		delete(itrLibBook->second);
	}
	m_libBookMap.clear();

	for(ItrBookCount itrBookCount = m_bookCountMap.begin() ; itrBookCount != m_bookCountMap.end() ; itrBookCount++){
		delete(itrBookCount->second);
	}
	m_bookCountMap.clear();

	for(ItrWaitingList itrWaitingList = m_waitingLists.begin() ; itrWaitingList != m_waitingLists.end() ; itrWaitingList++){
		delete(itrWaitingList->second);
	}
	m_waitingLists.clear();
	 
}	

/*------------------------------------------------------------------------------------*/

unsigned int Library::AddBorrower(const Person& _person)
{
	Borrower* newBorrower = new Borrower(_person);
	
	/*add to cust map*/
	unsigned int custNum =  newBorrower->getCustNum();
	m_custMap[ custNum ] = newBorrower; /*1*/
	m_custMapId2CustNum[ newBorrower->getId() ] = custNum;   /*2*/

	return custNum;
}

/*------------------------------------------------------------------------------------*/

bool Library::RemoveBorrower(unsigned int _custNum)
{
	/*check if exists*/
	ItrBorrwer itrBorrwer = SearchBorrowerImp(_custNum);
	if(itrBorrwer == m_custMap.end()){
		return false;
	}
	
	/*remove from all maps*/
	Borrower* borrower = itrBorrwer->second;
	m_custMap.erase(itrBorrwer);     /*1*/
	m_custMapId2CustNum.erase( borrower->getId() ); /*2*/
	
	delete(borrower);

	return true;
}

/*------------------------------------------------------------------------------------*/

unsigned int Library::AddLibBook(const Book& _book)
{
	LibraryBook* newlibBook = new LibraryBook(_book);
	
	/*add to libBook map*/
	unsigned int callNum = newlibBook->getCallNum();
	m_libBookMap[ callNum ] = newlibBook;  /*3*/
	
	/*add to book count map*/
	IncLibBookCount(newlibBook); /*4*/
	                                  
	/*add to book-libBook multi map*/
	unsigned int isbn = newlibBook->getIsbn();
	m_book2LibBookMMap.insert (pair<unsigned int,unsigned int>(isbn,callNum));   /*5*/

	/*add to bookTitle-libBook multi map*/
	string title = newlibBook->getTitle();
	m_bookTitle2LibBookMMap.insert (pair<string, unsigned int>(title,callNum));   		
	
	/*add to bookAutur-libBook multi map*/
	string author = newlibBook->getAuthor();
	m_bookAuthor2LibBookMMap.insert (pair<string, unsigned int>(author,callNum));   

	return callNum;
}

void Library::IncLibBookCount(const LibraryBook* _book)
{
	unsigned int isbn = _book->getIsbn();
	ItrBookCount itrBookCount = m_bookCountMap.find(isbn);
	if(itrBookCount == m_bookCountMap.end() ){
		BookCount* newBookCount = new BookCount; 
		newBookCount->m_count = 1;
		newBookCount->m_countOut = 0;
		m_bookCountMap[isbn] = newBookCount;	 
	}else{
		itrBookCount->second->m_count++;
	}
}

/*------------------------------------------------------------------------------------*/
void Library::RemoveLibBookFromMMisbn(LibraryBook* _libBook, unsigned int _callNum)
{
	ItrMMbook2LibBook  itrMMbook2LibBook =  m_book2LibBookMMap.find(_libBook->getIsbn());
	while(itrMMbook2LibBook != m_book2LibBookMMap.end()  &&   itrMMbook2LibBook->second != _callNum){
		++itrMMbook2LibBook;
	} 
	if(itrMMbook2LibBook == m_book2LibBookMMap.end()){ /*not suppose to happen !!!!*/
		throw _callNum;
	}else{
		m_book2LibBookMMap.erase(itrMMbook2LibBook);    /*5*/
	}
}

void Library::RemoveLibBookFromMMtitle(LibraryBook* _libBook, unsigned int _callNum)
{
	ItrMMbookStr2LibBook  itrMMbook2LibBook =  m_bookTitle2LibBookMMap.find(_libBook->getTitle());
	while(itrMMbook2LibBook != m_bookTitle2LibBookMMap.end()  &&   itrMMbook2LibBook->second != _callNum){
		++itrMMbook2LibBook;
	} 
	if(itrMMbook2LibBook == m_bookTitle2LibBookMMap.end()){ /*not suppose to happen !!!!*/
		throw _callNum;
	}else{
		m_bookTitle2LibBookMMap.erase(itrMMbook2LibBook);    
	}
}

void Library::RemoveLibBookFromMMauthor(LibraryBook* _libBook, unsigned int _callNum)
{
	ItrMMbookStr2LibBook  itrMMbook2LibBook =  m_bookAuthor2LibBookMMap.find(_libBook->getAuthor());
	while(itrMMbook2LibBook != m_bookAuthor2LibBookMMap.end()  &&   itrMMbook2LibBook->second != _callNum){
		++itrMMbook2LibBook;
	} 
	if(itrMMbook2LibBook == m_bookAuthor2LibBookMMap.end()){ /*not suppose to happen !!!!*/
		throw _callNum;
	}else{
		m_bookAuthor2LibBookMMap.erase(itrMMbook2LibBook);    
	}
}

bool Library::RemoveLibBook(unsigned int _callNum)
{
	ItrLibBook itrLibBook = SearchLibBookImp(_callNum);	
	
	/*check if exists*/
	if(itrLibBook == m_libBookMap.end() ){
		return false;
	}
	
	LibraryBook* libBook = itrLibBook->second;
	
	/*check if out*/
	if( libBook->getStatus() == OUT){
		return false;
	}
	
	/*bookCountMap-- */
	DecLibBookCount(libBook);    /*4*/
		
	/*remove from libBookMap*/
	m_libBookMap.erase(itrLibBook);  /*3*/
	
	/*remove from book-libBook multi map*/
	RemoveLibBookFromMMisbn(libBook, _callNum);
	
	/*remove from bookTitle-libBook multi map*/
	RemoveLibBookFromMMtitle(libBook, _callNum);

	/*remove from bookAuthor-libBook multi map*/
	RemoveLibBookFromMMauthor(libBook, _callNum);

	delete(libBook);

	return true;
}
	
void Library::DecLibBookCount(const LibraryBook* _book)
{
	unsigned int isbn = _book->getIsbn();
	ItrBookCount itrBookCount = m_bookCountMap.find(isbn);
	if(itrBookCount == m_bookCountMap.end() ){  /*not supose to happen!!!!*/
		throw isbn;
	}	
	
	BookCount* bookCount = itrBookCount->second;
	--(bookCount->m_count); 
}	

	
/*------------------------------------------------------------------------------------*/	

void Library::PrintCusts(bool _withBooks) const
{	
	
	for(CItrBorrwer itr = m_custMap.begin() ; itr != m_custMap.end() ; itr++){
		if(!_withBooks){		
			itr->second->Print();
		}else{
			itr->second->PrintWithBooksTaken();
		}
		cout << endl;
	}
}	

void Library::PrintLibBooks(bool _withOwner) const
{
	for(CItrLibBook itr = m_libBookMap.begin() ; itr != m_libBookMap.end() ; itr++){
		if(!_withOwner){		
			itr->second->Print();
		}else{
			itr->second->PrintWithOwner();
		}
		cout << endl;
	}	
}
/*------------------------------------------------------------------------------------*/		
	
ItrLibBook Library::SearchLibBookImp(unsigned int _callNum)
{
	ItrLibBook itrLibBook = m_libBookMap.find(_callNum);
	return itrLibBook;
}

LibraryBook* Library::SearchLibBookByCallNum(unsigned int _callNum)
{
	ItrLibBook itrLibBook = SearchLibBookImp(_callNum);
	if(itrLibBook == m_libBookMap.end() ){
		return NULL;
	}else{
		return itrLibBook->second;
	}
}
	
/*------------------------------------------------------------------------------------*/			
	
ItrBorrwer Library::SearchBorrowerImp(unsigned int _custNum)
{
	ItrBorrwer itrBorrwer = m_custMap.find(_custNum);
	return itrBorrwer;
}

Borrower* Library::GetBorrowerByCustNum(unsigned int _custNum)
{
	ItrBorrwer itrBorrwer = SearchBorrowerImp(_custNum);
	if(itrBorrwer == m_custMap.end() ){
		return NULL;
	}

	return itrBorrwer->second;	
}

Borrower* Library::GetBorrowerById(unsigned int _id)
{
	ItrId2CustNum itrId2CustNum = m_custMapId2CustNum.find(_id);
	ItrBorrwer itrBorrwer;	

	if(itrId2CustNum == m_custMapId2CustNum.end() ){
		return NULL;
	}else{
		unsigned int custNum = itrId2CustNum->second;
		itrBorrwer = SearchBorrowerImp(custNum);
		if(itrBorrwer == m_custMap.end() ){
			return NULL;
		}
	}

	return itrBorrwer->second;
}
	
Borrower* Library::SearchBorrowerById(unsigned int _id)
{
	return GetBorrowerById(_id);
}

Borrower* Library::SearchBorrowerByCustNum(unsigned int _custNum)
{
	return GetBorrowerByCustNum(_custNum);
}
	
/*------------------------------------------------------------------------------------*/		

BookCount* Library::GetBoookCountByIsbn(unsigned int _isbn)
{
	/*checks for avaliable books*/
	ItrBookCount itrBookCount = m_bookCountMap.find(_isbn);
	if(itrBookCount == m_bookCountMap.end() ){
		return 0;
	}

	return itrBookCount->second;
}

/*------------------------------------------------------------------------------------*/		

queue<Borrower*>* Library::GetWaitingList(unsigned int _isbn)
{
	ItrWaitingList itrWaitingList = m_waitingLists.find(_isbn);
	if(itrWaitingList == m_waitingLists.end() ){
		return 0;	
	}

	return itrWaitingList->second;
}

/*------------------------------------------------------------------------------------*/		

void Library::InsertBorrowerToWaitList(unsigned int _isbn, Borrower* borrower)
{
	queue<Borrower*>* waitingList = GetWaitingList(_isbn);

	if(!waitingList){
		waitingList = m_waitingLists[_isbn] = new queue<Borrower*>;
	}

	waitingList->push(borrower);
}

/*------------------------------------------------------------------------------------*/	
LibraryBook* Library::GetAvailableLibBook(unsigned int _isbn)
{
	LibraryBook* libBook = 0;
	ItrMMbook2LibBook  itrMMbook2LibBook =  m_book2LibBookMMap.find(_isbn);
	while(itrMMbook2LibBook != m_book2LibBookMMap.end() ){
		unsigned int callNum = itrMMbook2LibBook->second;
		libBook = SearchLibBookByCallNum(callNum);
		if(libBook->getStatus() != AVAILABLE){
			++itrMMbook2LibBook;
		}else{
			break;
		}	
	} 
	if(!libBook || libBook->getIsbn() != _isbn){ /*not suppose to happen !!!!*/
		throw _isbn;
	}

	return libBook;
}

/*------------------------------------------------------------------------------------*/	
	
unsigned int Library::BorrowBook(unsigned int _custNum, unsigned int _isbn)
{
	/*check borrower exists*/
	Borrower* borrower = GetBorrowerByCustNum(_custNum);
	if(!borrower){
		return false;
	}

	/*checks for avaliable books*/
	BookCount* bookCount = GetBoookCountByIsbn(_isbn);
	if(!bookCount){
		return false;
	}

	/*if borrower already has this book - borrowing not allowed*/
	if( borrower->getLibBookFromMap(_isbn) ){
		return false;
	}

	if(bookCount->m_count - bookCount->m_countOut <= 0){
		/*no books -> insert borrower to waiting list*/
		InsertBorrowerToWaitList(_isbn, borrower);
		return UINT_MAX;
	}

	/*all ok - borrow book*/
	/*library book side*/
	LibraryBook* libBook = GetAvailableLibBook(_isbn);
	libBook->setCurBorrower(borrower);
	libBook->setStatus(OUT);
	
	bookCount->m_countOut++;

	/*borrower side*/
	borrower->InsertBookToMap(_isbn, libBook);

	return libBook->getCallNum();
}

/*------------------------------------------------------------------------------------*/	
	
void Library::NotifyBorrowerOnWaitList(unsigned int _isbn)
{
	queue<Borrower*>* waitingList = GetWaitingList(_isbn);
	Borrower* borrower = waitingList->front();

	waitingList->pop();

	borrower->NotifyBookAvailable(_isbn);
}


bool Library::ReturnBook(unsigned int _custNum, unsigned int _callNum)
{
	/*check borrower exists*/
	Borrower* borrower = GetBorrowerByCustNum(_custNum);
	if(!borrower){
		return false;
	}

	LibraryBook* libBook = SearchLibBookByCallNum(_callNum);
	if(!libBook){
		return false;
	}

	/*check that borrower indeed has this book*/
	if(libBook->getCurBorrower() != borrower){
		return false;
	}

	unsigned int isbn = libBook->getIsbn();
	BookCount* bookCount = GetBoookCountByIsbn(isbn);
	if(!bookCount){
		throw _callNum;  /* not supose to happen !!!!!!!*/
	}

	if(bookCount->m_count - bookCount->m_countOut == 0){
		/*should send notification to first on waiting list*/
		NotifyBorrowerOnWaitList(isbn);
	}

	/*all ok - borrow book*/
	/*library book side*/
	libBook->setCurBorrower(0);
	libBook->setStatus(AVAILABLE);
	
	bookCount->m_countOut--;

	/*borrower side*/
	borrower->EraseBookFromMap(isbn);

	return true;
}

/*------------------------------------------------------------------------------------*/		

bool Library::SearchLibBooksByIsbn(unsigned int _isbn, list<LibraryBook*>& _outputList)
{
	bool toRet = false;
	LibraryBook* libBook = 0;
	
	for(ItrMMbook2LibBook  itrMMbook2LibBook =  m_book2LibBookMMap.find(_isbn); itrMMbook2LibBook != m_book2LibBookMMap.end() ; itrMMbook2LibBook++){	
		unsigned int callNum = itrMMbook2LibBook->second;
		libBook = SearchLibBookByCallNum(callNum);
		if(libBook->getIsbn() != _isbn){
			break;
		}else{
			toRet = true; 
			_outputList.push_back(libBook);
		}	
	} 

	return toRet;
}

/*------------------------------------------------------------------------------------*/		

bool Library::SearchLibBooksByTitle(string _title, list<LibraryBook*>& _outputList)
{
	bool toRet = false;
	LibraryBook* libBook = 0;
	
	for(ItrMMbookStr2LibBook  itrMMbook2LibBook =  m_bookTitle2LibBookMMap.find(_title); itrMMbook2LibBook != m_bookTitle2LibBookMMap.end() ; itrMMbook2LibBook++){	
		unsigned int callNum = itrMMbook2LibBook->second;
		libBook = SearchLibBookByCallNum(callNum);
		if(libBook->getTitle() != _title){
			break;
		}else{
			toRet = true; 
			_outputList.push_back(libBook);
		}	
	} 

	return toRet;
}

/*------------------------------------------------------------------------------------*/		

bool Library::SearchLibBooksByAuthor(string _author, list<LibraryBook*>& _outputList)
{
	bool toRet = false;
	LibraryBook* libBook = 0;
	
	for(ItrMMbookStr2LibBook  itrMMbook2LibBook =  m_bookAuthor2LibBookMMap.find(_author); itrMMbook2LibBook != m_bookAuthor2LibBookMMap.end() ; itrMMbook2LibBook++)
	{		
		unsigned int callNum = itrMMbook2LibBook->second;
		libBook = SearchLibBookByCallNum(callNum);
		if(libBook->getAuthor() != _author){
			break;
		}else{
			toRet = true; 
			_outputList.push_back(libBook);
		}	
	} 

	return toRet;

}

/*------------------------------------------------------------------------------------*/		





















		
	
