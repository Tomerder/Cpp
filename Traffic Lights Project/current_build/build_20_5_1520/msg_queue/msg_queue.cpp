// msg_queue.cpp
//
//	Author: Netali Setter 
//	Created on: 20.5.14
//	Last modified: 20.5.14

#include <iostream>
#include <cstring>

#include "msg_queue.h"

using namespace std;

MsgQueue::MsgQueue(SystemEntity _me)
{
	int key = ftok(MSGQ_FILE, MSGQ_ID);
	if (key == -1)
	{
		cout << "ftok failed" << endl;
	}
	
	m_id = msgget(key, 0666 | IPC_CREAT);
	if (m_id == -1)
	{
		cout << "msgget failed" << endl;
	}
	
	m_msgType[OAM] = 1;
	m_msgType[CONTROL] = 2;
	m_msgType[EMULATION] = 3;
	m_msgType[TESTER] = 4;
	m_msgType[DISPLAY] = 5;
	
	m_me = _me;
}

void MsgQueue::AddMsg(SystemEntity _destination, char* _msg, int _size)
{
	MsgBuff* msg = new MsgBuff;
	
	msg->m_type = m_msgType[_destination];
	
	memcpy(&msg->m_msg, _msg, _size);
	
 	if (msgsnd (m_id, msg, _size, 0) == -1)
    {
    	cout << "msgsnd failed" << endl;
    }
}

void MsgQueue::PrintMsg()
{
	if (msgrcv (m_id, &m_receiveMsg, sizeof(m_receiveMsg.m_msg), m_msgType[m_me], 0) == -1)
	{
		cout << "msgrcv failed" << endl;	
	}
	
	switch(m_receiveMsg.m_msg.m_header.m_type)
	{
		case EVENT_EMULATION: cout << g_eventNames[m_receiveMsg.m_msg.m_content.m_emulationEvent] << endl;
			break;
		case SIMULATION_MSG: cout << g_simMsgNames[m_receiveMsg.m_msg.m_content.m_simMsg] << endl;
			break;
		case LOG:	cout << m_receiveMsg.m_msg.m_content.m_payload << endl;
			break;
			
		default:
			break;
	}
}

