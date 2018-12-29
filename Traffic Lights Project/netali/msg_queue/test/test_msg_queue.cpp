// test_msg_queue.cpp
//
//	Author: Netali Setter 
//	Created on: 20.5.14
//	Last modified: 20.5.14

#include <cstring>

#include "msg_queue.h"

int main()
{
	MsgQueue queue1(CONTROL);
	MsgQueue queue2(OAM);
	MsgQueue queue3(EMULATION);

	Msg msg;
	msg.m_header.m_type = EVENT_EMULATION;
	msg.m_content.m_emulationEvent = NORTH_SOUTH_STRAIGHT_AND_RIGHT;
	
	queue1.AddMsg(CONTROL, (char*)&msg, sizeof(msg));
	
	
	
	Msg msg2;
	msg2.m_header.m_type = SIMULATION_MSG;
	msg2.m_content.m_simMsg = START;
	
	queue2.AddMsg(OAM, (char*)&msg2, sizeof(msg2));
	
	
	
	Msg msg3;
	msg3.m_header.m_type = LOG;
	memcpy (&msg3.m_content.m_payload, "blablabla", sizeof ("blablabla"));
	
	queue3.AddMsg(EMULATION, (char*)&msg3, sizeof(msg3));

	
	queue2.PrintMsg();
	queue1.PrintMsg();
	queue3.PrintMsg();
	
	return 0;
}
