/**************************************************************************************
    Author: Marianna Shvartsman
    Creation date :      2013-12-18
    Last modified date: 2013-12-20
    Description : Direction Monitor
***************************************************************************************/
#ifndef __DIRMONITOR_H__
#define __DIRMONITOR_H__
#include <windows.h>

#include "dispatcherCallback.h"

/*DISCRIPTON: DirMonitor watchs for all changes in directory and subderictories in giving path
 USAGE EXAMPLE: DirMonitor dir(L"C:\\Users\\Marianna\\Desktop\\TestWind\\"); 
							dir.Monitor();
*/

	
class DirMonitor: public Dispatcher<wchar_t*,DirMonitor>
{
public:
	DirMonitor(LPCWSTR _path);
	void Monitor();
private:
	LPCWSTR m_path;	
};

#endif