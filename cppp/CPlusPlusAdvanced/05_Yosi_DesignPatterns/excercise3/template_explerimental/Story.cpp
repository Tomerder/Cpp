/***************************************************************************
    Author: Stav Ofer
    Creation date:  		2013-11-07    
    Last modified date:		2013-11-08
    Description: 	COMPOSITE design pattern.
    				Base class: Text_t
    				Derived:
    				- Word_t - the leaf class
    				- Sentence_t: composite of words
    				- Chapter_t: composite of sentences
					- Story_t: template, composite of either sentences or chapters
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
		throw "object does not exists";
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



// ===================================================================== //
//								CHAPTER
// ===================================================================== //


Chapter_t::~Chapter_t()
{
	for( int i = m_component.size() - 1; i >= 0; --i )
	{
		delete m_component[i];
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
		throw "object does not exists";
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
//								STORY
// ===================================================================== //


template <class TXT>
Story_t<TXT>::~Story_t()
{
	for( int i = m_component.size() - 1; i >= 0; --i )
	{
		delete m_component[i];
	}
}
// --------------------------------------------------------------------- //

template <class TXT>
void Story_t<TXT>::Add(TXT* _child) throw(const char*)
{
	if( m_component.end() != find(m_component.begin(), m_component.end(), _child) )
	{
		throw "object already exists";
	}
	
	m_component.push_back(_child);
	_child->SetParent(this);
}
// --------------------------------------------------------------------- //

template <class TXT>
void Story_t<TXT>::Remove(TXT* _child) throw(const char*)
{
	stItr itr = find(m_component.begin(), m_component.end(), _child);
	
	if( itr == m_component.end() )
	{
		throw "object does not exists";
	}
	
	delete *itr;
	m_component.erase(itr);
}
// --------------------------------------------------------------------- //

template <class TXT>
void Story_t<TXT>::Print()
{
	cout << endl << StorySide << m_title << StorySide << endl << endl;
	for_each(m_component.begin(), m_component.end(), PrintStory);
	cout << endl;
}
// --------------------------------------------------------------------- //


