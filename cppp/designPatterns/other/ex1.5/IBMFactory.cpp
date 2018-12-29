/***************************************************************************
    Author: Stav Ofer
    Creation date:  		2013-11-06    
    Last modified date:		2013-11-06
    Description: 	device factories - IBM
****************************************************************************/

#include <vector>
#include <algorithm>
#include <iostream>

#include "DevFactory.h"
#include "IBMFactory.h"

using namespace std;
using namespace IBM;



InputDevice* IBMDeviceFactory_t::FInputDevice(InputDevType _type)
{
	switch(_type)
	{
	case KEYBOARD:
		return IBMKeyboardFactory::FIBMKeyboard();
	
	case MOUSE:
		return IBMMouseFactory::FIBMMouse();
	
	default:
		return 0;
	}
}
//=======================================================================//

OutputDevice* IBMDeviceFactory_t::FOutputDevice(InputDevType _type)
{
	switch(_type)
	{
	case PRINTER:
		return IBMPrinterFactory::FIBMPrinter();
	
	case MONITOR:
		return IBMMonitorFactory::FIBMMonitor();
	
	default:
		return 0;
	}
}
//=======================================================================//


