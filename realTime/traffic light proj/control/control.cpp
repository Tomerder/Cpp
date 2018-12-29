// control.cpp
//
//	What's this?
//	Author: Vladimir Krapp
//	Created on:
//	Last modified:

#include "control.h"

using namespace std;
//using namespace m10;

/*----------------------------------------------------------------------*/

Control* Control::m_control;

/*----------------------------------------------------------------------*/

Control::Control()  : m_secsOnCurState(0) //m_stateMachine( STATE_NUM  ,EVENT_NUM) , m_secsOnCurState(0)
{
	for (int i=0; i< COUNTER_CAR_NUM; i++){
		m_counterCars[i] = 0;
	}
	
	for (int i=0; i< COUNTER_PED_NUM; i++){
		m_counterPeds[i] = 0;
	}
	
	m_statesData[ST_NORTH_SOUTH_STRAIGHT_AND_RIGHT].m_secsLimit = 1;
	m_statesData[ST_NORTH_SOUTH_STRAIGHT_AND_RIGHT].m_nextState = ST_EAST_WEST_STRAIGHT_AND_RIGHT;
	
	m_statesData[ST_EAST_WEST_STRAIGHT_AND_RIGHT].m_secsLimit = 2;
	m_statesData[ST_EAST_WEST_STRAIGHT_AND_RIGHT].m_nextState = ST_NORTH_SOUTH_LEFT;
	
	m_statesData[ST_NORTH_SOUTH_LEFT].m_secsLimit = 3;
	m_statesData[ST_NORTH_SOUTH_LEFT].m_nextState = ST_EAST_WEST_LEFT;
	
	m_statesData[ST_EAST_WEST_LEFT].m_secsLimit = 4;
	m_statesData[ST_EAST_WEST_LEFT].m_nextState = ST_NORTH_SOUTH_STRAIGHT_AND_RIGHT;
}

/*----------------------------------------------------------------------*/

Control* Control::GetInstance()
{ 
	if (!m_control){
		m_control = new Control;
	}

	return m_control;
}
		

/*----------------------------------------------------------------------*/

//handles all events 
void EventHandler(EmulationEvent _event)
{
	cout << "EventHandler" << endl;
	
	switch (_event)
	{
		//cars sensors
		case CAR_SENSOR_NORTH:
			cout << "GOT CAR_SENSOR_NORTH" << endl;
			Control::GetInstance()->IncCar(NORTH_CAR);
			break;
		
		case CAR_SENSOR_SOUTH:
			cout << "GOT CAR_SENSOR_SOUTH" << endl;
			Control::GetInstance()->IncCar(SOUTH_CAR);
			break;
		
		case CAR_SENSOR_EAST:
			cout << "GOT CAR_SENSOR_EAST" << endl;
			Control::GetInstance()->IncCar(EAST_CAR);
			break;
			
		case CAR_SENSOR_WEST:
			cout << "GOT CAR_SENSOR_WEST" << endl;
			Control::GetInstance()->IncCar(WEST_CAR);
			break;
		
		//peds sensors
		case PD_SENSOR_NORTH:
			cout << "GOT PED_SENSOR_NORTH" << endl;
			Control::GetInstance()->IncPed(NORTH_PED);
			break;
		
		case PD_SENSOR_SOUTH:
			cout << "GOT PED_SENSOR_SOUTH" << endl;
			Control::GetInstance()->IncPed(SOUTH_PED);
			break;
		
		case PD_SENSOR_EAST:
			cout << "GOT PED_SENSOR_EAST" << endl;
			Control::GetInstance()->IncPed(EAST_PED);
			break;
			
		case PD_SENSOR_WEST:
			cout << "GOT PED_SENSOR_WEST" << endl;
			Control::GetInstance()->IncPed(WEST_PED);
			break;
	
		//orange 
		case POLICE_ORANGE:
		case ORANGE_MODE:
			cout << "ORANGE_MODE" << endl;
			Control::GetInstance()->SetCurState(ST_ORANGE);
	    	Control::GetInstance()->ZeroStateSecCount();
			break;
		
		//police change status
		case NORTH_SOUTH_STRAIGHT_AND_RIGHT:
			cout << "NORTH_SOUTH_STRAIGHT_AND_RIGHT" << endl;
			Control::GetInstance()->SetCurState(ST_NORTH_SOUTH_STRAIGHT_AND_RIGHT);
	    	Control::GetInstance()->ZeroStateSecCount();
			break;
		
		case EAST_WEST_STRAIGHT_AND_RIGHT:
			cout << "EAST_WEST_STRAIGHT_AND_RIGHT" << endl;
			Control::GetInstance()->SetCurState(ST_EAST_WEST_STRAIGHT_AND_RIGHT);
	    	Control::GetInstance()->ZeroStateSecCount();
			break;
		
		case NORTH_SOUTH_LEFT:
			cout << "NORTH_SOUTH_LEFT" << endl;
			Control::GetInstance()->SetCurState(ST_NORTH_SOUTH_LEFT);
	    	Control::GetInstance()->ZeroStateSecCount();
			break;
		
		case EAST_WEST_LEFT:
			cout << "EAST_WEST_LEFT" << endl;
			Control::GetInstance()->SetCurState(ST_EAST_WEST_LEFT);
	    	Control::GetInstance()->ZeroStateSecCount();
			break;	
			
			
			
		default:
			break;
	
	}

}

