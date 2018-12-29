#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include <iostream> // for Msg::Print

//=== DEBUG! Remove these when config module is installed =========

#include <string>

const size_t MAX_PAYLOAD_SIZE = 100;


// System work mode, in production mode there is no Tester SystemEntity
enum SystemMode { PROD , TEST } ;

// all possible actors in the simulation
enum SystemEntity { OAM , CONTROL , EMULATION , TESTER, DISPLAY} ;

enum SystemStatus { NORMAL, CRASH, POLICE_CONTROL } ;  

/*---------------------------------------------------------------*/
// Enums that can be the MsgContent

// Sent between the OA&M and the other stations, report and order change of simmulation mode
enum SimulationMsg { READY, START, SHUTDOWN, PAUSE } ;

/*---------------------------------------------------------------*/

// Enums for world emulation events
enum EmulationEvent{  
					   CAR_SENSOR_NORTH=0, CAR_SENSOR_SOUTH, CAR_SENSOR_EAST, CAR_SENSOR_WEST,
					   PD_SENSOR_NORTH , PD_SENSOR_SOUTH , PD_SENSOR_EAST , PD_SENSOR_WEST ,
					   ORANGE_MODE     ,
					   POLICE_CROSS_STATUS,
					   
					   NORTH_SOUTH_STRAIGHT_AND_RIGHT,
					   EAST_WEST_STRAIGHT_AND_RIGHT,
					   NORTH_SOUTH_LEFT,
					   EAST_WEST_LEFT,
					
					   POLICE_ORANGE, 
					   	   
					   EVENT_NUM
					};


extern const char* g_eventNames[];
extern const char* g_simMsgNames[];
extern const char* g_stateNames[];

/*---------------------------------------------------------------*/

enum LightsState {
	 ST_NORTH_SOUTH_STRAIGHT_AND_RIGHT,
     ST_EAST_WEST_STRAIGHT_AND_RIGHT,
     ST_NORTH_SOUTH_LEFT,
     ST_EAST_WEST_LEFT,
     ST_ORANGE, 
     STATE_NUM
};

enum MovinEntity { NORTH, SOUTH, EAST, WEST, LAST_MOVING_ENTITY};

struct CrossRoadStatus
{
	LightsState m_lightState;
	int m_cars[LAST_MOVING_ENTITY];
	int m_pedestrians[LAST_MOVING_ENTITY];
};
	
/*---------------------------------------------------------------*/

enum MsgType{ EVENT_EMULATION, SIMULATION_MSG, LOG, TRAFFIC_LIGHT_MAP } ;

typedef unsigned int MsgID;

typedef union        
{
    EmulationEvent  m_emulationEvent;
    SimulationMsg   m_simMsg;
    CrossRoadStatus m_crossRoadStatus;
    char            m_payload[MAX_PAYLOAD_SIZE];
} MsgContent;

// Msg manipulation functions are declared in comm.h and defined in comm.cpp
struct Msg
{

    struct 
    {
        SystemEntity    m_origin;       // Message originator
        MsgType         m_type;         // Message type
        MsgID           m_id;           // message ID, unique for each message from originator 
        size_t          m_length;       // Total message length: sizeof(m_header) + length of actual payload
    } m_header;

    MsgContent m_content;
};


/*---------------------------------------------------------------*/

#endif  //GENERAL
