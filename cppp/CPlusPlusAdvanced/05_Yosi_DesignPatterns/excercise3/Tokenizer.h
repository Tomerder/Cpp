/***************************************************************************
    Author: Stav Ofer
    Creation date:  		2013-10-06    
    Last modified date:		2013-10-08
    Description: 	parser - tokenizer
****************************************************************************/


#ifndef __TOKENIZER_H__
#define __TOKENIZER_H__

#include <string>
#include <queue>


class Tokenizer_t
{
public:
	
	// CTOR, DTOR
	Tokenizer_t	(const char* _delimiters) : m_delim(_delimiters) {};
	virtual ~Tokenizer_t();
	
	virtual void		Tokenize(const std::string& _line);	// tokenize _line, store internally
	virtual std::string	GetNextToken();						// return next token (by value), throw -1 when empty
	
	bool	Empty() const	{ return m_tokens.empty(); }
	
protected:
	const std::string 	m_delim;	
	std::queue<std::string>	m_tokens;
	
	Tokenizer_t	(const Tokenizer_t& _t);
	Tokenizer_t& operator =	(const Tokenizer_t& _t);
	
private:
};



#endif  /* __TOKENIZER_H__ */


