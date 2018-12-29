#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "log.h"
#include "system.h"
#include "comm.h"
#include "config.h"

#include "control.h"

#define CONFIG_FILE "../config.txt"

#define NAME(event)        eventName[(event)]
#define DEFAULT_VAL(event) "event"

#define DealWithPolice(event) \
	if(long(POLICE_IN_CROSS)==event )\
		g_PoliceInCross = !g_PoliceInCross;\
	else if(!g_PoliceInCross && long(POLICE_IN_CROSS) < event )\
		continue;

using namespace std;

//*********************************
// default communication variable

std::string IP_OAM  = "127.0.0.1";
std::string IP_CONTROL = "127.0.0.1";
std::string IP_EMULATION = "127.0.0.1";
std::string IP_TEST = "127.0.0.1";

int PORT_OAM = 6000;
int PORT_CONTROL = 7000;
int PORT_EMULATION = 8000;
int PORT_TEST = 9000;

// default system mode

int SYSTEM_MODE = 1;

// default log mode

int LOG_MOD = 1;

//***********************************

long g_configData[EVENT_NUM];

int  g_stop = 0;

pthread_mutex_t g_mtx;
pthread_cond_t  g_stopCMD;

//initialize from ReadFromConfig 
CommService* g_comm;

bool g_PoliceInCross = false;

/*-------------------------------------------------------*/	

//control - contains hardware & stateMachine
//Control control;       => singletone 

/*-------------------------------------------------------*/	

void WaitForOAM()
{
	cout << "testControl::WaitForOAM" << endl;
	pthread_cond_wait(&g_stopCMD, &g_mtx);
	cout << "testControl::after WaitForOAM" << endl;
}

/*-------------------------------------------------------*/	

void ReadFromConfig()
{
	if( !ConfigRead(CONFIG_FILE) )
	{
		fprintf(stderr,"can't open configuration file");
	}
	// set log mode
	LOG_MOD = atoi( ConfigGet("LOG_MOD","1") );
	// set system mode
	SYSTEM_MODE  = atoi( ConfigGet("SYSTEM_MODE","1") );
    
    // set communication variables
	IP_OAM       = ConfigGet("IP_OAM",IP_OAM.c_str());
	IP_CONTROL   = ConfigGet("IP_CONTROL",IP_CONTROL.c_str());
	IP_EMULATION = ConfigGet("IP_EMULATION",IP_EMULATION.c_str());
	IP_TEST      = ConfigGet("IP_TEST",IP_TEST.c_str());

	PORT_OAM       = atoi( ConfigGet("PORT_OAM","6000") );
	PORT_CONTROL   = atoi( ConfigGet("PORT_CONTROL","7000") );
	PORT_EMULATION = atoi( ConfigGet("PORT_EMULATION","8000") );
	PORT_TEST      = atoi( ConfigGet("PORT_TEST","9000") );
	
	cout << "IP_OAM : " << IP_OAM << "   PORT_OAM : " << PORT_OAM << endl;
	
	g_comm = new CommService(IP_CONTROL, PORT_CONTROL);
	
}

/*-------------------------------------------------------*/	

void SendStateOAM()
{
	CrossRoadStatus statusToSend;

	statusToSend.m_lightState = (LightsState)Control::GetInstance()->GetCurState();  

	Msg msg;

	msg.m_header.m_origin = CONTROL;       // Message originator
    msg.m_header.m_type = TRAFFIC_LIGHT_MAP;         // Message type
    msg.m_header.m_id = 0;           // message ID, unique for each message from originator 
    msg.m_header.m_length = sizeof(msg.m_header) + sizeof(CrossRoadStatus); 

	msg.m_content.m_crossRoadStatus = statusToSend;

	g_comm->Send(OAM, msg);	
}

/*-------------------------------------------------------*/	

void HandleEvent(const Msg* _msg)	   //*-*
{
	//ToLog(LOG_MOD, Message(_msg));   
	
	EmulationEvent event = _msg->m_content.m_emulationEvent;      
	
	cout << "testControl::HandleEvent : " << event << endl;
	
	Control::GetInstance()->InterruptEmulate(event);
	
}

/*-------------------------------------------------------*/	

void Handel_OAM_CMD(SimulationMsg _cmd)
{
	cout << "testControl::Handel_OAM_CMD" << endl;
	
	switch(_cmd)
	{
		case START:
		{
			g_stop = 0;
			pthread_cond_signal(&g_stopCMD);
			break;
		}
		case PAUSE:
		{
			g_stop = 1;
			break;
		}
		case SHUTDOWN:
		{
			ToLog(LOG_MOD, Message("exit"));
			exit(1);
		}
		default: ToLog(LOG_MOD, Message("uknon OAM_CMD"));
	}	
}

