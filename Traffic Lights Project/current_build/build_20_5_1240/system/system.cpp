// system.cpp
//
//	System-wide global variables
//	Author: Vladimir Krapp
//	Created on:
//	Last modified:

#include "system.h"

// names of events, to print
const char* g_eventNames[] = {
		   "CAR1S", "CAR2S", "CAR3S", "CAR4S",
		   "PD1S" , "PD2S" , "PD3S" , "PD4S" ,
		   "ORANGE_MODE"  ,
		   "POLICE_CROSS_STATUS" ,
		   
		   "NORTH_SOUTH_STRAIGHT_AND_RIGHT",
		   "EAST_WEST_STRAIGHT_AND_RIGHT",
		   "NORTH_SOUTH_LEFT",
		   "EAST_WEST_LEFT",
		   
		   "POLICE_ORANGE", 
		   };



const char* g_simMsgNames[] = {
		   "READY", "START", "SHUTDOWN", "PAUSE"
};

