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

void Display::DrawArrow()
{

	struct winsize size;
	if (ioctl(0, TIOCGWINSZ, (char *) &size) < 0)
    	printf("TIOCGWINSZ error");
    	
	SetColor(Green);
	
	int y = -10;
	WriteAt(size.ws_row/2-y, size.ws_col/2+3, "*");
	WriteAt(size.ws_row/2+1-y, size.ws_col/2+3, "*");
	WriteAt(size.ws_row/2+2-y, size.ws_col/2+3, "*");
	WriteAt(size.ws_row/2+3-y, size.ws_col/2+3, "*");
	WriteAt(size.ws_row/2+4-y, size.ws_col/2+3, "*");
	WriteAt(size.ws_row/2+5-y, size.ws_col/2+3, "*");
	
	//WriteAt(size.ws_row/2-y, size.ws_col/2+3+1, "\\");
	//WriteAt(size.ws_row/2-y, size.ws_col/2+3-1, "/");
	//WriteAt(size.ws_row/2+1-y, size.ws_col/2+3+2, "\\");
	//WriteAt(size.ws_row/2+1-y, size.ws_col/2+3-2, "/");
	
	WriteAt(size.ws_row/2+3-y, size.ws_col/2+3+1, "*");
	WriteAt(size.ws_row/2+3-y, size.ws_col/2+3+2, "*");
	WriteAt(size.ws_row/2+3-y, size.ws_col/2+3+3, "*");
	WriteAt(size.ws_row/2+3-y, size.ws_col/2+3+4, "*");
	WriteAt(size.ws_row/2+3-y, size.ws_col/2+3+5, "*");
	
	WriteAt(size.ws_row/2-y, size.ws_col/2-3, "*");
	WriteAt(size.ws_row/2+1-y, size.ws_col/2-3, "*");
	WriteAt(size.ws_row/2+2-y, size.ws_col/2-3, "*");
	WriteAt(size.ws_row/2+3-y, size.ws_col/2-3, "*");
	WriteAt(size.ws_row/2+4-y, size.ws_col/2-3, "*");
	WriteAt(size.ws_row/2+5-y, size.ws_col/2-3, "*");
	
	WriteAt(size.ws_row/2-y, size.ws_col/2-4, "*");
	WriteAt(size.ws_row/2-y, size.ws_col/2-5, "*");
	WriteAt(size.ws_row/2-y, size.ws_col/2-6, "*");
	WriteAt(size.ws_row/2-y, size.ws_col/2-7, "*");
	
	
	//DrawLight2(size.ws_row/2-y/2, size.ws_col/2+4);
	//DrawLight2(size.ws_row/2-y/2, size.ws_col/2-4);
		
}


					
					  	

void Display::SetCrossRoadMode(EmulationEvent _mode)
{
	Color general = (_mode == POLICE_ORANGE) ? Yellow : Red;
	
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

	if (_mode == POLICE_ORANGE)
	{
		return;
	}
		
	switch(_mode)
	{
		case NORTH_SOUTH_STRAIGHT_AND_RIGHT:
			{
				DrawLight(CAR_LIGHT_N_RIGHT, Green);
				DrawLight(PD_LIGHT_E, Green);
				DrawLight(CAR_LIGHT_S_RIGHT, Green);
				DrawLight(PD_LIGHT_W, Green);
			}
			break;
		case EAST_WEST_STRAIGHT_AND_RIGHT:
			{
				DrawLight(CAR_LIGHT_W_RIGHT, Green);
				DrawLight(PD_LIGHT_S, Green);
				DrawLight(CAR_LIGHT_E_RIGHT, Green);
				DrawLight(PD_LIGHT_N, Green);
			}
			break;
		case EAST_WEST_LEFT:
			{
				DrawLight(CAR_LIGHT_E_LEFT, Green);
				DrawLight(CAR_LIGHT_W_LEFT, Green);
			}
			break;
		case NORTH_SOUTH_LEFT:
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
		case CAR_LIGHT_S_RIGHT: DrawCarLightImp(size.ws_row/2-y/2, size.ws_col/2+4, _color);
			break;
		case CAR_LIGHT_S_LEFT: DrawCarLightImp(size.ws_row/2-y/2, size.ws_col/2-4, _color);
			break;
		case CAR_LIGHT_N_RIGHT: DrawCarLightImp(size.ws_row/2+y/2+1, size.ws_col/2-4, _color);
			break;
		case CAR_LIGHT_N_LEFT: DrawCarLightImp(size.ws_row/2+y/2+1, size.ws_col/2+4, _color);
			break;		
			
		case CAR_LIGHT_E_RIGHT: DrawCarLightImp(size.ws_row/2+2, size.ws_col/2-11, _color);
			break;
		case CAR_LIGHT_E_LEFT: DrawCarLightImp(size.ws_row/2-2, size.ws_col/2-11, _color);
			break;
		case CAR_LIGHT_W_RIGHT: DrawCarLightImp(size.ws_row/2-2, size.ws_col/2+11, _color);
			break;
		case CAR_LIGHT_W_LEFT: DrawCarLightImp(size.ws_row/2+2, size.ws_col/2+11, _color);
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

	SetColor(_color);
		
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
	WriteAt(_y, _x-2, "*");
}


    

