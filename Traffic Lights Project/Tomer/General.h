#ifndef _GENERAL_
#define _GENERAL_

/*---------------------------------------------------------------*/

typedef enum { PROD , TEST } SystemMode;

typedef enum { OFF, START, PAUSE } SystemCMD;

typedef enum { OAM , CONTROL , EMULATION , TESTER } SystemEnitity;

typedef enum { NORMAL, CRASH, POLICE } SystemStatus;

typedef enum { SENSOR_CHANGE , POLICE , CRASH } EventType;

typedef enum { CAR1 ,CAR2 ,CAR3 ,CAR4 ,PD1 , PD2 , PD3 , PD4 } Sensors;  

/*---------------------------------------------------------------*/

typedef enum { OAM_CMD, TRAFFIC_LIGHT_MAP, ,LOG , EVENT_EMULATION, IS_ALIVE } MsgType;

typedef unsigned int MsgID;

struct Msg
{
    struct 
    {
        SystemEntity    m_origin;       // Message originator
        MsgType         m_type;         // Message type
        MsgID           m_id;           // message ID, unique for each message from originator 
        size_t          m_length;       // Total message length: sizeof(m_header) + length of actual payload
    } m_header;

    char        m_payload[MAX_PAYLOAD_SIZE];
};

/*---------------------------------------------------------------*/

#endif  //GENERAL
