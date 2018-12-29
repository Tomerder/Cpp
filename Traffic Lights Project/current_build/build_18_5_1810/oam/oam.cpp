// oam.cpp
//
//	What's this?
//	Author: Vladimir Krapp
//	Created on:
//	Last modified:


#include "system.h"
#include "oam.h"
#include "comm.h"
#include "config.h"
#include "log.h"


using namespace std;


OAM_t* OAM_t::m_instance;


OAM_t::OAM_t()
{
    m_running = false;
    m_comm = new CommService(IP_OAM, PORT_OAM);
    m_comm->AddPeer(EMULATION, IP_EMULATION, PORT_EMULATION);
    m_comm->SetMessageHandler(OAM_t::MsgHandler);
    m_instance = this;
}

OAM_t::~OAM_t()
{
    delete m_comm;
}


void 
OAM_t::
Start()
{
    m_running = true;
    while(m_running)
    {
        
    }
}


void 
OAM_t::
MsgHandler(const Msg* _msg)
{
    if(_msg->m_header.m_type == SIMULATION_MSG)
    {
        if(_msg->m_content.m_simMsg == READY)
        {
            Msg msg;
            msg.m_header.m_origin = OAM;
            msg.m_header.m_id = 1;
            msg.m_header.m_type = SIMULATION_MSG;
            msg.m_content.m_simMsg = START;
            msg.m_header.m_length = sizeof(msg.m_header) + sizeof(msg.m_content.m_simMsg);

            m_instance->m_comm->Send(EMULATION, msg);
        }
    }
    cout << "Got Msg" << endl;
}
