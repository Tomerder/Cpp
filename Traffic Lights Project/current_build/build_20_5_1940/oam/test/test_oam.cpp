// oam.cpp
//
//	What's this?
//	Author: Vladimir Krapp
//	Created on:
//	Last modified:

#include <iostream>
#include <vector>       // for menu options

#include <cstring>
#include <cstdlib>
#include <unistd.h> // for sleep, debuggin, REMOVE!


using namespace std;


#include "display.h"
#include "log.h"
#include "system.h"
#include "comm.h"
#include "config.h"
#include "menu.h"
#include "msg_queue.h"

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

//communication object
CommService* g_comm;

//int g_commInitiated = 1; // number of entities to wait for

int g_commInitiated = 2; // number of entities to wait for

// 
int g_displayMode = 0;

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


MsgQueue g_msg_queue(OAM);

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
		
	g_comm->Send(_dest, msg);
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
		
    cout << "Sending Event " << g_eventNames[_event] << endl;

	g_comm->Send(_dest, msg);
}

void HandleEvents(const Msg* _msg)
{
	
	if (!_msg)
	{
		cout << "Bad Msg" << endl;
	}
	
    if(g_commInitiated)
    {
        if(_msg->m_header.m_type != SIMULATION_MSG)
        {
            cout << "Comm not inited, waiting for SIMULATION_MSG" << endl;
            cout << "Got Msg. Type: " << _msg->m_header.m_type << endl;
            return;
        }
        if(_msg->m_content.m_simMsg != READY)
        {
            cout << "Comm not inited, waiting for READY" << endl;
            cout << "Got sim Msg. : " << _msg->m_content.m_simMsg << endl;
            return;
        }

        cout << "Got READY" << endl;

        sleep(1);

        g_commInitiated -= 1;

        if(!g_commInitiated)
        {
            cout << "Sending START" << endl;
            SendSimMsg(EMULATION, START);
            SendSimMsg(CONTROL, START);
        }
    }
    else
    {
        EmulationEvent event;
        switch (_msg->m_header.m_type)
        {
            case SIMULATION_MSG: // shouldn't get SIMULATION_MSG  
                cout << "Comm not inited, waiting for SIMULATION_MSG" << endl;
                break;

            case EVENT_EMULATION:
                event = _msg->m_content.m_emulationEvent;
                cout << "Got event: " << g_eventNames[event] << endl;
                break;

            case LOG:
                cout << "Got log " << endl;
                g_msg_queue.AddMsg(_msg->m_header.m_origin, (char*)_msg, sizeof(*_msg));
                break;

            case TRAFFIC_LIGHT_MAP:
                cout << "Got Light map: " << endl;
                if(g_displayMode)
                {
                    clear();
                    Display::SetCrossRoadMode(_msg->m_content.m_crossRoadStatus.m_lightState);
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
    g_comm = new CommService(IP_OAM ,PORT_OAM);	

	g_comm->SetMessageHandler(HandleEvents);cout << __LINE__ << endl;
	g_comm->AddPeer( EMULATION, IP_EMULATION, PORT_EMULATION );cout << __LINE__ << endl;
	g_comm->AddPeer( CONTROL, IP_CONTROL, PORT_CONTROL );cout << __LINE__ << endl;
	
    string menu_strings[] = {string("Run"), string("Start"), string("Stop"), string("Crash"), string("Inject event"), string("Display mode"), string("Exit") };
    Menu_t<string> oam_mainMenu(menu_strings, 7);
    
    vector<const char*> events(g_eventNames,g_eventNames + EVENT_NUM - 1); 
    Menu_t<const char*> events_menu(events);
        
    

    while(1)
    {
        int ch = oam_mainMenu.PresentMenu(); 
        int event_ch = 0;
        switch(ch)
        {
            case 1:
                cout << "Run" << endl;
                break;
            case 5:
                event_ch  = events_menu.PresentMenu();
                if(event_ch >=1 && event_ch <= EVENT_NUM)
                {
                    SendEvent(EMULATION, EmulationEvent(event_ch - 1));
                }
                break;
            case 6:
                Display::SetUp();
                g_displayMode = 1;

                getch();
                g_displayMode = 0;
                Display::ShutDown();
                getch();
                break;

            case 7:
                return 0;

            default:
                break;
        }

    }
	
	return 0;
}
