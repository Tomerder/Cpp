/***************************************************************************
    Author: Stav Ofer
    Creation date:  		2013-11-06    
    Last modified date:		2013-11-06
    Description: 	
****************************************************************************/

#include <iostream>

#include "DevFactory.h"
#include "IBMFactory.h"

using namespace std;
using namespace IBM;


int main()
{
	DevFactory_t*	df = new IBMDeviceFactory_t;
	InputDevice*	Id1, Id2;
	Id1 = df->FInputDevice (MOUSE);
	Id2 = df->FInputDevice (JOYSTICK);
	
	if(Id1) {
		Id1->DisplayDevice ();
	}
	else {
		cout << "1: N/A" << endl;
	}
	
	if(Id2) {
		Id2->DisplayDevice ();
	}
	else {
		cout << "2: N/A" << endl;
	}
	
	delete df;
	delete Id1;
	delete Id2;
	
	return 0;
}

