// display.h
//
//	Display module for rt project
//	Author: Vladimir Krapp
//	Created on: 13/5/14
//	Last modified:

#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <ncurses.h>    

#include "system.h"

class Display
{
public:

    enum Color
    {
        Red     	= 1,
        Yellow  	= 2,
        Green  		= 3,
        White   	= 4,
        Magenta	 	= 5,
        Cyan		= 6,
        Red_BG		= 7,
        Green_BG	= 8,
        Magenta_BG	= 9,
        Black_BG	= 10
    };
    
    enum Light
    {
    	CAR_LIGHT_N_RIGHT = 0,
		CAR_LIGHT_N_LEFT,
		CAR_LIGHT_S_RIGHT,
		CAR_LIGHT_S_LEFT,
		CAR_LIGHT_E_RIGHT,
		CAR_LIGHT_E_LEFT,
		CAR_LIGHT_W_RIGHT,
		CAR_LIGHT_W_LEFT,
		
		PD_LIGHT_N,
		PD_LIGHT_S,
		PD_LIGHT_E,
		PD_LIGHT_W
    };
    
    Display();
    static void SetBackGround(Color _color);
    
 	static void HandlingDisplayMsg (LightsState _newState);
	
	static void ClearLights();
	static void SetCrossRoadMode(LightsState _mode);

    static void SetUp();
    static void ShutDown();
    static void SetColor(Color _color);
    static void WriteAt(int _x, int _y, const char* _str);

    static void Demo();
    
    static void DrawLight(Light _light, Color _color);
    static void DrawCrossingVertical(int _yTop, int _yBottom, int _x, Color _color);
    static void DrawCrossingHorizontal(int _y, int _xLeft, int _xRight, Color _color);
    
    static void DrawRoads();
    
    static void DrawCar(MovinEntity _entity, Color _color, int _nCars);
    static void DrawPD(MovinEntity _entity, Color _color);
    
    static void DrawCarImp(int _y, int _x, Color _color, int _nCars);

    
    static void DrawArrow();
    
    static void DrawCarLightImp(int _x, int _y, Color _color);
    
    void HandlingDisplayMsg (CrossRoadStatus* _newState);

private:
    
    CrossRoadStatus m_currOnScreen;
    
    int m_carWaitingState[4];
    int m_pdWaitingState[4];
    
    static const Color m_carColor = Magenta_BG;
    static const Color m_deleteColor = Black_BG;
    
}; // class Display


#endif //__DISPLAY_H__
