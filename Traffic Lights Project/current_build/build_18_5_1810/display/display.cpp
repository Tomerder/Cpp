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
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
    init_pair(4, COLOR_WHITE, COLOR_BLACK);
}

void 
Display::ShutDown()
{
    endwin();
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


    

