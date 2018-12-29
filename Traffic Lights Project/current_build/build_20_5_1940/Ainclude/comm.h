// comm.h
//
//	Communications module for RT project
//	Author: Vladimir Krapp
//	Created on: 12/5/14
//	Last modified:

#ifndef __REAL_TIME_COMM_H__
#define __REAL_TIME_COMM_H__

#include <cstddef>  // for size_t
#include <string>   // for passing IP as argument
#include <map>      // for container of <SystemEntity, TCPconnection>

#include "thread.h"   // for MessageThread

#include "tcp_ip.h" // for TCPconnection, TCPlistener

#include "system.h" // for systemwide definitions


//=== Constants and Definitions ===
const int LISTENER_QUEUE_SIZE = 5;

//enum SystemEntity
//{
//    SystemEntityFirst = 0x1,
//
//    TrafficControl  = 0x1,
//    OAM             = 0x2,
//    Emmulator       = 0x4,
//    AllPeers        = 0x8,
//
//    SystemEntityLast
//};
//
//


//=== struct Msg ===
// Defines the structure of the in-system messages

//enum MsgType
//{
//    MsgTypeBegin    = 0x1,
//
//    TestMessage     = 0x1,
//    EmmulationEvent = 0x2,
//    OAMmessage      = 0x4,
//
//    MsgTypeLast
//};
//

//typedef unsigned int MsgID;



//=== class CommService ===

typedef void (*MsgHandler)(const Msg* _msg);



class CommService
{
public:
    
    /*** CommService ************************************************/
    // CTOR
    //
    // Arguments: 	_IP - string with the IPv4 address of the machine
    //                    running the application 
    //              _port - port on which application listens for msgs.
    // 				
    CommService(std::string _IP, int _port);


    /*** ~CommService ***********************************************/
    // DTOR
    //
    ~CommService();



    /*** AddPeer ****************************************************/
    // Register and open a TCP connection to a peer 
    //
    // Arguments: 	 _peer - name of the system to communicate with
    //               _IP - string with the IPv4 address of the peer
    //               _port - port on which the peer listens for msgs.
    // 				
    // Result and Exceptions:
    //  on success:
    // 	on failure:	
    void AddPeer(SystemEntity _peer, std::string _IP, int _port);

    /*** Send *******************************************************/
    // Send message to a peer. Function is non-blocking. 
    // Messages are added to a circular buffer message queue. 
    // If buffer is full, message will overwrite the earliest 
    // message still in queue. 
    //
    // Arguments: 	_peer - name of the message recipient
    //              _msg - the message to send
    // 				
    // Result and Exceptions:
    //  on success:
    // 	on failure:	
    void Send(SystemEntity _peer, const Msg& _msg);


    /*** SetMessageHandler ******************************************/
    // Set the callback to be performed when a message is received by 
    // the system. 
    // No more messages will be received untill the callback returns.
    //
    // Arguments: 	_handler - 
    // 				
    // Result and Exceptions:
    //  on success:
    // 	on failure:	
    void SetMessageHandler(MsgHandler _handler);


    // ???
    void SetErrorHandler(MsgHandler _handler);

private:

    static void MsgAcceptLoop(CommService* _cs);
   
    Runnable* m_loop;
    Thread* m_thread;

    MsgHandler m_callback;

    TCPlistener*      m_listener;

    std::map<SystemEntity, Address> m_peers;

}; // class CommService

#endif //__REAL_TIME_COMM_H__
