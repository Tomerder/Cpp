#include <iostream>
#include <string.h>

#include "library.h"

using namespace std;

#define SIZE 10

#define MIN_ID 111111111

/*------------------------------------------------------------------------------------*/
void Test();
void interactiveMain();

void InitPersons(Person* arrOfPersons);	
void InitBooks(Book* arrOfBooks);	

/*------------------------------------------------------------------------------------*/

int main() 
{
	/*Test();*/
	interactiveMain();	

	return 0;
}

/*------------------------------------------------------------------------------------*/

void Test()
{
	Library lib;
	
	cout << "/*--------------------------------------------------------*/" << endl;
	
	Person per1(784651654,"tomer","haifa",30);
	Person per2(777777777,"dudu","tl",40);
	
	Book bk1(111111111,"book1","author1",MISTORY,50);
	Book bk2(222222222,"book2","author2",GENERAL);
	Book bk3(333333333,"book3","author3",GENERAL);
	Book bk4(444444444,"book4","author4",MISTORY,77);
	
	lib.AddBorrower(per1);
	lib.AddBorrower(per2);
		
	lib.PrintCusts();
	cout << "/*--------------------------------------------------------*/" << endl;
	
	lib.AddLibBook(bk1);
	lib.AddLibBook(bk1);
	lib.AddLibBook(bk1);
	lib.AddLibBook(bk2);
	lib.AddLibBook(bk2);
	lib.AddLibBook(bk3);		
	
	
	lib.PrintLibBooks();	
	cout << "/*--------------------------------------------------------*/" << endl;
	
	lib.RemoveLibBook(4);
	lib.RemoveLibBook(2);
	lib.AddLibBook(bk4);	
	lib.PrintLibBooks();
	cout << "/*--------------------------------------------------------*/" << endl;
	
}	

/*------------------------------------------------------------------------------------*/

void InitPersons(Person** arrOfPersons)
{
	string Names[SIZE] = {"dudu" , "tomer" , "yosi" , "sara" ,"david" , "neta", "reut" , "natan" , "kuku" , "dana"};
	for(int i=0; i<SIZE; i++){
		arrOfPersons[i] = new Person(i,Names[i],"city " + i ,i*10);
	}
}	

void InitBooks(Book** arrOfBooks)
{
	string Names[SIZE] = {"dudu" , "tomer" , "yosi" , "sara" ,"david" , "neta", "reut" , "natan" , "kuku" , "dana"};
	for(int i=0; i<SIZE; i++){
		arrOfBooks[i] = new Book((i+1)*10,"bookTitle" , Names[i] , GENERAL ,i*10);
	}
}	

void CleanPersons(Person** arrOfPersons)
{
	for(int i=0; i<SIZE; i++){
		delete(arrOfPersons[i]);
	}
}	

void CleanBooks(Book** arrOfBooks)
{
	for(int i=0; i<SIZE; i++){
		delete(arrOfBooks[i]);
	}
}	
/*------------------------------------------------------------------------------------*/
void AddBookMain(Library* _lib, Book** _arrOfBooks)
{
	int bookNum=0 , callNum=0;
	cout << "/*--------------------------------------------------------*/" << endl;
	cout << "you have " << SIZE << " kind of books for test. enter book number to add to library :";
	cin >> bookNum;

	if( bookNum <= SIZE && bookNum>0 ){
		callNum = _lib->AddLibBook(*_arrOfBooks[bookNum - 1]);
	}else{
		cout << "book number illeagal" << endl;
		return;
	}

	if(callNum > 0){
		cout << "call number of added book is: " << callNum << endl;
		_lib->PrintLibBooks();
	}else{
		cout << "error!!!" << endl;
	}
}

void AddCustMain(Library* _lib, Person** _arrOfPersons)
{
	int personNum=0 , custNum=0;
	cout << "/*--------------------------------------------------------*/" << endl;
	cout << "you have " << SIZE << " persons for test. enter persons number to add as customer :";
	cin >> personNum;

	if( personNum <= SIZE && personNum>0){
		custNum = _lib->AddBorrower(*_arrOfPersons[personNum - 1]);
	}else{
		cout << "illeagal input" << endl;
		return;
	}

	if(custNum > 0){
		cout << "cust number of added customer is: " << custNum << endl;
		_lib->PrintCusts();
	}else{
		cout << "error!!!" << endl;
	}
}
/*------------------------------------------------------------------------------------*/

