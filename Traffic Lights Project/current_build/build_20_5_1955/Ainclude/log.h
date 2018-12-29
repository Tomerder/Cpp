/*********************************************************** 
	Author :             omer konyo
	Creation date :      29.01.2014
	Last modified date : 18/5/14, Vladi - removed custom mutex dependency, fixed spelling

	Description :	logger file
 
*************************************************************/
#ifndef __LOGER_H__
#define __LOGER_H__

#include <cstring>
#include <fstream>

#include "system.h"
#include "comm.h"
#include "mutex.h"

#define Message(FullMsg) (FullMsg),__LINE__, __FILE__ ,__TIME__ ,__DATE__,__FUNCTION__


class Log
{
public:

/*--------------------------------------------*/
/*              LOGGER FLAGS                  */
/*----------                    --------------*/
	enum Mode {
					DEBUG    = 0x1,
					CRITICAL = 0x2,
					NORMAL   = 0x4,
					SYSTEM   = 0x8,
				 	
					NO_TIME  = 0x10,
					JUST_MSG = 0x20
				};
				
	enum Destination {
					REMOTE   = 0X1,
					LOGFILE  = 0X2,
					TERMINAL = 0X4
		
	};

	explicit Log(CommService* comm=0);
	~Log();
 /*--------------------------------------------*/	
	
//-----------------------------------------------------------
// Enter _msg according to the applied log's flags and       
// _msgMode.  user can use the  "Message" macro to eased the  
// utility.   
	void  ToLog(Log::Mode _msgMode ,const char* _msg ,const int _line, 
	const char* _file ,const char* _time ,const char* _date ,const char* _func);
//-----------------------------------------------------------

private:

	std::string   m_fileName;
	std::ofstream m_file;
	Mode          m_mode;       // log mod
	Destination   m_dest;       // where to send
	SystemEntity  m_sysEntity;  // who call for log
	
	Mutex         m_mtx;

	CommService*  m_comm;
	
	
private:

	void ReadFromConfig();
	void SendLogToOAM(std::string _msgString);
	void sendMessageToDestinations(std::string _message);
};


#endif /* __LOGER_H__ */