/*-------------------------------------------------------*/		

void GetMsgHandler(const Msg* _msg)
{
	cout << "testControl::GetMsgHandler" << endl;

	switch( _msg->m_header.m_type )
	{
		case SIMULATION_MSG:
		{
			Handel_OAM_CMD(_msg->m_content.m_simMsg);
			break;
		}
		case EVENT_EMULATION:
		{
			HandleEvent(_msg);	
			break;
		}
		default: ToLog(LOG_MOD, Message("uknon MsgType"));
	}
}

/*-------------------------------------------------------*/	

void ReleaseCarPed(LightsState _curState)
{
	switch(_curState)
	{
		case ST_NORTH_SOUTH_STRAIGHT_AND_RIGHT:
			Control::GetInstance()->DecCar(NORTH_CAR);
			Control::GetInstance()->DecCar(SOUTH_CAR);
			Control::GetInstance()->DecPed(EAST_PED);
			Control::GetInstance()->DecPed(WEST_PED);
			break;
	
		case ST_EAST_WEST_STRAIGHT_AND_RIGHT:
			Control::GetInstance()->DecCar(EAST_CAR);
			Control::GetInstance()->DecCar(WEST_CAR);
			Control::GetInstance()->DecPed(NORTH_PED);
			Control::GetInstance()->DecPed(SOUTH_PED);
			break;
			
		case ST_NORTH_SOUTH_LEFT:
			Control::GetInstance()->DecCar(NORTH_CAR);
			Control::GetInstance()->DecCar(SOUTH_CAR);
			break;
			
		case ST_EAST_WEST_LEFT:
			Control::GetInstance()->DecCar(EAST_CAR);
			Control::GetInstance()->DecCar(WEST_CAR);
			break;
			
		default:
			break;
	}
}

/*-------------------------------------------------------*/	

void Operate()
{
	cout << "testControl::Operate" << endl;

	while( 1 )
	{		
		sleep(1);
	    
	    //stop from OAM
	    while( g_stop )
	    {
	    	ToLog(LOG_MOD, Message("world emulation stoped"));
	    	WaitForOAM();
	    	ToLog(LOG_MOD, Message("world emulation continued"));
	    }	
	    
	    /*------------------flow ---------------------------------------------*/
	    Control::GetInstance()->IncCurStateSecCount();
	    
	    LightsState curState = Control::GetInstance()->GetCurState();
	    StateData curStateData = Control::GetInstance()->GetStateData(curState);
	    
	    //if time limit has passed
	    if ( curStateData.m_secsLimit   <=   Control::GetInstance()->GetSecsOnCurState()  ){
	    	//to next state
	    	Control::GetInstance()->SetCurState(curStateData.m_nextState);
	    	Control::GetInstance()->ZeroStateSecCount();
	    	
	    	//release ped and car on green 
	    	ReleaseCarPed(curState);	
	    }
	      
	    /*------------------send status to OAM ------------------------------*/
	    SendStateOAM();	
	}	
}

/*-------------------------------------------------------*/	

void FreePthreads(void)
{
	pthread_cond_destroy(&g_stopCMD);
	pthread_mutex_destroy(&g_mtx);
}

/*-------------------------------------------------------*/						

void Init()
{
	cout << "testControl::Init" << endl;

	ReadFromConfig();
	
	g_comm->SetMessageHandler(GetMsgHandler);
	g_comm->AddPeer( OAM, IP_OAM, PORT_OAM );
	
	LogCreate("config_log.txt" , LOG_MOD);
	
	if( pthread_cond_init(&g_stopCMD, 0) )
	{
		ToLog(LOG_MOD, Message("pthread_cond_init fail"));
	}
	if( pthread_mutex_init(&g_mtx, 0) )
	{
		ToLog(LOG_MOD, Message("pthread_mutex_init fail"));
	}
	atexit( FreePthreads );
	
	//control - contains hardware & stateMachine  *-*
	
	Control::GetInstance()->BindInterupts();
	
	Control::GetInstance()->InitStateMachine();
	
}

/*-------------------------------------------------------*/	

void MakeAndSendReadyMsgToAOM()
{
	Msg msg;

	msg.m_header.m_origin = CONTROL;       // Message originator
    msg.m_header.m_type = SIMULATION_MSG;         // Message type
    msg.m_header.m_id = 0;           // message ID, unique for each message from originator 
    msg.m_header.m_length = sizeof(msg.m_header) + sizeof(SimulationMsg); 
	
	msg.m_content.m_simMsg = READY;
		
	g_comm->Send(OAM, msg);
}

/*-------------------------------------------------------*/	

int main()
{
	Init();
	
	MakeAndSendReadyMsgToAOM();
	
	WaitForOAM();
		
	Operate();

	return 0;
}

