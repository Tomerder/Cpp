/*********************************************************** 
	Author :             omer konyo
	Creation date :      29.01.2014
	Last modified date : 29.01.2014

	Description :	handel logger file
 
 	Use static logger for the Application
 	
*************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "mutex.h"
#include "log.h"

static struct Logger
{
	FILE*         m_file;
	unsigned int  m_mode;
	
	Mutex         m_mtx;
} logger;

/***************** Create *****************/

int LogCreate(const char* _fileName , unsigned int _logMode)
{
	logger.m_file = fopen( _fileName ,"w");
	if(!logger.m_file)
	{
		return -1;
	}
	logger.m_mode = _logMode;
	
	atexit( LogDestroy );
	return 0;
}

/***************** Destroy *****************/

void  LogDestroy(void)
{
	fclose(logger.m_file);
}

/***************** ToLog *****************/
/* It may look messy but all it does is print
*/
void  ToLog(unsigned int _msgMode ,const char* _msg ,const int _line, 
	const char* _file ,const char* _time ,const char* _date ,const char* _func)
{	
	Lock _(logger.m_mtx);
	
	if(!(logger.m_mode & _msgMode))
	{
		return;
	}
	if(logger.m_mode & LOG_NO_TIME)
	{
		fprintf(logger.m_file ,"%s:%d:%s >>> %s\n",
		                 _file,_line, _func ,_msg);
		return;
	}
	if(logger.m_mode & LOG_JUST_MSG)
	{
		fprintf(logger.m_file ," >>> %s\n",_msg);
		return;
	}
	fprintf(logger.m_file ,"%s %s :: %s:%d:%s >>> %s\n",
	               _date, _time, _file,_line, _func ,_msg);
}
