#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include <iostream> // for Msg::Print

//=== DEBUG! Remove these when config module is installed =========

#include <string>

const size_t MAX_PAYLOAD_SIZE = 100;

const std::string IP_OAM  = "192.168.1.111";
const std::string IP_CONTROL = "127.0.0.1";
const std::string IP_EMULATION = "192.168.1.108";
const std::string IP_TEST = "127.0.0.1";

const int PORT_OAM = 6000;
const int PORT_CONTROL = 7000;
const int PORT_EMULATION = 8000;
const int PORT_TEST = 9000;


// System work mode, in production mode there is no Tester SystemEntity
enum SystemMode { PROD , TEST } ;

// all possible actors in the simulation
enum SystemEntity { OAM , CONTROL , EMULATION , TESTER } ;

enum SystemStatus { NORMAL, CRASH, POLICE_CONTROL } ;

enum Sensors { CAR1 ,CAR2 ,CAR3 ,CAR4 ,PD1 , PD2 , PD3 , PD4 } ;  

/*---------------------------------------------------------------*/
// Enums that can be the MsgContent

// Sent between the OA&M and the other stations, report and order change of simmulation mode
enum SimulationMsg { READY, START, SHUTDOWN, PAUSE } ;

/*---------------------------------------------------------------*/

// Enums for world emulation events
enum EmulationEvent{  
					   CAR1S=0, CAR2S, CAR3S, CAR4S,
					   PD1S , PD2S , PD3S , PD4S ,
					   POLICE_IN_CROSS ,
					   ORANGE_MODE     ,
					   
					   EVENT_NUM
					};

/*---------------------------------------------------------------*/

enum MsgType{ EVENT_EMULATION, SIMULATION_MSG, LOG , TRAFFIC_LIGHT_MAP } ;

typedef unsigned int MsgID;

typedef union        
{
    EmulationEvent  m_emulationEvent;
    SimulationMsg   m_simMsg;
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
