#include <stdlib.h>
#include <stdio.h>

#include "log.h"
#include "system.h"
#include "comm.h"
#include "config.h"
#include "time.h"


#define CONFIG_FILE "config.txt"

#define NAME(event)        g_eventNames[(event)]
#define DEFAULT_VAL(event) "event"

#define DealWithPolice(event) \
	if(long(POLICE_CROSS_STATUS)==event )\
		g_PoliceInCross = !g_PoliceInCross;\
	else if(long(POLICE_CROSS_STATUS) < event && !g_PoliceInCross )\
		continue;

//*********************************
// default communication variable

std::string IP_OAM  = "192.168.1.111";
std::string IP_CONTROL = "192.168.1.130";
std::string IP_EMULATION = "192.168.1.54";
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

CommService* g_comm = 0;
Log* g_log = 0;

bool g_PoliceInCross = false;


void WaitForOAM()
{
	g_log->ToLog(Log::DEBUG, Message("WaitForOAM"));	
	pthread_cond_wait(&g_stopCMD, &g_mtx);
}


void ReadFromConfig()
{
	if( !ConfigRead(CONFIG_FILE) )
	{
		fprintf(stderr,"can't open configuration file");
	}
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
	
	// set event statistics
	for (int event = CAR_SENSOR_NORTH ; event < EVENT_NUM ; ++event)
	{
    	g_configData[event] = atoi( ConfigGet(NAME(event),DEFAULT_VAL(event)) );
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
			
	g_comm->Send(CONTROL, msg);  // TODO need to send to CONTROL
}


void RandomizeAndSendEvent(EmulationEvent _event)	
{
	long MeanTime = g_configData[_event];

	if( MeanTime && rand()%MeanTime == 0 )
	{
		SendEvent(_event);
	
		char msgToLog[32];
		sprintf(msgToLog, "event %d sent", int(_event));
		g_log->ToLog(Log::DEBUG, Message(msgToLog));
	}
}


void Handel_OAM_CMD(SimulationMsg _cmd)
{
	switch(_cmd)
	{
		case START:
		{
			g_log->ToLog(Log::DEBUG, Message("OAM sent START"));
			g_stop = 0;
			pthread_cond_signal(&g_stopCMD);
			break;
		}
		case PAUSE:
		{
			g_log->ToLog(Log::DEBUG, Message("OAM sent PAUSE"));
			g_stop = 1;
			break;
		}
		case SHUTDOWN:
		{
			g_log->ToLog(Log::NORMAL, Message("OAM sent SHUTDOWN"));
			exit(1);
		}
		default: g_log->ToLog(Log::DEBUG, Message("unknon OAM_CMD"));
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
			g_log->ToLog(Log::NORMAL, Message("OAM send EVENT to CONTROL"));
			g_comm->Send(CONTROL, *_msg);	
			break;
		}
		default: g_log->ToLog(Log::DEBUG, Message("uknon MsgType"));
	}
}


void Operate()
{
	while( 1 )
	{		
		sleep(1);

		for(int event = CAR_SENSOR_NORTH ; event < EVENT_NUM; ++event)
		{
			DealWithPolice(event); // macro
		
	    	RandomizeAndSendEvent(EmulationEvent(event));
	    }
	    
	    while( g_stop )
	    {

	    	g_log->ToLog(Log::NORMAL, Message("world emulation stoped"));
	    	WaitForOAM();
	    	g_log->ToLog(Log::NORMAL, Message("world emulation continued"));

	    }		
	}	
}


void FreePthreads(void)
{
	pthread_cond_destroy(&g_stopCMD);
	pthread_mutex_destroy(&g_mtx);
	delete g_log;
	delete g_comm;
}					

void Init()
{
	ReadFromConfig();
	
	g_comm = new CommService(IP_EMULATION, PORT_EMULATION);
	
	g_comm->SetMessageHandler(GetEventHandler);
	g_comm->AddPeer( OAM, IP_OAM, PORT_OAM );
	g_comm->AddPeer( CONTROL, IP_CONTROL, PORT_CONTROL );
	
	g_log = new Log(g_comm);
	
	if( pthread_cond_init(&g_stopCMD, 0) )
	{
		g_log->ToLog(Log::NORMAL, Message("pthread_cond_init fail"));
	}
	if( pthread_mutex_init(&g_mtx, 0) )
	{
		g_log->ToLog(Log::NORMAL, Message("pthread_mutex_init fail"));
	}
	atexit( FreePthreads );
	
	g_log->ToLog(Log::NORMAL, Message("world emulation finish initiation"));
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

	g_log->ToLog(Log::NORMAL, Message("sending READY"));		
	g_comm->Send(OAM, msg);
}
	

int main()
{
	srand(time(NULL));
	
	Init();

	MakeAndSendReadyMsgToAOM();
	
	WaitForOAM();
		
	Operate();

	return 0;
}

