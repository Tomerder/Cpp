/***************************************************************************
    Author: Stav Ofer
    Creation date:  		2013-11-07    
    Last modified date:		2013-11-07
    Description: 	convert decimal number to roman numerals
****************************************************************************/

#include <string>
#include <iostream>

#include "Interpreter.h"

using namespace std;



int main()
{
	Dec2Roman_t inter;
	int number;
	string result;
	
	cout << endl << "Enter a number between 1 and 3999, -1 to exit: ";
	cin >> number;
	
	
	while( number != -1 )
	{
		try
		{
			result = inter.interpret(number);
			cout << "In roman numerals: " << result << endl;
			inter.Clean();
		}
		catch(const char* excep) {
			cout << excep << endl;
		}
		
		cout << endl << "Enter a number between 1 and 3999, -1 to exit: ";
		cin >> number;
	}
	
	return 0;
}
