/*---------------------------------------------------------------*/
/* Tomer Dery
/* Oven System
/*---------------------------------------------------------------*/
#define REG_HEAT_TEMP 0x1024      //heat temp from user 
#define REG_TIMER 0x2048		  //timer from user
#define REG_START_WORK 0x4096     
#define REG_TEMP_TUNE 1111        //tune temp  reg
#define REG_TIME_TUNE 2222        //tune timer reg
#define REG_TERMOSTAT 3333        
#define REG_HUMID_SENSOR 4444

/*---------------------------------------------------------------*/

typedef enum
{
	REG_TEMP_TUNE,     		//R
	REG_TIME_TUNE,     		//R
	REG_TERMOSTAT,     		//R
	REG_HUMID_SENSOR,		//R
	REG_HEAT_TEMP,			//R
	REG_TIMER,				//RW
	REG_START_WORK,			//RW
	REG_LAST
}Regs;

/*---------------------------------------------------------------*/

//every event will be activated by interupt handler on the interupt vector  
//example:  SM_EventHappened (StateTransMatrix , EVT_OVER_PWR) 
typedef enum
{
	EVT_ON_OFF,
	EVT_STOP,
	EVT_HEAT,
	EVT_TEMP_CNG,
	EVT_TIMER_CNG,
	EVT_OVER_HEAT,
	EVT_OVER_HUMID,
	EVT_OVER_PWR,
	EVT_LAST
}Events;

/*---------------------------------------------------------------*/

typedef enum
{
	STS_OFF,
	STS_WORK,
	STS_NOT_WORK,
	STS_LAST
}States;

/*---------------------------------------------------------------*/

typedef void (*Func)(void);

typedef struct MatrixEntry{
	States m_nextState;
	Func m_trnsFunc;
}

/*---------------------------------------------------------------*/

MatrixEntry StateTransMatrixEntries[STS_LAST][EVT_LAST];
/*
						STS_OFF,				STS_WORK,					STS_NOT_WORK,
	
	EVT_ON_OFF,			WORK					OFF							OFF
	EVT_STOP,			-						NOT_WORK					-
	EVT_HEAT,			-						-							TransFunc
	EVT_TEMP_CNG,		-						TransFunc					-
	EVT_TIMER_CNG,		-						TransFunc					-
	EVT_OVER_HEAT,		-						NOT_WORK + TransFunc		-
	EVT_OVER_HUMID,		-						NOT_WORK + TransFunc		-	
	EVT_OVER_PWR,		-						NOT_WORK + TransFunc		-
*/

/*---------------------------------------------------------------*/

void On_Entry_WORK()
{
	//write current time to REG_START_WORK 
}

void On_State_WORK()
{
	//set heat indicator (led) according to termostat
	//set humid indicator (led) according to humid sensor
	
	/*if ( REG_TIMER == 0 ){
	  	 turn off heater and fan 		  
	  }else{
		 turn on/off heater according to delta of tempature (REG_HEAT_TEMP - REG_TERMOSTAT)
		 turn on/off fan according to delta of tempature and humidity status (REG_HUMID_SENSOR)
	  }
	*/
}

/*---------------------------------------------------------------*/

void On_Entry_NOT_WORK()
{
	//turn off heater and fan 		 
}

/*---------------------------------------------------------------*/

void TransFunc_NOT_WORK_EVT_HEAT()
{
	//if ( not overHeat && not overHumid && not overPwr  ){
	//	  turn heater on 
	//    move to STS_WORK
	//}
}

/*---------------------------------------------------------------*/

void TransFunc_WORK_EVT_TEMP_CNG()
{
	//write updated temp to REG_HEAT_TEMP  :  0-400
}

/*---------------------------------------------------------------*/

void TransFunc_WORK_EVT_TIME_CNG()
{
	//write updated time to REG_TIMER  :  0-MAXTIME
}

/*---------------------------------------------------------------*/

void TransFunc_WORK_EVT_OVER_HEAT()
{
	//turn on emergency indicator
}

void TransFunc_WORK_EVT_OVER_HUMID()
{
	//turn on emergency indicator
}

void TransFunc_WORK_EVT_OVER_PWR()
{
	//turn on emergency indicator
}

/*---------------------------------------------------------------*/

void On_Entry_OFF()
{
	//turn off oven	 
}

/*---------------------------------------------------------------*/

void DoEveryMinute()
{
	/*if (StateTransMatrix->m_currentState == STS_WORK)
	  {
	      //write to REG_TIMER <- (REG_TIMER - 1)
	  }
	*/

	/*if ( not overHeat && not overHumid && not overPwr  ){
	  	  turn off emergency indicator 
	  } 
	*/
}

/*---------------------------------------------------------------*/

StateMachine* StateTransMatrix;

void SystemStartUp()
{
	StateTransMatrix = SM_Create( STS_LAST, EVT_LAST, StateTransMatrixEntries); 
	
	//fill up the matrix and states functions with the funcs ans transactions above 
	
	SM_GenerateTick(StateTransMatrix ,10);
}

//interupt -> interupt controler -> cpu -> interupt hundler
void InteruptHundler(Events _eventNum)
{
	SM_EventHappened (StateTransMatrix , EVT_OVER_PWR) ;
}

void SystemShutDown()
{
	StateTransMatrix = SM_Destroy(StateTransMatrix); 
	//fill up the matrix and states functions with the funcs ans transactions above 
}

/*---------------------------------------------------------------*/









