// log_display.cpp
//
//	Author: Netali Setter 
//	Created on: 20.5.14
//	Last modified: 20.5.14
//
//Log Display for different entities
//Give flag when running test 1,2,3
// 1 = OAM
// 2 = CONTROL
// 3 = EMULATION


#include <stdlib.h>

#include "msg_queue.h"

using namespace std;

int main(int argc, char* argv[])
{
	MsgQueue* queue = 0;
	
	int entity = atoi(argv[1]);
	
	switch (entity)
	{
		case 1: queue = new MsgQueue(OAM);
			break;
		case 2: queue = new MsgQueue(CONTROL);
			break;
		case 3: queue = new MsgQueue(EMULATION);
			break;
			
		default:
			{
				cout << "Bad Entity. please insert 1, 2 or 3" << endl;
				return 0;
			}
	}
	
	while (1)
	{
		queue->PrintMsg();
	}

	
	delete queue;	
}

