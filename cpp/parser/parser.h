/**************************************************************************************
    Author : Tomer Dery
    Creation date :      19.1.14
    Date last modified : 19.1.14
    Description : Parser
***************************************************************************************/
#ifndef __PARSER_H__
#define __PARSER_H__

#include <string>
#include <set>
#include <vector>

using namespace std;

#include "tokenaizer.h"
#include "analizer.h"

/*--------------------------------------------------------------------------------*/

class Parser{   

private: 	
	vector<string> m_fileLines;

	Tokenaizer* m_tokenaizer;
	Analizer* m_analizer;
	
	size_t m_numOfTokens;
	
	/*will never be use*/
	Parser(const Parser& _pars);	
	Parser& operator=(const Parser& _pars);
	
public: 
	Parser(string _flags = "");  	
		
	virtual ~Parser();
	
	bool GetLinesFromFile(const string& _fileName);
	
	virtual void ParseFile();

};

/*--------------------------------------------------------------------------------*/
	
#endif /*__PARSER_H__*/


