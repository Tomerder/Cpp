// hardware.cpp
//
//	Implementation of the basic IO functions
//	Author: Netali Setter
//	Created on: 10/5/14
//	Last modified: 18/5/14


#include "hardware.h"

BYTE Hardware::HardwarePhysical[MAX_HARDWARE];

void* Hardware::ExcecuteTimersFuncsMicro (void* _args)
{
	Hardware* hardware = (Hardware*)_args;
	
	while(!hardware->m_isShutDown)
	{
		usleep(1);
		for (size_t i=0; i < hardware->m_microTickCounter; ++i)
		{
			hardware->InterruptEmulate(hardware->m_1MicroSecondTick[i]);
		}
	}
	
	return 0;
}


void* Hardware::ExcecuteTimersFuncsMilli (void* _args)
{
	Hardware* hardware = (Hardware*)_args;
	
	while(!hardware->m_isShutDown)
	{
		usleep(1000);
		for (size_t i=0; i < hardware->m_milliTickCounter; ++i)
		{
			hardware->InterruptEmulate(hardware->m_1MilliSecondTick[i]);
		}
	}
	
	return 0;
}


void* Hardware::ExcecuteTimersFuncsSec (void* _args)
{
	Hardware* hardware = (Hardware*)_args;
	
	while(!hardware->m_isShutDown)
	{
		sleep(1);
		for (size_t i=0; i < hardware->m_secondTickCounter; ++i)
		{
			hardware->InterruptEmulate(hardware->m_1SecondTick[i]);
		}
	}
	
	return 0;
}


void Hardware::InitInterrupts()
{
    //Shut all lines, when driver is established then we shall enable per each
   /* InterruptBind(SPI_DATA_READY_E);
	InterruptLineEnable(SPI_DATA_READY_E);
	InterruptBind(USB_DATA_READY_E);
	InterruptLineEnable(USB_DATA_READY_E);
	InterruptBind(SPI_DATA_READY_E);
	InterruptLineEnable(TIMER_1_E);
	InterruptBind(SPI_DATA_READY_E);
	InterruptLineEnable(TIMER_2_E);*/
}

void Hardware::InitTimerFunctions()
{
	m_microTickCounter = 0;
	m_milliTickCounter = 0;
	m_secondTickCounter = 0;
	
	pthread_create(&m_threadMicro, 0, Hardware::ExcecuteTimersFuncsMicro, this);
	pthread_create(&m_threadMilli, 0, Hardware::ExcecuteTimersFuncsMilli, this);
	pthread_create(&m_threadSec, 0, Hardware::ExcecuteTimersFuncsSec, this);
}


void Hardware::InitHardwarePorts()
{
	//initialize all - map to specific last
	for(int reg=0; reg<registerEnum_LAST; ++reg) 
	{
		MapRegister((RegisterEnum)reg, registerEnum_LAST); 
	}
	
	//Register all standard registers	 
	MapRegister(CAR_LIGHT_N_RIGHT_REG_E, CAR_LIGHT_N_RIGHT_REG_E+0x800);
	MapRegister(CAR_LIGHT_N_LEFT_REG_E, CAR_LIGHT_N_LEFT_REG_E+0x800);
	MapRegister(CAR_LIGHT_S_RIGHT_REG_E, CAR_LIGHT_S_RIGHT_REG_E+0x800);
	MapRegister(CAR_LIGHT_S_LEFT_REG_E, CAR_LIGHT_S_LEFT_REG_E+0x800);
	MapRegister(CAR_LIGHT_E_RIGHT_REG_E, CAR_LIGHT_E_RIGHT_REG_E+0x800);
	MapRegister(CAR_LIGHT_E_LEFT_REG_E, CAR_LIGHT_E_LEFT_REG_E+0x800);
	MapRegister(CAR_LIGHT_W_RIGHT_REG_E, CAR_LIGHT_W_RIGHT_REG_E+0x800);
	MapRegister(CAR_LIGHT_W_LEFT_REG_E, CAR_LIGHT_W_LEFT_REG_E+0x800);
	MapRegister(PD_LIGHT_N_REG_E, PD_LIGHT_N_REG_E+0x800);
	MapRegister(PD_LIGHT_S_REG_E, PD_LIGHT_S_REG_E+0x800);
	MapRegister(PD_LIGHT_E_REG_E, PD_LIGHT_E_REG_E+0x800);
	MapRegister(PD_LIGHT_W_REG_E, PD_LIGHT_W_REG_E+0x800);
	

	//Starts all registers shadows with zero
	for(int reg=0; reg<registerEnum_LAST; ++reg)
	{
		HardwareMap[reg].m_shadow= 0; 
	}

}


Hardware::Hardware()
{
    InterruptDisable();
    
	InitInterrupts();
	
	InitHardwarePorts();
	
	InitTimerFunctions();
	
	m_isShutDown = false;
	
	InterruptEnable();
}


