// comm.cpp
//
//	What's this?
//	Author: Vladimir Krapp
//	Created on:
//	Last modified:

#include "comm.h"

#include <iostream> // for debug prints and logging
#include <cstring>  // for memcopy

using namespace std;

//=============================================================

CommService::
CommService(string _IP, int _port)
{
    Address addr(_IP, _port);

    m_listener = TCPlistener::Create(&addr, LISTENER_QUEUE_SIZE);

}

CommService::
~CommService()
{
    // close listenning socket
    delete m_listener;
    // +
    // cancel listenning thread
    m_thread->Cancel(); 
    // close peer connections

}

void 
CommService::
AddPeer(SystemEntity _peer, std::string _IP, int _port)
{
    // Create TCPconnection
    Address addr(_IP, _port);

    m_peers.insert(make_pair(_peer, addr));
}


void 
CommService::
Send(SystemEntity _peer, const Msg& _msg)
{
    map<SystemEntity, Address>::iterator itr = m_peers.find(_peer);
    if(itr == m_peers.end())
    {
        // log error, throw exception, etc.
        cout << "No such peer" << endl;
    }
    
    Address addr = itr->second;

    TCPconnection* peer = TCPconnection::Create(&addr);

    peer->Send((char*)&_msg, _msg.m_header.m_length);
}



void
CommService::
SetMessageHandler(MsgHandler _handler)
{
    // Store _handler
    m_callback = _handler;
    
    // Create listener thread data structure
    m_loop = new FunctionWrapper<void, CommService*, CommService::MsgAcceptLoop>(this);
    
    // Start listener thread with data structure
    m_thread = new Thread(m_loop);
}



void
CommService::MsgAcceptLoop(CommService* _cs)
{
    while(1)
    {
        cout << "MsgAcceptorLoop Running" << endl;     
        TCPconnection* peerIncoming  = _cs->m_listener->Accept();
        
        cout << "MsgAcceptorLoop got peer connection" << endl;     
        Msg msg;

        peerIncoming->Recv(reinterpret_cast<char*>(&msg), sizeof(msg));

        _cs->m_callback(&msg);

        delete peerIncoming;
    }
}




