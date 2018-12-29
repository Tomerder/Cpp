/***************************************************************************
    Author: Stav Ofer
    Creation date:  		2013-10-06    
    Last modified date:		2013-10-08
    Description: 	parser - tokenizer
****************************************************************************/

#include <cctype>
#include <string>
#include <queue>
using namespace std;

#include "Tokenizer.h"



/*######################################################################*/

// DTOR
Tokenizer_t::	~Tokenizer_t()
{
	while( !m_tokens.empty() )
	{
		m_tokens.pop();
	}
}
/*######################################################################*/


// tokenize _line & put tokens in _queue
void Tokenizer_t::	Tokenize(const string& _line)
{
	string token;
	size_t pos  = 0;
	size_t pos2 = 0;
	
	while( (string::npos != pos) && (string::npos != ( pos2 = _line.find_first_of(m_delim, pos) )) )
	{
		if( pos2 == pos ) {	// 1-char token
			if( isspace(_line[pos2]) )
			{
				++pos;
				continue;
			}
			token.assign(_line, pos2, 1);
		}
		else
		{	// before delimiter
			token.assign(_line, pos, pos2-pos);
			
			// delimiter
			if( !isspace(_line[pos2]) )
			{
				m_tokens.push(token);
				token.assign(_line, pos2, 1);
			}
		} // end if-else
		
		m_tokens.push(token);
		pos = pos2+1;
	} // end while
	
	if( pos < _line.size() && !isspace(_line[pos]) )
	{
		token.assign(_line, pos, _line.size()-pos);
		m_tokens.push(token);
	}
}
/*######################################################################*/


// return next token (by value), throw -1 when empty
string Tokenizer_t:: GetNextToken()
{
	if(m_tokens.empty()) {
		throw -1;
	}
	
	string temp = m_tokens.front();
	m_tokens.pop();
	return temp;
}
/*######################################################################*/


