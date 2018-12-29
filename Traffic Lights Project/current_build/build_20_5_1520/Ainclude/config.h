/*****************************************************************************************************************
*    AUTHOR: Tomer Dery                                                                                 
*    DATE: 28.01.14                                                                                              
*    LAST MODIFIED: 28.01.14                                                                                  
*    DESCRIPTION: Configuration file			 
*****************************************************************************************************************/
#ifndef __CONFIG_H__
#define __CONFIG_H__

/*-----------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------*/

void ConfigDestroy();

// return 0 on fail, 1 on success
int ConfigRead(const char* _fileName);

// Return 0 if parameter not found.
const char* ConfigGet(const char* _parameterName, const char* _default);

/*-----------------------------------------------------------------------------*/


#endif  /*__CONFIG_H__*/



