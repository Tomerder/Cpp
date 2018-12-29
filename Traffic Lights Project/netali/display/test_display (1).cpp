// display.cpp
//
//	What's this?
//	Author: Vladimir Krapp
//	Created on:
//	Last modified:

#include <CppUTest/TestHarness.h>
#include <CppUTest/CommandLineTestRunner.h>
#include <unistd.h>
#include <iostream>

#include "display.h"
#include "log.h"
#include "system.h"
#include "comm.h"
#include "config.h"


using namespace std;




/**************************************************************************/





int main(int argc, char** argv)
{
	Display::SetUp();

	Display::DrawRoads();

	Display::SetCrossRoadMode(ST_NORTH_SOUTH_STRAIGHT_AND_RIGHT);
	
	Display::DrawCar(NORTH, 1);
	Display::DrawCar(SOUTH,2 );
	Display::DrawCar(EAST, 3);
	Display::DrawCar(WEST, 4);
	
	
	/*	Display::DrawEntity(Display::CAR_LIGHT_E_RIGHT);
	Display::DrawEntity(Display::CAR_LIGHT_E_LEFT);
	Display::DrawEntity(Display::CAR_LIGHT_W_RIGHT);
	Display::DrawEntity(Display::CAR_LIGHT_W_LEFT);
	
	Display::DrawEntity(Display::CAR_LIGHT_S_RIGHT);
	Display::DrawEntity(Display::CAR_LIGHT_S_LEFT);
	Display::DrawEntity(Display::CAR_LIGHT_N_RIGHT);
	Display::DrawEntity(Display::CAR_LIGHT_N_LEFT);
	

	 
	
	*/
	
	
	
	
	/*int sleepTime = 300000;
	
	Display::SetCrossRoadMode(POLICE_ORANGE);
	usleep(sleepTime);
	Display::ClearLights();
	usleep(sleepTime);
	Display::SetCrossRoadMode(POLICE_ORANGE);
	usleep(sleepTime);
	Display::ClearLights();
	usleep(sleepTime);
	Display::SetCrossRoadMode(POLICE_ORANGE);
	usleep(sleepTime);
	Display::ClearLights();
	usleep(sleepTime);
	Display::SetCrossRoadMode(POLICE_ORANGE);
	usleep(sleepTime);
	Display::ClearLights();
	usleep(sleepTime);
	Display::SetCrossRoadMode(POLICE_ORANGE);
	usleep(sleepTime);
	Display::ClearLights();
	usleep(sleepTime*2);
	

	
	Display::SetCrossRoadMode(NORTH_SOUTH_STRAIGHT_AND_RIGHT);
	sleep(3);
	Display::SetCrossRoadMode(EAST_WEST_STRAIGHT_AND_RIGHT);
	sleep(3);
	Display::SetCrossRoadMode(NORTH_SOUTH_LEFT);
	sleep(3);	
	Display::SetCrossRoadMode(EAST_WEST_LEFT);*/

	
	
	

	getch();
	Display::ShutDown(); 
	
	
	return 0;
}
