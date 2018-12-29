#include <iostream>
#include <string>

using namespace std;

//==========================================================================
// Abstract Devices
//==========================================================================

class InputDevice {
public:
	virtual void DisplayDevice () = 0 ;
};



class OutputDevice {
public:
	virtual void DisplayDevice () = 0 ;
};

//==========================================================================
// IBM Devices
//==========================================================================

class IBMKeyboard : public InputDevice {
public:
	void DisplayDevice () {
		cout << "IBMKeyboard" << endl ;
	} 
};

class IBMPrinter : public OutputDevice {
public:
	void DisplayDevice () {
		cout << "IBMPrinter" << endl; 
	}
};

//==========================================================================
// Samsung Devices
//==========================================================================

class SamsungMouse : public InputDevice {
public:
	void DisplayDevice () {
		cout << "SamsungMouse" << endl ;
	}
};

class SamsungMonitor : public OutputDevice {
public:
	void DisplayDevice () {
		cout << "SamsungMonitor" << endl ;
	}
};

//==========================================================================
// Abstract Factory
//==========================================================================

class DeviceFactory {
public:
	virtual  InputDevice*	   FInputDevice () = 0;
	virtual  OutputDevice* FOutputDevice () = 0;
};

//==========================================================================
// IBM Factory
//==========================================================================

class IBMDeviceFactory : public DeviceFactory {
public:
	InputDevice* FInputDevice () {
		return new IBMKeyboard ;
	}
	OutputDevice* FOutputDevice () {
		return new IBMPrinter ;
	}
};


//==========================================================================
// Samsung Factory
//==========================================================================

class SamsungDeviceFactory : public DeviceFactory {
public:
	InputDevice* FInputDevice () {
		return new SamsungMouse ;
	}
	OutputDevice* FOutputDevice () {
		return new SamsungMonitor ;
	}
};

//==========================================================================
// Application
//==========================================================================

int main() {
	DeviceFactory*	df = new IBMDeviceFactory;
	InputDevice*	Id;
	Id = df->FInputDevice ();
	Id->DisplayDevice ();

	delete df;
	return 0;
}
