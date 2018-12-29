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
#include <string>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <sstream>

#include "mutex.h"
#include "log.h"
#include "comm.h"
#include "system.h"
#include "config.h"


#define CONFIG_FILE "config.txt"

using namespace std;

/***************** Create *****************/
void Log::ReadFromConfig()
{
	if( !ConfigRead(CONFIG_FILE) )
	{
		fprintf(stderr,"can't open configuration file");
	}
	
	m_mode      = Mode( atoi( ConfigGet("LOG_MODE","1") ));
	m_fileName  = ConfigGet("LOG_FILE_NAME","log.txt");
	m_sysEntity = SystemEntity( atoi( ConfigGet("MY_ID","0") ));
	m_dest      = Destination( atoi( ConfigGet("LOG_DEST","7") ));
}

Log::Log(CommService*  comm) : 
	m_comm(comm) 
{
	ReadFromConfig();
	
	m_file.open(m_fileName.c_str(), ofstream::out | ofstream::app);
}

Log::~Log()
{
	m_file.close();
}

/***************** ToLog *****************/

void Log::SendLogToOAM(string _msgString)
{
	Msg msg;
	
	msg.m_header.m_origin = m_sysEntity;
	msg.m_header.m_type   = LOG;
	msg.m_header.m_length = sizeof(msg.m_header)+_msgString.size();
	
	memcpy(msg.m_content.m_payload ,_msgString.c_str() ,_msgString.size());
		
	m_comm->Send(OAM, msg);
}


/* It may look messy but all it does is print
*/
void  Log::ToLog(Log::Mode _msgMode ,const char* _msg ,const int _line, 
	const char* _file ,const char* _time ,const char* _date ,const char* _func)
{	
	Lock _(m_mtx);
	
	if(!(m_mode & _msgMode))
	{
		return;
	}

    if(m_dest & LOGFILE)
    {	
		if(m_mode & NO_TIME)
		{
			m_file <<_file<<":"<<_line<<":"<<_func<<" >>> "<<_msg<<endl;
			return;
		}
		if(m_mode & JUST_MSG)
		{
			m_file <<" >>> " << _msg << endl;
			return;
		}
		m_file <<_date<<" "<<_time<<" ::"<<_file<<":"<<_line<<":"<<_func<<" >>> "<<_msg<<endl;
	}

	if (m_dest & TERMINAL)
    {
		cout <<_date<<" "<<_time<<" ::"<<_file<<":"<<_line<<":"<<_func<<" >>> "<<_msg<<endl;
	}
	
    if(m_comm && m_sysEntity != OAM && (m_dest & REMOTE) )
    {
    	stringstream ss;
    	ss <<_date<<" "<<_time<<" ::"<<_file<<":"<<_line<<":"<<_func<<" >>> "<<_msg<<endl;
    	SendLogToOAM(ss.str());
    }
}