void RemoveBookMain(Library* _lib)
{
	int callNum;
	cout << "/*--------------------------------------------------------*/" << endl;
	cout << "Enter call num to remove :";
	cin >> callNum;

	if (_lib->RemoveLibBook(callNum)){
		cout << "book removed" << endl;
		_lib->PrintLibBooks();
	}else{
		cout << "error!!!" << endl;
	}
}

void RemoveCustMain(Library* _lib)
{
	int custNum;
	cout << "/*--------------------------------------------------------*/" << endl;
	cout << "Enter cust num to remove :";
	cin >> custNum;

	if (_lib->RemoveBorrower(custNum)){
		cout << "customer removed" << endl;
		_lib->PrintCusts();
	}else{
		cout << "error!!!" << endl;
	}
}
/*------------------------------------------------------------------------------------*/
void SearchBookMain(Library* _lib)
{
	LibraryBook* libBookToFound = 0;
	bool WasFound = false;
	list<LibraryBook*>::iterator itr;
	list<LibraryBook*> libBooksList;
	int i;
	string title, author;

	char ch;
	cout << "search by: " << endl;
	cout << "1: callNum " << endl;
	cout << "2: isbn " << endl;
	cout << "3: title " << endl;
	cout << "4: author " << endl;
	cout << "Please, choose option: ";

	cin >> ch;
	switch(ch) {
		case '1' :  cout << "enter call number: " ;
					unsigned int callNum;
					cin >> callNum;
					libBookToFound = _lib->SearchLibBookByCallNum(callNum); 
					if(libBookToFound){
						cout << "library book was found:" << endl;
						libBookToFound->Print();
					}else{
						cout << "library book was not found!!!" << endl;
					}
					break;		
		case '2' :  cout << "enter isbn: " ;
					unsigned int isbn;
					cin >> isbn;
					WasFound = _lib->SearchLibBooksByIsbn(isbn, libBooksList); 
					if(WasFound){
						for(itr = libBooksList.begin() , i=1; itr != libBooksList.end() ; itr++ , i++){
							cout << "(" << i << ") ";							
							(*itr)->Print();
							cout << endl;
						}
					}else{
						cout << "books with this isbn were not found at library!!!" << endl;
					}
					break;		
		case '3' :  cout << "enter title: " ;
					cin >> title;
					WasFound = _lib->SearchLibBooksByTitle(title, libBooksList); 
					if(WasFound){
						for(itr = libBooksList.begin() , i=1; itr != libBooksList.end() ; itr++ , i++){
							cout << "(" << i << ") ";							
							(*itr)->Print();
							cout << endl;
						}
					}else{
						cout << "books with this title were not found at library!!!" << endl;
					}
					break;		
		case '4' :  cout << "enter author: " ;
					cin >> author;
					WasFound = _lib->SearchLibBooksByAuthor(author, libBooksList); 
					if(WasFound){
						for(itr = libBooksList.begin() , i=1; itr != libBooksList.end() ; itr++ , i++){
							cout << "(" << i << ") ";							
							(*itr)->Print();
							cout << endl;
						}
					}else{
						cout << "books with this author were not found at library!!!" << endl;
					}
					break;		
		default:    break;
	}
}

void SearchCustMain(Library* _lib)
{
	Borrower* borrowerToFound = 0;

	char ch;
	cout << "search by: " << endl;
	cout << "1: id " << endl;
	cout << "2: custNum " << endl;
	cout << "Please, choose option: ";

	cin >> ch;
	switch(ch) {
		case '1' :  cout << "enter id: ";
					unsigned int id;
					cin >> id;
					borrowerToFound = _lib->SearchBorrowerById(id); 
					if(borrowerToFound){
						cout << "borrower was found" << endl;
					}else{
						cout << "borrower was not found!!!" << endl;
					}
					break;
		case '2' :  cout << "enter cust num: ";
					unsigned int custNum;
					cin >> custNum;
					borrowerToFound = _lib->SearchBorrowerByCustNum(custNum); 
					if(borrowerToFound){
						cout << "borrower was found" << endl;
					}else{
						cout << "borrower was not found!!!" << endl;
					}
					break;				
		default: break;
	}

}

