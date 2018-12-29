/***************************************************************************
    Author: Stav Ofer
    Creation date:  		2013-11-05    
    Last modified date:		2013-11-05
    Description: 	
****************************************************************************/

#include <vector>
#include <algorithm>

#include <cstring>
#include <iostream>

#include "bank.h"
#include "account.h"
#include "accFamilyImpl.h"
#include "accPersonalImpl.h"

using namespace std;


enum Choices
{
	EXIT,
	
	AAA,
	BBB,
	CCC,
	
	MENU = 100
};


//void PrintChoices(void);

/*######################################################################*/



int main()
{
//	Bank_t myBank = 
	
	Account_t *acc1;
	
	acc1 = new Account_t(PERSONAL, 1000, 2, &(Bank_t::GetBank()) );
	
	
	
	
	
	
	
	delete acc1;
	
	
//	PrintChoices();
//	
//	cout << endl << "Enter your choice: ";
//	cin >> choice;
//	
//	while(choice)
//	{
//		
//		switch(choice)
//		{
//		
////		case XX:
////			
////			
////			break;

////		case XX:
////			
////			
////			break;
//		
////		case XX:
////			
////			
////			break;
//		
//		case MENU:
//		
//			PrintChoices();
//			cout << endl;
//			break;
//			
//		case EXIT:
//		default:
//		
//			return 0;
//			
//		} // end switch
//		
//		cout << "Enter next choice (" << MENU << " for menu, " << EXIT << " to exit): ";
//		cin >> choice;
//	} // end choice
	
	
	
	
	return 0;
}


/*######################################################################*/

// print choices
//void PrintChoices(void)
//{
//	//	cout << ": " << AAA << endl;
//	//	cout << ": " << BBB << endl;
//	//	cout << ": " << CCC << endl;

//	cout << "Print menu: " << MENU << endl;
//	cout << "Exit: " << EXIT << endl;
//}
/*######################################################################*/

