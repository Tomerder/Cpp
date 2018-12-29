/**************************************************************************************
    Author : Tomer Dery
    Creation date :      19.1.14
    Date last modified : 19.1.14
    Description : Parser
***************************************************************************************/
#ifndef __ERROR_H__
#define __ERROR_H__

#include <string>

/*--------------------------------------------------------------------------------*/	

typedef enum{ MAIN_E , MUL_TYPE_E , NOT_DEF_E , ELSE_E , OPR_PPP_E , OPR_MMM_E , BRC_E , BRC_NC_E }ERROR;

const string errors[] =	{ "illegal - declaration before 'main'" 	, 
						  "multiple type declaration" 				,
						   " is not defined"  						,         /**/
   						   "'else' without 'if'"	  				, 
						   "no operator +++"	      				,
						   "no operator ---"	      				,  
						   " closing brace without opening"			,         /**/
                           " brace not closed"  	       };   			  /**/

/*--------------------------------------------------------------------------------*/	

class Error{   

private: 	
	const ERROR m_error;
	const size_t m_lineNum;
	string m_str;
	
	/*will never be use*/
	Error& operator=(const Error& _err);
	
public: 	
	Error(ERROR _error, size_t _lineNum, string _str="") : m_error(_error) ,  m_lineNum(_lineNum) , m_str(_str)  {} 	
		
	Error(const Error& _err) : m_error(_err.m_error) ,  m_lineNum(_err.m_lineNum) {};  		
		
	virtual ~Error() {} 	

	virtual void Print() const { cout << "Line : " << m_lineNum << m_str << errors[m_error] << endl;  } 	
	
};

/*--------------------------------------------------------------------------------*/	
	
#endif /*__ERROR_H__*/


