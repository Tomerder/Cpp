/***************************************************************************
    Author: Stav Ofer
    Creation date:  		2013-00-00    
    Last modified date:		2013-00-00
    Description: 	
****************************************************************************/


#include <cstring>
#include <iostream>
using namespace std;

#include "XXX.h"


enum Choices
{
	EXIT,
	
	AAA,
	BBB,
	CCC,
	
	MENU = 100
};


void PrintChoices(void);

/*######################################################################*/



int main()
{
	
	
	
	PrintChoices();
	
	cout << endl << "Enter your choice: ";
	cin >> choice;
	
	while(choice)
	{
		
		switch(choice)
		{
		
//		case XX:
//			
//			
//			break;

//		case XX:
//			
//			
//			break;
		
//		case XX:
//			
//			
//			break;
		
		case MENU:
		
			PrintChoices();
			cout << endl;
			break;
			
		case EXIT:
		default:
		
			return 0;
			
		} // end switch
		
		cout << "Enter next choice (" << MENU << " for menu, " << EXIT << " to exit): ";
		cin >> choice;
	} // end choice
	
	return 0;
}


/*######################################################################*/

// print choices
void PrintChoices(void)
{
	//	cout << ": " << AAA << endl;
	//	cout << ": " << BBB << endl;
	//	cout << ": " << CCC << endl;

	cout << "Print menu: " << MENU << endl;
	cout << "Exit: " << EXIT << endl;
}
/*######################################################################*/

