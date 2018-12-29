/***************************************************************************
    Author: Stav Ofer
    Creation date:  		2013-11-06    
    Last modified date:		2013-11-06
    Description: 	Abstract device factory + abstract input/output dev classes
****************************************************************************/

#ifndef __DEV_FACTORY_H__
#define __DEV_FACTORY_H__


typedef enum InputDevType
{
	KEYBOARD,
	MOUSE,
	JOYSTICK
} InputDevType;

typedef enum OutputDevType
{
	MONITOR,
	PRINTER
} OutputDevType;


//=========================================================================
// 							Abstract Devices
//=========================================================================
class InputDevice
{
public:
	virtual void DisplayDevice () = 0 ;
};
//=========================================================================

class OutputDevice
{
public:
	virtual void DisplayDevice () = 0 ;
};
//=========================================================================


//=========================================================================
// 							Abstract Factory
//=========================================================================
class DevFactory_t
{
public:
	virtual  InputDevice*	FInputDevice (InputDevType _type) = 0;
	virtual  OutputDevice*	FOutputDevice (OutputDevType _type) = 0;
};
//=========================================================================


#endif  /* __DEV_FACTORY_H__ */
