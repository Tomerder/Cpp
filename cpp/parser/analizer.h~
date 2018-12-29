/**************************************************************************************
    Author : Tomer Dery
    Creation date :      19.1.14
    Date last modified : 19.1.14
    Description : Parser
***************************************************************************************/
#ifndef __ANALIZER_H__
#define __ANALIZER_H__

#include <string>
#include <set>
#include <deque>
#include <vector>

using namespace std;

#include "error.h"

/*--------------------------------------------------------------------------------*/

#define NUM_OF_TOKENS_TO_SAV 2
#define NUM_OF_BRACES_TYPES 4

/*--------------------------------------------------------------------------------*/

class Analizer{   

private: 	
	set<string> m_symbolTable;
	set<string> m_types;
	set<string> m_vars;
	
	/*if->mark , else->clear*/ 
	bool m_wasIfFlag; 
	
	bool m_isFirstToken; 

	int m_countBraces[NUM_OF_BRACES_TYPES];
	
	string m_lastTokens[NUM_OF_TOKENS_TO_SAV];
	deque<string> m_tokensToAnalize;
	
	size_t m_lineNum;
	
	deque<Error> m_errors;
	
	/*will never be use*/
	Analizer(const Analizer& _anlz);	
	Analizer& operator=(const Analizer& _anlz);
	
public: 
	Analizer() : m_isFirstToken(true) {} 	
		
	virtual ~Analizer() {}	
	
	void AddSymbol(const string& _symbol)  { m_symbolTable.insert(_symbol); } 
	void AddType(const string& _type) { m_types.insert(_type); } 
		
	void AddSymbols(const vector<string>& _symbols);
	void AddTypes(const vector<string>& _types);	
	
	/*
	void SetSymbols(const vector<string>& _symbols) {m_symbolTable = _symbols;} 
	void SetTypes(const vector<string>& _types) {m_types = _types;} 
	*/
	
	void SetTokens(const deque<string>& _tokensToAnalize , size_t _lineNum) { m_tokensToAnalize = _tokensToAnalize; m_lineNum = _lineNum ; } 
	
	const deque<Error>& GetErrors() const;
	
	
	virtual void Analize();
	
	/*end of file -> check all braces has been closed*/ 
	virtual void AnalizeEnd();

	virtual void PrintErrors() const; 
	
};

/*--------------------------------------------------------------------------------*/
	
#endif /*__ANALIZER_H__*/


