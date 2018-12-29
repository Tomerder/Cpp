// display.h
//
//	Display module for rt project
//	Author: Vladimir Krapp
//	Created on: 13/5/14
//	Last modified:

#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <ncurses.h>    


class Display
{
public:

    enum Color
    {
        Red     = 1,
        Yellow  = 2,
        Green   = 3,
        White   = 4
    };


    static void SetUp();
    static void ShutDown();
    static void SetColor(Color _color);
    static void WriteAt(int _x, int _y, const char* _str);

    static void Demo();
    
    static void DrawRoads();

private:
    
}; // class Display



#endif //__DISPLAY_H__
