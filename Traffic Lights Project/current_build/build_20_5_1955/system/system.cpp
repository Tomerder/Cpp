// system.cpp
//
//	System-wide global variables
//	Author: Vladimir Krapp
//	Created on:
//	Last modified:

#include "system.h"

// names of events, to print
const char* g_eventNames[] = {
		   "CAR_SENSOR_NORTH", "CAR_SENSOR_SOUTH", 
		   "CAR_SENSOR_EAST" , "CAR_SENSOR_WEST",
		   "PD_SENSOR_NORTH" , "PD_SENSOR_SOUTH" , 
		   "PD_SENSOR_EAST" , "PD_SENSOR_WEST" ,
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

const char* g_stateNames[] = {
              "ST_NORTH_SOUTH_STRAIGHT_AND_RIGHT",
		      "ST_EAST_WEST_STRAIGHT_AND_RIGHT",
		      "ST_NORTH_SOUTH_LEFT",
		      "ST_EAST_WEST_LEFT",
		
		      "ST_POLICE_ORANGE", 
};
