#include <string.h>
#include <iostream>

#include "parser.h"

using namespace std;

/*--------------------------------------------------------------------------------*/
/*
void Tokenaizer::AddDelimiters(string _delimiters)
{
	for(unsigned int i=0; i<_delimiters.length() ; i++){
		AddDelimiter (_delimiters[i]);
	}
} 	
*/
/*--------------------------------------------------------------------------------*/	
/*set   deque<string> m_tokensCreated   from    string m_lineToTokenize*/
size_t Tokenaizer::CreateTokens()
{
	size_t numOfTokens=0;
	
	size_t endPos=0;
	string token,delim;
	
	m_tokensCreated.clear();
	

	do{
		endPos = m_lineToTokenize.find_first_of(m_delimiters) ;

		++numOfTokens;
		token = m_lineToTokenize.substr(0, endPos);
		
		if( !token.empty() && token != " " && token != ""){
			cout << token << endl;
			m_tokensCreated.push_back(token);
		}
	
		delim = m_lineToTokenize.substr(endPos , 1);
		if( !delim.empty() && delim != " " && delim != "" && !isspace(m_lineToTokenize[endPos])){
			cout << delim << endl;	
			m_tokensCreated.push_back(delim);	
		}

		m_lineToTokenize.erase(0,endPos+1);

	} while ( m_lineToTokenize != "" );



	 return numOfTokens;
}

/*--------------------------------------------------------------------------------*/	







/*
	size_t pos = 0;
    do { 
        size_t beg_word = m_lineToTokenize.find_first_not_of(m_delimiters, pos);
        if (beg_word == string::npos) 
            break;
        size_t end_word = m_lineToTokenize.find_first_of(m_delimiters, beg_word);
        size_t beg_next_word = m_lineToTokenize.find_first_not_of(m_delimiters, end_word);
        cout << string(m_lineToTokenize, pos, beg_next_word-pos-1) << endl; 
		cout << m_lineToTokenize[end_word] << endl; 
        pos = end_word+1;
    } while (pos != string::npos);
*/
/*
	size_t pos=0,lastPos=0,delimPos=0;
	while (string::npos != pos || string::npos != lastPos)
    {
        // Found a token, add it to the vector.
        cout << m_lineToTokenize.substr(lastPos, pos - lastPos) << endl ;

		
		delimPos = m_lineToTokenize.find_first_of(m_delimiters, pos);
		cout << m_lineToTokenize[delimPos];

        // Skip delimiters.  Note the "not_of"
        //lastPos = m_lineToTokenize.find_first_not_of(m_delimiters, pos);
		lastPos = m_lineToTokenize.find_first_of(m_delimiters, pos) + 1;		
	
        // Find next "non-delimiter"
        pos = m_lineToTokenize.find_first_of(m_delimiters, lastPos);

    }
*/





	
	