Hardware::~Hardware()
{
	m_isShutDown = true;
	
	pthread_join(m_threadMicro, 0);
	pthread_join(m_threadMilli, 0);
	pthread_join(m_threadSec, 0);
}


void Hardware::MapRegister(RegisterEnum _register, size_t _address)
{
	HardwareMap[_register].m_address = _address;
}

int Hardware::Read(size_t _address)
{
	return HardwarePhysical[_address];
}

void Hardware::Write(size_t _address, int _data)
{
	HardwarePhysical[_address] = _data;
}

void Hardware::WriteWithShaddow(RegisterEnum _register, int _data)
{
	Write(HardwareMap[_register].m_address, _data);
    HardwareMap[_register].m_shadow= _data;
}

int Hardware::ReadShaddow(RegisterEnum _register)
{
	return HardwareMap[_register].m_shadow;
}

//add new entery to int.vector
void Hardware::InterruptBind(InterruptHandlerFunc _func, InterruptLineEnum _line)
{
	m_interruptVector[_line] = _func;
	//m_InterruptLinesStatus[_line] = true;	  ???
}

//execute int.handler
void Hardware::InterruptEmulate(InterruptLineEnum _line)
{
	if (m_areInterruptsEnabled && m_InterruptLinesStatus[_line])
	{
		m_interruptVector[_line]();
	}	
}

void Hardware::InterruptLineDisable(InterruptLineEnum _line)
{
	m_InterruptLinesStatus[_line] = false;
}

void Hardware::InterruptLineEnable(InterruptLineEnum _line)
{
	m_InterruptLinesStatus[_line] = true;
}

void Hardware::InterruptEnable()
{
	m_areInterruptsEnabled = true;
}

void Hardware::InterruptDisable()
{
	m_areInterruptsEnabled = true;
}


void Hardware::Bind_1MicroSecondTick(InterruptLineEnum _line)
{
	m_1MicroSecondTick[m_microTickCounter++] = _line;
}

void Hardware::Bind_1MilliSecondTick(InterruptLineEnum _line)
{
	m_1MilliSecondTick[m_milliTickCounter++] = _line;
}

void Hardware::Bind_1SecondTick(InterruptLineEnum _line)
{
	m_1SecondTick[m_secondTickCounter++] = _line;
}





/*********************Hardware Abstraction Layer*********************/


void CrossRoadeHal:: SetMode(CrossRoadeMode _mode)
{
	//check for special modes
	switch(_mode)
	{
		case ORANGE_MODE:
		{
			for (int i=0; i<Hardware::registerEnum_LAST; ++i)
			{
				m_hardware.Write(i, Hardware::ORANGE);
			}
		}
			break;
		
		case OFF_MODE:
		{
			for (int i=0; i<Hardware::registerEnum_LAST; ++i)
			{
				m_hardware.Write(i, Hardware::OFF);
			}
		}
			break;
		default:
			break;
	}
	
	//turn all lights off
	for (int i=0; i<Hardware::registerEnum_LAST; ++i)
	{
		m_hardware.Write(i, Hardware::RED);
	}
	
	//set new mode
	switch(_mode)
	{
		case NORTH_STRAIGHT_AND_RIGHT:
			{
				m_hardware.Write(Hardware::CAR_LIGHT_N_RIGHT_REG_E, Hardware::GREEN);
				m_hardware.Write(Hardware::PD_LIGHT_E_REG_E, Hardware::GREEN);
			}
			break;
		case WEST_STRAIGHT_AND_RIGHT:
			{
				m_hardware.Write(Hardware::CAR_LIGHT_W_RIGHT_REG_E, Hardware::GREEN);
				m_hardware.Write(Hardware::PD_LIGHT_N_REG_E, Hardware::GREEN);
			}
		case EAST_STRAIGHT_AND_RIGHT:
			{
				m_hardware.Write(Hardware::CAR_LIGHT_E_RIGHT_REG_E, Hardware::GREEN);
				m_hardware.Write(Hardware::PD_LIGHT_S_REG_E, Hardware::GREEN);
			}
			break;
		case SOUTH_STRAIGHT_AND_RIGHT:
			{
				m_hardware.Write(Hardware::CAR_LIGHT_S_RIGHT_REG_E, Hardware::GREEN);
				m_hardware.Write(Hardware::PD_LIGHT_W_REG_E, Hardware::GREEN);
			}
			break;
		case LEFT_TURN_EAST_WEST:
			{
				m_hardware.Write(Hardware::CAR_LIGHT_E_LEFT_REG_E, Hardware::GREEN);
				m_hardware.Write(Hardware::CAR_LIGHT_W_LEFT_REG_E, Hardware::GREEN);
			}
			break;
		case LEFT_TURN_NORTH_SOUTH:
			{
				m_hardware.Write(Hardware::CAR_LIGHT_S_LEFT_REG_E, Hardware::GREEN);
				m_hardware.Write(Hardware::CAR_LIGHT_N_LEFT_REG_E, Hardware::GREEN);
			}
			break;
		default:
			break;
	}

}






