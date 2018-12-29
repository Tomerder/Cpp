// msg_queue.h
//
//	Author: Netali Setter 
//	Created on: 20.5.14
//	Last modified: 20.5.14

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
       
#include "system.h"

#define MSGQ_FILE "../Ainclude/system.h"
#define MSGQ_ID 172113

class MsgQueue
{
public:
	MsgQueue(SystemEntity _me);
	
	typedef struct MsgBuff
	{
		long m_type;
		Msg m_msg;
	}MsgBuff;
	
	void AddMsg(SystemEntity _destination, char* _msg, int _size);
	void PrintMsg();
	
private:
	static const int MAX_MSG_SIZE = 64;
	int m_id;
	MsgBuff m_receiveMsg;
	SystemEntity m_me;
	
	long m_msgType[5];
};













