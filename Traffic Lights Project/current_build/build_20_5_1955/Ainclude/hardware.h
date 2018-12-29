#define BYTE unsigned char 

#include <pthread.h>
#include <unistd.h>

#include "system.h"

class Hardware
{
public:
	typedef enum RegisterEnum{
		CAR_LIGHT_N_RIGHT_REG_E = 0,
		CAR_LIGHT_N_LEFT_REG_E,
		CAR_LIGHT_S_RIGHT_REG_E,
		CAR_LIGHT_S_LEFT_REG_E,
		CAR_LIGHT_E_RIGHT_REG_E,
		CAR_LIGHT_E_LEFT_REG_E,
		CAR_LIGHT_W_RIGHT_REG_E,
		CAR_LIGHT_W_LEFT_REG_E,
		
		PD_LIGHT_N_REG_E,
		PD_LIGHT_S_REG_E,
		PD_LIGHT_E_REG_E,
		PD_LIGHT_W_REG_E,
		
	  	registerEnum_LAST
	}RegisterEnum;
	
	enum LIGHT_STATE { OFF, RED, ORANGE, GREEN } ; 
	
	//replaced by EmulationEvent
	/*typedef enum InterruptLineEnum{
		SENSOR_CAR_N = 0,
		SENSOR_CAR_S,
		SENSOR_CAR_E,
		SENSOR_CAR_W,
		SENSOR_PD_N,
		SENSOR_PD_S,
		SENSOR_PD_W,
		SENSOR_PD_E,
		ORANGE_MODE_ON,
		ORANGE_MODE_OFF,
		POLICE_CONTROL_ON,
		POLICE_CONTROL_OFF,
		EVENT_NUM
	}EmulationEvent;*/
	
	Hardware();
	~Hardware();
	
	int Read(size_t _address);	
	void Write(size_t _address, int _data);
	
	int ReadShaddow(RegisterEnum _register);
	void WriteWithShaddow(RegisterEnum _register, int _data);
	
	void MapRegister(RegisterEnum _register, size_t _address);
	
	typedef void (*InterruptHandlerFunc)();
	
	//adds new entery to int.vector
	//Not safe if _line is already occupied. changes old handler to new
	void InterruptBind(InterruptHandlerFunc _func, EmulationEvent _line);
	
	//executes interrupt
	//for disabled interrupts -  no action
	void InterruptEmulate(EmulationEvent _line);
	
	void InterruptLineDisable(EmulationEvent _line);
	void InterruptLineEnable(EmulationEvent _line);
	void InterruptEnable();
	void InterruptDisable();
	
	void Bind_1MicroSecondTick(EmulationEvent _line);
	void Bind_1MilliSecondTick(EmulationEvent _line);
	void Bind_1SecondTick(EmulationEvent _line);
	
	//CallMeAtTime (Function, Time);
	
	typedef struct HardwareRegMap
	{
		size_t m_address;
		int m_shadow;
	}HardwareRegMap;
	
private:
	static const size_t MAX_HARDWARE = 5000;
	static const size_t MAX_INTERRUPTS = 256;
	
	HardwareRegMap HardwareMap[registerEnum_LAST];
	static BYTE HardwarePhysical[MAX_HARDWARE];
	InterruptHandlerFunc m_interruptVector[EVENT_NUM];
	bool m_InterruptLinesStatus[EVENT_NUM];
	
	EmulationEvent m_1MicroSecondTick[EVENT_NUM];
	size_t m_microTickCounter;
	EmulationEvent m_1MilliSecondTick[EVENT_NUM];
	size_t m_milliTickCounter;
	EmulationEvent m_1SecondTick[EVENT_NUM];
	size_t m_secondTickCounter;
	
	static void* ExcecuteTimersFuncsMicro (void* _args);
	static void* ExcecuteTimersFuncsMilli (void* _args);
	static void* ExcecuteTimersFuncsSec (void* _args);
	
	pthread_t m_threadMicro;
	pthread_t m_threadMilli;
	pthread_t m_threadSec;
	
	bool m_areInterruptsEnabled;
	bool m_isShutDown;
	
	/*Disable all interrupts before using*/
	void InitInterrupts();
	void InitHardwarePorts();
	void InitTimerFunctions();
};


/*********************Hardware Abstraction Layer*********************/

class CrossRoadeHal
{
public:
	typedef enum CrossRoadeMode{
		NORTH_STRAIGHT_AND_RIGHT,
		SOUTH_STRAIGHT_AND_RIGHT,
		EAST_STRAIGHT_AND_RIGHT,
		WEST_STRAIGHT_AND_RIGHT,
		LEFT_TURN_EAST_WEST,
		LEFT_TURN_NORTH_SOUTH,
		ORANGE_MODE,
		OFF_MODE
	}CrossRoadeMode;
	
	void SetMode(CrossRoadeMode _mode);
	
private:
	Hardware m_hardware;
};
