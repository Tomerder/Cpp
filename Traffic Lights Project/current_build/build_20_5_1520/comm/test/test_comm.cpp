// comm.cpp
//
//	What's this?
//	Author: Vladimir Krapp
//	Created on:
//	Last modified:


#include <iostream>
#include <cstring>


#include "display.h"
#include "log.h"
#include "system.h"
#include "comm.h"
#include "config.h"


using namespace std;



#define CONFIG_FILE "../config.txt"



/* temp replacing OAM */
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
	
}



//communication object
CommService g_comm(IP_OAM, PORT_OAM);
int g_commInitiated = 1; // number of entities to wait for



/**************************************************************************/

void SendSimMsg(SystemEntity _dest, SimulationMsg _msg)
{
	Msg msg = { 
		{OAM,      // SystemEntity    m_origin
		SIMULATION_MSG, // MsgType         m_type
		0,              // MsgID           m_id
		sizeof(msg.m_header) + sizeof(SimulationMsg)}, // size
		{EmulationEvent(_msg)}  // MsgContent m_content
		};
		
	g_comm.Send(_dest, msg);
}

void SendEvent(SystemEntity _dest, EmulationEvent _event)
{
	Msg msg = { 
		{OAM,      // SystemEntity    m_origin
		EVENT_EMULATION, // MsgType         m_type
		0,              // MsgID           m_id
		sizeof(msg.m_header) + sizeof(EmulationEvent)}, // size
		{_event}  // MsgContent m_content
		};
		
	g_comm.Send(_dest, msg);
}

void HandleEvents(const Msg* _msg)
{
	cout << __LINE__ << endl;
	
	if (!_msg)
	{
		cout << "Bad Msg" << endl;
	}
	
    if(g_commInitiated)
    {
        if(_msg->m_header.m_type != SIMULATION_MSG)
        {
            cout << "Comm not inited, waiting for READY" << endl;
            return;
        }
        if(_msg->m_content.m_simMsg != READY)
        {
            cout << "Comm not inited, waiting for READY" << endl;
            return;
        }

        cout << "Got READY" << endl;

        SendSimMsg(CONTROL, START);

        cout << "Sending Event" << g_eventNames[CAR_SENSOR_NORTH] << endl;
        SendEvent(CONTROL, CAR_SENSOR_NORTH);

        g_commInitiated -= 1;
    }
    else
    {

        switch (_msg->m_header.m_type)
        {
            // shouldn't get SIMULATION_MSG  

            case EVENT_EMULATION:
            {
                cout << __LINE__ << endl;
                EmulationEvent event = _msg->m_content.m_emulationEvent;cout << __LINE__ << endl;
                cout << "Got event: " << g_eventNames[event] << endl;
            }
                break;
            default:
                break;
        }
    }// if (g_commInitiated)   
}


int main(int argc, char** argv)
{
    cout << __LINE__ << endl;
	ReadFromConfig();cout << __LINE__ << endl;
    // Create/Connect Msg Queue	
	


	//LogCreate("oa&m_log.txt" , LOG_MOD);
	
	g_comm.SetMessageHandler(HandleEvents);cout << __LINE__ << endl;
	g_comm.AddPeer( EMULATION, IP_EMULATION, PORT_EMULATION );cout << __LINE__ << endl;
	
    while(1)
    {
        sleep(1);

    }
	
	return 0;
}


//
//int main()
//{
//
//    cout << msg.m_header.m_length << endl;
//
//    CommService cs(IP_TEST, PORT_EMULATION);
//
//    cs.AddPeer(OAM, IP_OAM, PORT_OAM);
//    cs.AddPeer(EMULATION, IP_EMULATION, PORT_EMULATION);
//
//    cs.SetMessageHandler(HandleMsg);
//    cs.Send(OAM, msg);
//
//    sleep(4);
//
//    return 0;
//}
//
//
//

