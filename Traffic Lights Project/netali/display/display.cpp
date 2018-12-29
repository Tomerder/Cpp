// display.cpp
//
//	What's this?
//	Author: Vladimir Krapp
//	Created on:
//	Last modified:

#include <ncurses.h>
#include <cstring>
#include <termios.h>
#include <sys/ioctl.h>

#include "display.h"

using namespace std;

void 
Display::SetUp()
{
    initscr();
    cbreak();
    noecho();

    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    init_pair(4, COLOR_WHITE, COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(6, COLOR_CYAN, COLOR_BLACK);
    
    init_pair(7, COLOR_YELLOW, COLOR_RED);
    init_pair(8, COLOR_YELLOW, COLOR_GREEN);
    init_pair(9, COLOR_YELLOW, COLOR_MAGENTA);
    init_pair(10, COLOR_BLACK, COLOR_BLACK);
    
}

void 
Display::ShutDown()
{
    endwin();
}

void
Display::ClearLights()
{
	erase();
	DrawRoads();
}

void 
Display::SetColor(Color _color)
{
    attron(COLOR_PAIR(_color));
}



Display::Display()
{
	memset (m_carWaitingState, 0, sizeof(int)*4);
	memset (m_pdWaitingState, 0, sizeof(int)*4);
}

void
Display::WriteAt(int _x, int _y, const char* _str)
{
    mvprintw(_x, _y, _str);
    refresh();
}

void
Display::Demo()
{
    char buff[128];

    getstr(buff);

    SetColor(Yellow);

    WriteAt(10, 10, buff);

    SetColor(White);

    getch();
}


void
Display::DrawRoads()
{
	struct winsize size;
	if (ioctl(0, TIOCGWINSZ, (char *) &size) < 0)
    	printf("TIOCGWINSZ error");

	SetColor(White);
	
	for (int i=0; i<size.ws_row; ++i)
	{
		WriteAt(i, size.ws_col/2 -10, "|");
	}
	
	for (int i=0; i<size.ws_row; ++i)
	{
		WriteAt(i, size.ws_col/2 +10, "|");
	}
	
	for (int i=0; i<size.ws_col; ++i)
	{
		WriteAt(size.ws_row/2 -4, i, "_");
	}
	
	for (int i=0; i<size.ws_col; ++i)
	{
		WriteAt(size.ws_row/2 +4, i, "_");
	}
	
	
}

					
					  	

void Display::SetCrossRoadMode(LightsState _mode)
{
	Color general = (_mode == ST_ORANGE) ? Yellow : Red;
	
	DrawLight(CAR_LIGHT_N_RIGHT, general);
	DrawLight(CAR_LIGHT_N_LEFT, general);
	DrawLight(CAR_LIGHT_S_RIGHT, general);
	DrawLight(CAR_LIGHT_S_LEFT, general);
	DrawLight(CAR_LIGHT_E_RIGHT, general);
	DrawLight(CAR_LIGHT_E_LEFT, general);
	DrawLight(CAR_LIGHT_W_RIGHT, general);
	DrawLight(CAR_LIGHT_W_LEFT, general);
	DrawLight(PD_LIGHT_N, general);
	DrawLight(PD_LIGHT_S, general);
	DrawLight(PD_LIGHT_E, general);
	DrawLight(PD_LIGHT_W, general);

	if (_mode == ST_ORANGE)
	{
		return;
	}
		
	switch(_mode)
	{
		case ST_NORTH_SOUTH_STRAIGHT_AND_RIGHT:
			{
				DrawLight(CAR_LIGHT_N_RIGHT, Green);
				DrawLight(PD_LIGHT_E, Green);
				DrawLight(CAR_LIGHT_S_RIGHT, Green);
				DrawLight(PD_LIGHT_W, Green);
			}
			break;
		case ST_EAST_WEST_STRAIGHT_AND_RIGHT:
			{
				DrawLight(CAR_LIGHT_W_RIGHT, Green);
				DrawLight(PD_LIGHT_S, Green);
				DrawLight(CAR_LIGHT_E_RIGHT, Green);
				DrawLight(PD_LIGHT_N, Green);
			}
			break;
		case ST_EAST_WEST_LEFT:
			{
				DrawLight(CAR_LIGHT_E_LEFT, Green);
				DrawLight(CAR_LIGHT_W_LEFT, Green);
			}
			break;
		case ST_NORTH_SOUTH_LEFT:
			{
				DrawLight(CAR_LIGHT_S_LEFT, Green);
				DrawLight(CAR_LIGHT_N_LEFT, Green);
			}
			break;
		default:
			break;
	}
}


void Display::DrawLight(Light _light, Color _color)
{
	struct winsize size;
	if (ioctl(0, TIOCGWINSZ, (char *) &size) < 0)
    	printf("TIOCGWINSZ error");
    	
    int y = -10;
    	
	switch (_light)
	{
		case CAR_LIGHT_S_RIGHT: DrawCarLightImp(size.ws_row/2-y/2, size.ws_col/2+7, _color);
			break;
		case CAR_LIGHT_S_LEFT: DrawCarLightImp(size.ws_row/2-y/2, size.ws_col/2+4, _color);
			break;
		case CAR_LIGHT_N_RIGHT: DrawCarLightImp(size.ws_row/2+y/2+1, size.ws_col/2-7, _color);
			break;
		case CAR_LIGHT_N_LEFT: DrawCarLightImp(size.ws_row/2+y/2+1, size.ws_col/2-4, _color);
			break;		
			
		case CAR_LIGHT_E_RIGHT: DrawCarLightImp(size.ws_row/2+3, size.ws_col/2-11, _color);
			break;
		case CAR_LIGHT_E_LEFT: DrawCarLightImp(size.ws_row/2+1, size.ws_col/2-11, _color);
			break;
		case CAR_LIGHT_W_RIGHT: DrawCarLightImp(size.ws_row/2-2, size.ws_col/2+11, _color);
			break;
		case CAR_LIGHT_W_LEFT: DrawCarLightImp(size.ws_row/2, size.ws_col/2+11, _color);
			break;
			
			
		case PD_LIGHT_W: DrawCrossingVertical(size.ws_row/2 -3, size.ws_row/2 +4, size.ws_col/2 -25, _color);
			break;
		case PD_LIGHT_E: DrawCrossingVertical(size.ws_row/2 -3, size.ws_row/2 +4, size.ws_col/2 +25, _color);
			break;
		case PD_LIGHT_S: DrawCrossingHorizontal(size.ws_row/2+12, size.ws_col/2+10, size.ws_col/2-10, _color);
			break;
		case PD_LIGHT_N: DrawCrossingHorizontal(size.ws_row/2-12, size.ws_col/2+10, size.ws_col/2-10, _color);
			break;
			

	
		default:
			break;
	}
	
}


void Display::DrawCrossingHorizontal(int _y, int _xLeft, int _xRight, Color _color)
{
	SetColor(_color);
	
	for (; _xRight <= _xLeft; ++_xRight)
	{
		WriteAt(_y, _xRight, "|");
		WriteAt(_y-1, _xRight, "|");
	}
}



void Display::DrawCrossingVertical(int _yTop, int _yBottom, int _x, Color _color)
{
	SetColor(_color);
	
	for (; _yTop <= _yBottom; ++_yTop)
	{
		WriteAt(_yTop, _x, "----");
	}
}


void Display::DrawCarLightImp(int _y, int _x, Color _color)
{    

	SetColor(Red_BG);
	WriteAt(_y, _x, " ");
	/*	
	WriteAt(_y, _x, "*");
	WriteAt(_y+1, _x, "*");
	WriteAt(_y-1, _x, "*");
	WriteAt(_y, _x+1, "*");
	WriteAt(_y, _x-1, "*");
	WriteAt(_y+1, _x+1, "*");
	WriteAt(_y-1, _x-1, "*");
	WriteAt(_y+1, _x-1, "*");
	WriteAt(_y-1, _x+1, "*");
	WriteAt(_y, _x+2, "*");
	WriteAt(_y, _x-2, "*");*/
}


void Display::DrawCarImp(int _y, int _x, Color _color, int _nCars)
{
	SetColor(_color);
	
	WriteAt(_y, _x+3, _nCars);
	
	WriteAt(_y, _x, " ");
	WriteAt(_y+1, _x, " ");
	WriteAt(_y, _x+1, " ");
	WriteAt(_y+1, _x+1, " ");
}


void Display::DrawCar(MovinEntity _entity, Color _color, int _nCars)
{
	struct winsize size;
	if (ioctl(0, TIOCGWINSZ, (char *) &size) < 0)
    	printf("TIOCGWINSZ error");
    	
	int y = -10;
	
	switch(_entity)
	{
		case NORTH:	DrawCarImp(size.ws_row/2+y/2-3, size.ws_col/2-5, _color, _nCars);
			break;
		case SOUTH:	DrawCarImp(size.ws_row/2-y/2+3, size.ws_col/2+4, _color, _nCars);
			break;
		case EAST:	DrawCarImp(size.ws_row/2+2, size.ws_col/2-16, _color, _nCars);
			break;
		case WEST:	DrawCarImp(size.ws_row/2-2, size.ws_col/2+16, _color, _nCars);
			break;
		
		default:
			break;
	}	

}

		

void
Display::HandlingDisplayMsg (CrossRoadStatus* _newState)
{
	if (_newState->m_lightState != m_currOnScreen.m_lightState)
	{
		SetCrossRoadMode(_newState->m_lightState);
	}
	
	
	int carsDiff = _newState->m_cars[NORTH] - m_currOnScreen.m_cars[NORTH];
	if (carsDiff == 0)
	{
		return; //continue;
	}
	
	if (_newState->m_cars[NORTH] == 0)
	{
		DrawCar(NORTH, m_deleteColor, );
	}
	else if (m_currOnScreen)
}

    

