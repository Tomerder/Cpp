// oam.cpp
//
//	What's this?
//	Author: Vladimir Krapp
//	Created on:
//	Last modified:

#include <iostream>

#include <cstring>
#include <cstdlib>
#include <unistd.h> // for sleep, debuggin, REMOVE!


using namespace std;


#include "display.h"
#include "log.h"
#include "system.h"
#include "comm.h"
#include "config.h"


using namespace std;

#define CONFIG_FILE "config.txt"

//TEST_GROUP(tg)
//{
//};
//
//TEST(tg, test_name)
//{
//    Display::SetUp();   
//    Display::Demo();
//    Display::ShutDown();   
//}



/* temp replacing OAM */
std::string IP_OAM  = "192.168.1.111";
std::string IP_CONTROL = "127.0.0.1";
std::string IP_EMULATION = "192.168.1.108";
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
CommService g_comm(IP_OAM, PORT_OAM);


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




/**************************************************************************/

void MakeAndSendReadyMsgToEmulator()
{
	Msg msg = { 
		{OAM,      // SystemEntity    m_origin
		SIMULATION_MSG, // MsgType         m_type
		0,              // MsgID           m_id
		sizeof(msg.m_header) + sizeof(SimulationMsg)}, // size
		{EmulationEvent(START)}  // MsgContent m_content
		};
		
	g_comm.Send(EMULATION, msg);
}


void HandleEvents(const Msg* _msg)
{
	cout << __LINE__ << endl;
	
	if (!_msg)
	{
		cout << "Bad Msg" << endl;
	}
	
	switch (_msg->m_header.m_type)
	{
		case SIMULATION_MSG:
		{
			if (_msg->m_content.m_simMsg == READY) cout << __LINE__ << endl;
				MakeAndSendReadyMsgToEmulator();cout << __LINE__ << endl;
		}
			break;
		case EVENT_EMULATION:
		{cout << __LINE__ << endl;
			EmulationEvent event = _msg->m_content.m_emulationEvent;cout << __LINE__ << endl;
	
			if (_msg->m_header.m_type == EVENT_EMULATION)
			{
				Display::SetCrossRoadMode(event);	cout << __LINE__ << endl;
			}
		}
			break;
		default:
			break;
	}	
}


int main(int argc, char** argv)
{cout << __LINE__ << endl;
	ReadFromConfig();cout << __LINE__ << endl;
	
	Display::SetUp();  cout << __LINE__ << endl;
	Display::DrawRoads();cout << __LINE__ << endl;
	
	//LogCreate("oa&m_log.txt" , LOG_MOD);
	
	g_comm.SetMessageHandler(HandleEvents);cout << __LINE__ << endl;
	g_comm.AddPeer( EMULATION, IP_EMULATION, PORT_EMULATION );cout << __LINE__ << endl;
	
	
	
	

	 
	
	
	
	
	
	
	/*int sleepTime = 300000;
	
	Display::SetCrossRoadMode(POLICE_ORANGE);
	usleep(sleepTime);
	Display::ClearLights();
	usleep(sleepTime);
	Display::SetCrossRoadMode(POLICE_ORANGE);
	usleep(sleepTime);
	Display::ClearLights();
	usleep(sleepTime);
	Display::SetCrossRoadMode(POLICE_ORANGE);
	usleep(sleepTime);
	Display::ClearLights();
	usleep(sleepTime);
	Display::SetCrossRoadMode(POLICE_ORANGE);
	usleep(sleepTime);
	Display::ClearLights();
	usleep(sleepTime);
	Display::SetCrossRoadMode(POLICE_ORANGE);
	usleep(sleepTime);
	Display::ClearLights();
	usleep(sleepTime*2);
	

	
	Display::SetCrossRoadMode(NORTH_SOUTH_STRAIGHT_AND_RIGHT);
	sleep(3);
	Display::SetCrossRoadMode(EAST_WEST_STRAIGHT_AND_RIGHT);
	sleep(3);
	Display::SetCrossRoadMode(NORTH_SOUTH_LEFT);
	sleep(3);	
	Display::SetCrossRoadMode(EAST_WEST_LEFT);*/

	
	
	

	//getch();
	//Display::ShutDown(); 
	
	while(1);

   // return CommandLineTestRunner::RunAllTests(argc, argv);
	return 0;
}
