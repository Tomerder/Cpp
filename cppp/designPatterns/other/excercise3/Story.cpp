/***************************************************************************
    Author: Stav Ofer
    Creation date:  		2013-11-07    
    Last modified date:		2013-11-09
    Description: 	COMPOSITE design pattern.
    				Base class: Text_t
    				Derived:
    				- Word_t - the leaf class
    				- Sentence_t: composite of words
    				- Chapter_t: composite of sentences
					- ShortStory_t: composite of sentences
					- Novel_t: composite of chapters
					
					Copy/assignment: allowed for words and sentences only.
					Note: the copy is BY VALUE, and parent pointer is not copied
****************************************************************************/

#include <algorithm>
#include <vector>
#include <string>
#include <iostream>

#include "Story.h"

using namespace std;


// for printing chapter & story titles
ostream& ChapSide(ostream& _os)
{
	return _os << " -- ";
}
// --------------------------------------------------------------------- //
ostream& StorySide(ostream& _os)
{
	return _os << "  ~~~  ";
}
// --------------------------------------------------------------------- //


// ===================================================================== //
//								SENTENCE
// ===================================================================== //

Sentence_t::~Sentence_t()
{
	for( int i = m_component.size() - 1; i >= 0; --i )
	{
		delete m_component[i];
		m_component[i] = 0;
	}
}
// --------------------------------------------------------------------- //


void Sentence_t::Add(Word_t* _child) throw(const char*)
{
	if( m_component.end() != find(m_component.begin(), m_component.end(), _child) )
	{
		throw "object already exists";
	}
	
	m_component.push_back(_child);
	_child->SetParent(this);
}
// --------------------------------------------------------------------- //

void Sentence_t::Remove(Word_t* _child) throw(const char*)
{
	stcItr itr = find(m_component.begin(), m_component.end(), _child);
	
	if( itr == m_component.end() )
	{
		throw "object does not exist";
	}
	
	delete *itr;
	m_component.erase(itr);
}
// --------------------------------------------------------------------- //

void Sentence_t::Print()
{
	for_each(m_component.begin(), m_component.end(), PrintWord);
	std::cout << std::endl;
}
// --------------------------------------------------------------------- //

void Sentence_t::CopyImp(const Sentence_t& _other)
{
	Word_t* word;
	for(int i=0; i<_other.m_component.size(); ++i)
	{
		word = new Word_t(*_other.m_component[i]);
		Add(word);
	}
}
// --------------------------------------------------------------------- //



// ===================================================================== //
//								CHAPTER
// ===================================================================== //


Chapter_t::~Chapter_t()
{
	for( int i = m_component.size() - 1; i >= 0; --i )
	{
		delete m_component[i];
		m_component[i] = 0;
	}
}
// --------------------------------------------------------------------- //

void Chapter_t::Add(Sentence_t* _child) throw(const char*)
{
	if( m_component.end() != find(m_component.begin(), m_component.end(), _child) )
	{
		throw "object already exists";
	}
	
	m_component.push_back(_child);
	_child->SetParent(this);
}
// --------------------------------------------------------------------- //

void Chapter_t::Remove(Sentence_t* _child) throw(const char*)
{
	chItr itr = find(m_component.begin(), m_component.end(), _child);
	
	if( itr == m_component.end() )
	{
		throw "object does not exist";
	}
	
	delete *itr;
	m_component.erase(itr);
}
// --------------------------------------------------------------------- //


void Chapter_t::Print()
{
	cout << endl << ChapSide << m_title << ChapSide << endl << endl;
	for_each(m_component.begin(), m_component.end(), PrintSen);
	cout << endl;
}
// --------------------------------------------------------------------- //



// ===================================================================== //
//								SHORT STORY
// ===================================================================== //

SStory_t::~SStory_t()
{
	for( int i = m_component.size() - 1; i >= 0; --i )
	{
		delete m_component[i];
		m_component[i] = 0;
	}
}
// --------------------------------------------------------------------- //

void SStory_t::Add(Sentence_t* _child) throw(const char*)
{
	if( m_component.end() != find(m_component.begin(), m_component.end(), _child) )
	{
		throw "object already exists";
	}
	
	m_component.push_back(_child);
	_child->SetParent(this);
}
// --------------------------------------------------------------------- //

void SStory_t::Remove(Sentence_t* _child) throw(const char*)
{
	sstItr itr = find(m_component.begin(), m_component.end(), _child);
	
	if( itr == m_component.end() )
	{
		throw "object does not exist";
	}
	
	delete *itr;
	m_component.erase(itr);
}
// --------------------------------------------------------------------- //

void SStory_t::Print()
{
	cout << endl << StorySide << m_title << StorySide << endl << endl;
	for_each(m_component.begin(), m_component.end(), PrintStory);
	cout << endl;
}
// --------------------------------------------------------------------- //



// ===================================================================== //
//								NOVEL
// ===================================================================== //

Novel_t::~Novel_t()
{
	for( int i = m_component.size() - 1; i >= 0; --i )
	{
		delete m_component[i];
		m_component[i] = 0;
	}
}
// --------------------------------------------------------------------- //

void Novel_t::Add(Chapter_t* _child) throw(const char*)
{
	if( m_component.end() != find(m_component.begin(), m_component.end(), _child) )
	{
		throw "object already exists";
	}
	
	m_component.push_back(_child);
	_child->SetParent(this);
}
// --------------------------------------------------------------------- //

void Novel_t::Remove(Chapter_t* _child) throw(const char*)
{
	novItr itr = find(m_component.begin(), m_component.end(), _child);
	
	if( itr == m_component.end() )
	{
		throw "object does not exist";
	}
	
	delete *itr;
	m_component.erase(itr);
}
// --------------------------------------------------------------------- //

void Novel_t::Print()
{
	cout << endl << StorySide << m_title << StorySide << endl << endl;
	for_each(m_component.begin(), m_component.end(), PrintNovel);
	cout << endl;
}
// --------------------------------------------------------------------- //