/*------------------------------------------------------------------------------------*/

void BorrowBookMain(Library* _lib)
{
	unsigned int isbn , custNum, callNum;

	cout << "enter cust num: " ;				
	cin >> custNum;

	cout << "enter isbn: " ;				
	cin >> isbn;

	callNum = _lib->BorrowBook(custNum, isbn);
	if(callNum){
		if(callNum == UINT_MAX){
			cout << "customer has been inserted to waiting list and will be notify when the book will be in stock" << endl ; 
		}else{
			cout << "book has been borrowed - call number : " << callNum << endl ; 
		}
	} else{
		cout << "error!!!" << endl ; 
	}
}

/*------------------------------------------------------------------------------------*/

void ReturnBookMain(Library* _lib)
{
	unsigned int custNum, callNum;

	cout << "enter cust num: " ;				
	cin >> custNum;

	cout << "enter call number that has been returned: " ;				
	cin >> callNum;
	
	if(_lib->ReturnBook(custNum, callNum) ){
		cout << "book has been returned" << endl ; 
	} else{
		cout << "error!!!" << endl ; 
	}
}

/*------------------------------------------------------------------------------------*/
void interactiveMain()
{
	Library* lib = new Library;
	Person* arrOfPersons[SIZE];
	Book* arrOfBooks[SIZE];	

	InitPersons(arrOfPersons);	
	InitBooks(arrOfBooks);	

	
	Person per1(784651654,"tomer","haifa",30);
	Person per2(777777777,"dudu","tl",40);
	
	Book bk1(1,"book1","author1",MISTORY,50);
	Book bk2(2,"book2","author2",GENERAL);
	Book bk3(3,"book3","author3",GENERAL);
	Book bk4(4,"book4","author4",MISTORY,77);
	
	lib->AddBorrower(per1);
	lib->AddBorrower(per2);
	
	lib->AddLibBook(bk1);
	lib->AddLibBook(bk1);
	lib->AddLibBook(bk1);
	lib->AddLibBook(bk2);
	lib->AddLibBook(bk2);
	lib->AddLibBook(bk3);		
	lib->AddLibBook(bk4);		

	char ch;
	
	int cont = 1;
	
	while(cont) {
		cout << endl;
		cout << "/*--------------------------------------------------------*/" << endl;
		cout << "1 - add a book" 	<< endl;
		cout << "2 - add customer" 	<< endl;
		cout << "3 - remove book" 	<< endl;
		cout << "4 - remove customer" 	<< endl;
		cout << "5 - search book" 	<< endl;
		cout << "6 - search customer" 	<< endl;
		cout << "7 - borrow book" 	<< endl;
		cout << "8 - return book" 	<< endl;
		cout << "9 - print books" 	<< endl;
		cout << "0 - print customers" 	<< endl;		
		cout << "Please, choose option: ";
	
		cin >> ch;
		
		switch(ch) {
			case '1' : AddBookMain(lib, arrOfBooks) ; break;		
			case '2' : AddCustMain(lib, arrOfPersons) ; break;	
			case '3' : RemoveBookMain(lib) ; break;			
			case '4' : RemoveCustMain(lib) ; break;
			case '5' : SearchBookMain(lib) ; break;			
			case '6' : SearchCustMain(lib) ; break;
			case '7' : BorrowBookMain(lib) ; break;			
			case '8' : ReturnBookMain(lib) ; break;			
			case '9' : lib->PrintLibBooks(true); break;			
			case '0' : lib->PrintCusts(true); break;
	
			default: cont = 0;
		}
	}

	delete lib;
	CleanPersons(arrOfPersons);	
	CleanBooks(arrOfBooks);	

	cout << "/-----------------------------------------------------/" << endl;

}

/*--------------------------------------------------------------------------*/

