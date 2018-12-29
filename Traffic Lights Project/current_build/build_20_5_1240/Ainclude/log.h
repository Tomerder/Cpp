/*********************************************************** 
	Author :             omer konyo
	Creation date :      29.01.2014
	Last modified date : 18/5/14, Vladi - removed custom mutex dependency, fixed spelling

	Description :	logger file
 
*************************************************************/
#ifndef __LOGER_H__
#define __LOGER_H__

#include <cstring>

#define Message(FullMsg) (FullMsg),__LINE__, __FILE__ ,__TIME__ ,__DATE__,__FUNCTION__

/*--------------------------------------------*/
/*              LOGGER FLAGS                  */
/*----------                    --------------*/
typedef enum{
				LOG_DEBUG=1,
				LOG_CRITICAL=2,
				LOG_NORMAL=4,
				LOG_SUPPORT=8,
				
				LOG_NO_TIME=16,
				LOG_JUST_MSG=32
				
			}   LOG_FLAGS;
 /*--------------------------------------------*/


/*-----------------------------------------------------------*/
/* Open log file with _logMode flags.                        */
/* return boolean value on fail/success.                     */
int   LogCreate(const char* _fileName , unsigned int _logMode);
 /*----------------------------------------------------------*/



/*-----------------------------------------------------------*/
/* Close log file.                                           */
void  LogDestroy(void);
/*-----------------------------------------------------------*/



/*-----------------------------------------------------------*/
/* Enter _msg according to the applied log's flags and       */
/* _msgMode.  user can use the  "Message" macro to eased the  */
/* utility.                                                  */
void  ToLog(unsigned int _msgMode ,const char* _msg ,const int _line, 
	const char* _file ,const char* _time ,const char* _date ,const char* _func);
/*-----------------------------------------------------------*/



#endif /* __LOGER_H__ */
