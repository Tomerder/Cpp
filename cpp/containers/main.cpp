#include <iostream>
#include <string.h>
#include <typeinfo>

#include "container.h"
#include "vector.h"
#include "list.h"

using namespace std;

//void checkRTTI();

void interactiveMain();

void remove(Container_t<int>* _container);
void find(Container_t<int>* _container);
void append(Container_t<int>* _container);
void prepend(Container_t<int>* _container);

int toInsert = 1;	

/*------------------------------------------------------------------------------------*/
int main() 
{
	//checkRTTI();
	interactiveMain();
		
	return 0;
}
/*------------------------------------------------------------------------------------*/

void interactiveMain()
{

	char ch;
	Container_t<int>* container = NULL;	
	
	cout << "/-----------------------------------------------------/" << endl;	
	cout << "Press 'v' to test vector , any other key to test list : ";
	cin >> ch;

	if(ch == 'v'){
		container = new Vector_t<int>();
	}else{
		container = new List_t<int>();
	}
	

	int cont = 1;
	
	while(cont) {
		cout << endl;
		cout << "1 - insert to end" 	<< endl;
		cout << "2 - append " 	<< endl;
		cout << "3 - prepend " 	<< endl;
		cout << "4 - remove " 	<< endl;
		cout << "5 - find value 5" 	<< endl;	
		cout << "6 - get num of items" 	<< endl;
		cout << "7 - save to file" 	<< endl;
		cout << "8 - get from file" 	<< endl;	
		cout << "9 - print" 	<< endl;			
		cout << "Please, choose option: ";
	
		cin >> ch;
		
		switch(ch) {
			case '1' : container->Insert(toInsert++); container->Print(); break;		
			case '2' : append(container) ; break;	
			case '3' : prepend(container) ; break;		
			case '4' : remove(container) ; break;
			case '5' : find(container); break;
			case '6' : cout << "Num of items: " <<container->getNumOfItems() << endl ; break;
			case '7' : container->SaveToFile("tmp.txt") ; break;
			case '8' : container->GetFromFile("tmp.txt"); break;
			case '9' : container->Print(); break; // container->Print(); break;
			
					
			default: cont = 0;
		}
	}

	delete container;

	cout << "/-----------------------------------------------------/" << endl;

}

/*------------------------------------------------------------------------------------*/

void append(Container_t<int>* _container)
{
	int ind;
	cout << "enter index to append :" ;
	cin >> ind ; 
	
	if(!_container->Append(ind,toInsert++)) { 
		cout << "index error!!!" << endl;
	}else{
		_container->Print();
	}
}



void prepend(Container_t<int>* _container)
{
	int ind;
	cout << "enter index to append :"; 
	cin >> ind ; 
	
	if(! _container->Prepend(ind,toInsert++)) {
		cout << "index error!!!" << endl;
	}else{
		_container->Print();
	}
}

/*------------------------------------------------------------------------------------*/

void remove(Container_t<int>* _container)
{
	int ind;
	cout << "enter index to remove :"; 
	cin >> ind ; 
	
	try{
		int getInt = _container->Remove(ind);
		cout << getInt << " removed." << endl;
		_container->Print();
	}catch(TExeption_t<int>& exp){
		exp.Print();
	}	
}

/*------------------------------------------------------------------------------------*/


void find(Container_t<int>* _container)
{
	int itemFound = 0;
	bool res = _container->Find(5, &itemFound);
	if(res)	{
		cout <<  "item found: " << itemFound  << endl;
	}else{
		cout <<  "wasnt found"  << endl;
	}
	//_container->Print();
}


/*------------------------------------------------------------------------------------*/

void checkRTTI()
{
	Container_t<int>* container = new Vector_t<int>();

	cout << "typeid(container).name() : " << typeid(container).name() << endl;
	
	cout << "( typeid(container) == typeid(Container_t<int>*) ) : " << ( typeid(container) == typeid(Container_t<int>*) ) << endl;
	cout << "( typeid(container) == typeid(Vector_t<int>*) ) : " << ( typeid(container) == typeid(Vector_t<int>*) ) << endl;
		
	cout << "( dynamic_cast< Container_t<int> *>(container) == 0 ) : " << (dynamic_cast< Container_t<int> *>(container) == 0) << endl;	
	cout << "( dynamic_cast< Vector_t<int> *>(container) == 0 ) : " << (dynamic_cast< Vector_t<int> *>(container) == 0) << endl;

}

/*------------------------------------------------------------------------------------*/