/*----------------------------------------------------------------------*/

void EventHandler_CAR_SENSOR_NORTH()
{
	cout << "EventHandler_CAR_SENSOR_NORTH" << endl;
	EventHandler(CAR_SENSOR_NORTH);
}

void EventHandler_CAR_SENSOR_SOUTH()
{
	EventHandler(CAR_SENSOR_SOUTH);
}

void EventHandler_CAR_SENSOR_EAST()
{
	EventHandler(CAR_SENSOR_EAST);
}

void EventHandler_CAR_SENSOR_WEST()
{
	EventHandler(CAR_SENSOR_WEST);
}

/*----------------*/

void EventHandler_PD_SENSOR_NORTH()
{
	cout << "EventHandler_CAR_SENSOR_NORTH" << endl;
	EventHandler(PD_SENSOR_NORTH);
}

void EventHandler_PD_SENSOR_SOUTH()
{
	EventHandler(PD_SENSOR_SOUTH);
}

void EventHandler_PD_SENSOR_EAST()
{
	EventHandler(PD_SENSOR_EAST);
}

void EventHandler_PD_SENSOR_WEST()
{
	EventHandler(PD_SENSOR_WEST);
}

/*----------------*/

void EventHandler_ORANGE_MODE()
{
	EventHandler(ORANGE_MODE);
}

void EventHandler_POLICE_CROSS_STATUS()
{
	EventHandler(POLICE_CROSS_STATUS);
}

void EventHandler_NORTH_SOUTH_STRAIGHT_AND_RIGHT()
{
	EventHandler(NORTH_SOUTH_STRAIGHT_AND_RIGHT);
}

void EventHandler_EAST_WEST_STRAIGHT_AND_RIGHT()
{
	EventHandler(EAST_WEST_STRAIGHT_AND_RIGHT);
}

void EventHandler_NORTH_SOUTH_LEFT()
{
	EventHandler(NORTH_SOUTH_LEFT);
}

void EventHandler_EAST_WEST_LEFT()
{
	EventHandler(EAST_WEST_LEFT);
}

void EventHandler_POLICE_ORANGE()
{
	EventHandler(POLICE_ORANGE);
}
/*----------------------------------------------------------------------*/

void Control::BindInterupts()
{	
	cout << "BindInterupts" << endl;

	cout << "EventHandler_CAR_SENSOR_NORTH :" << (unsigned)EventHandler_CAR_SENSOR_NORTH << endl; 

	m_hardware.InterruptBind(EventHandler_CAR_SENSOR_NORTH, CAR_SENSOR_NORTH); 
	m_hardware.InterruptBind(EventHandler_CAR_SENSOR_SOUTH, CAR_SENSOR_SOUTH);  
	m_hardware.InterruptBind(EventHandler_CAR_SENSOR_EAST, CAR_SENSOR_EAST);  
	m_hardware.InterruptBind(EventHandler_CAR_SENSOR_WEST, CAR_SENSOR_WEST);  
	
	m_hardware.InterruptBind(EventHandler_PD_SENSOR_NORTH, PD_SENSOR_NORTH); 
	m_hardware.InterruptBind(EventHandler_PD_SENSOR_SOUTH, PD_SENSOR_SOUTH);  
	m_hardware.InterruptBind(EventHandler_PD_SENSOR_EAST, PD_SENSOR_EAST);  
	m_hardware.InterruptBind(EventHandler_PD_SENSOR_WEST, PD_SENSOR_WEST);  
	
	
	m_hardware.InterruptBind(EventHandler_ORANGE_MODE, ORANGE_MODE);  
	m_hardware.InterruptBind(EventHandler_POLICE_CROSS_STATUS, POLICE_CROSS_STATUS);  
	m_hardware.InterruptBind(EventHandler_NORTH_SOUTH_STRAIGHT_AND_RIGHT, NORTH_SOUTH_STRAIGHT_AND_RIGHT);  
	m_hardware.InterruptBind(EventHandler_EAST_WEST_STRAIGHT_AND_RIGHT,  EAST_WEST_STRAIGHT_AND_RIGHT);  
	m_hardware.InterruptBind(EventHandler_NORTH_SOUTH_LEFT, NORTH_SOUTH_LEFT);  
	m_hardware.InterruptBind(EventHandler_EAST_WEST_LEFT, EAST_WEST_LEFT);   
	m_hardware.InterruptBind(EventHandler_POLICE_ORANGE, POLICE_ORANGE);   
}

/*----------------------------------------------------------------------*/

void Control::InitStateMachine()
{
	//TODO
	
}

/*----------------------------------------------------------------------*/


