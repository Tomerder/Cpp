/***************************************************************************
    Author: Stav Ofer
    Creation date:  		2013-11-06    
    Last modified date:		2013-11-06
    Description: 	device factories - IBM
****************************************************************************/

#ifndef __IBM_FACTORY_H__
#define __IBM_FACTORY_H__

#include <iostream>

#include "DevFactory.h"


namespace IBM
{

using std::cout;
using std::endl;


//=========================================================================
// 								IBM Devices
//=========================================================================

//=============================== keyboard ==============================//
class IBMKeyboard : public InputDevice
{
public:
	void DisplayDevice () {
		cout << "IBMKeyboard" << endl ;
	} 
};

//================================ mouse ================================//
class IBMMouse : public InputDevice
{
public:
	void DisplayDevice () {
		cout << "IBMMouse" << endl ;
	} 
};


//=============================== printer ===============================//
class IBMPrinter : public OutputDevice
{
public:
	void DisplayDevice () {
		cout << "IBMPrinter" << endl; 
	}
};

//=============================== monitor ===============================//
class IBMMonitor : public OutputDevice
{
public:
	void DisplayDevice () {
		cout << "IBMMonitor" << endl; 
	}
};


//=========================================================================
// 								IBM Factory
//=========================================================================
class IBMDeviceFactory_t : public DevFactory_t
{
public:
	InputDevice*  FInputDevice( InputDevType  _type);	
	OutputDevice* FOutputDevice(OutputDevType _type);

//private:
//	static std::vector<InputDevType>	m_inputTypes  = {KEYBOARD, MOUSE};
//	static std::vector<OutputDevType>	m_outputTypes = {MONITOR, PRINTER};
};



//=========================================================================
// 							IBM Device Factories
//=========================================================================

//=============================== keyboard ==============================//
class IBMKeyboardFactory : public IBMDeviceFactory_t
{
public:
	IBMKeyboard* FIBMKeyboard()
	{
		return new IBMKeyboard;
	}
};

//================================ mouse ================================//
class IBMMouseFactory : public IBMDeviceFactory_t
{
public:
	IBMMouse* FIBMMouse()
	{
		return new IBMMouse;
	}
};

//=============================== printer ===============================//
class IBMPrinterFactory : public IBMDeviceFactory_t
{
public:
	IBMPrinter* FIBMPrinter()
	{
		return new IBMPrinter;
	}
};

//=============================== monitor ===============================//
class IBMMonitorFactory : public IBMDeviceFactory_t
{
public:
	IBMMonitor* FIBMMonitor()
	{
		return new IBMMonitor;
	}
};


}
//=========================== END namespace IBM =========================//


#endif  /* __IBM_FACTORY_H__ */
