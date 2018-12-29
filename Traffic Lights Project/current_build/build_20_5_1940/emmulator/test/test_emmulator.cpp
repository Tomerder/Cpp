#include <stdlib.h>
#include <iostream>

#include "log.h"
#include "system.h"
#include "comm.h"
#include "config.h"

#define CONFIG_FILE std::string("config.txt")
#define LOG_MOD     LOG_DEBUG
#define DEFAULT_VAL "2"


#define NAME(event)  eventName[(event)]

using namespace std;


long g_configData[EVENT_NUM];

int  g_stop = 0;

pthread_mutex_t g_mtx;
pthread_cond_t  g_stopCMD;

CommService* g_comm;


const char* eventName[32] = {
		   "CAR1S", "CAR2S", "CAR3S", "CAR4S",
		   "PD1S" , "PD2S" , "PD3S" , "PD4S" ,
		   "POLICE_IN_CROSS" ,
		   "ORANGE_MODE"
		   };


void WaitForOAM()
{
	pthread_cond_wait(&g_stopCMD, &g_mtx);
}


void ReadFromConfig(std::string file, long* data)
{
	for (int event = CAR1S ; event < EVENT_NUM ; ++event)
	{
    	g_configData[event] = atoi( ConfigGet(NAME(event),DEFAULT_VAL) );
    }
}

void SendEvent(EmulationEvent _event)
{
	Msg msg = { 
		{EMULATION,       // SystemEntity    m_origin
		EVENT_EMULATION, // MsgType         m_type
		0,               // MsgID           m_id
		sizeof(msg.m_header) + sizeof(EmulationEvent)}, // size
		{_event}  // MsgContent m_content
		};	

	g_comm.Send(CONTROL, msg);	
}


void RandomizeAndSendEvent(EmulationEvent _event)	
{
	long MeanTime = g_configData[_event];

	if( MeanTime && rand()%MeanTime == 0 )
	{
		SendEvent(_event);
	}
}


void Handel_OAM_CMD(SimulationMsg _cmd)
{
	switch(_cmd)
	{
		case START:
		{
            cout << "Got START msg." << endl;
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

	

void GetEventHandler(const Msg* _msg)
{
	switch( _msg->m_header.m_type )
	{
		case SIMULATION_MSG:
		{

			Handel_OAM_CMD(_msg->m_content.m_simMsg);
			break;
		}
		case EVENT_EMULATION:
		{
			g_comm.Send(CONTROL, *_msg);	
			break;
		}
		default: ToLog(LOG_MOD, Message("uknon MsgType"));
	}
}


void Operate()
{
	while( 1 )
	{		
		sleep(1);
		
		for(int event = CAR1S ; event < EVENT_NUM; ++event)
		{
	    	RandomizeAndSendEvent(EmulationEvent(event));
	    }
	    
	    while( g_stop )
	    {
	    	WaitForOAM();
	    }		
	}	
}



void FreePthreads(void)
{
	pthread_cond_destroy(&g_stopCMD);
	pthread_mutex_destroy(&g_mtx);
}

					

void Init()
{
	ReadFromConfig(CONFIG_FILE, g_configData);
	
	g_comm->SetMessageHandler(GetEventHandler);

	g_comm->AddPeer(OAM, IP_OAM, PORT_OAM);

	LogCreate("world_emu_log.txt" , LOG_MOD);
	
	if( pthread_cond_init(&g_stopCMD, 0) )
	{
		ToLog(LOG_MOD, Message("pthread_cond_init fail"));
	}
	if( pthread_mutex_init(&g_mtx, 0) )
	{
		ToLog(LOG_MOD, Message("pthread_mutex_init fail"));
	}
	atexit( FreePthreads );
}

void MakeAndSendReadyMsgToAOM()
{
	Msg msg = { 
		{EMULATION,      // SystemEntity    m_origin
		SIMULATION_MSG, // MsgType         m_type
		0,              // MsgID           m_id
		sizeof(msg.m_header) + sizeof(SimulationMsg)}, // size
		{EmulationEvent(READY)}  // MsgContent m_content
		};
		
	g_comm.Send(OAM, msg);
}
	

int main()
{
	Init();
	
	MakeAndSendReadyMsgToAOM();
	
	WaitForOAM();
		
	Operate();

	return 0;
}

