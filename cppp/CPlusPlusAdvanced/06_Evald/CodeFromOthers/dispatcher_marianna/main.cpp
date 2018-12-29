/**************************************************************************************
    Author: Marianna Shvartsman
    Creation date :      2013-12-20
    Last modified date: 2013-12-21
    Description : Direction Monitor
***************************************************************************************/
#include "dirMonitor.h"


class Display
{
public:
	void NotifyMe(wchar_t* _str){ wprintf(L"%s\n",_str);}
};


typedef Dispatcher<wchar_t*,DirMonitor>::ObserverCB<Display> DirMonitorEasyCB;

int main()
{
	Display disp;
	DirMonitor dir(L"C:\\Users\\Marianna\\Desktop\\TestWind\\");
	DirMonitorEasyCB* cb =  new DirMonitorEasyCB(&dir,&disp);
	dir.Monitor();

	return 0;
}