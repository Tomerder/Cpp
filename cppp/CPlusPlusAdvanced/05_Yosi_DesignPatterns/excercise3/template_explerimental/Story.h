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

#ifndef __STORY_H__
#define __STORY_H__

#include <algorithm>
#include <vector>
#include <string>
#include <iostream>


// ===================================================================== //
//							TEXT Base Class
// ===================================================================== //
class Text_t
{
public:
	
	// CTOR, DTOR
	virtual 	~Text_t() {};
	explicit	Text_t() : m_parent(0) {}
	
	virtual void 	Print() {};

	virtual Text_t*	GetParent()	const throw(const char*) { return m_parent; }
	virtual void	SetParent(Text_t* _parent) 			 { m_parent = _parent; }
	
	virtual int		GetLength() { return 0; }
	
	// functions with default actions for leaves
	
	virtual void*	GetChildren() throw(const char*)	{ throw "No Children"; }
	
	virtual void 	Add(Text_t* _child)	   throw(const char*) {};
	virtual void 	Remove(Text_t* _child) throw(const char*) {};
	
protected:
	Text_t*	m_parent;
	
	// functor for Print
	template <class TXT>
	class PrintImp
	{
	public:
		void operator()(TXT* _txt)
			{ _txt->Print(); }
	};
	// ----------------------- //
};



// ===================================================================== //
//								WORD
// ===================================================================== //
class Word_t : public Text_t
{
public:
	virtual	~Word_t() {};
			
			// non-explicit on purpose, can accept char* etc.
			Word_t(std::string _word) : Text_t() { m_word = _word; }	
	
	virtual void 	Print()	{ std::cout << m_word << " "; }
	
			int		GetLength() { return m_word.size(); }
	
	// inherited:
//	Text_t*	m_parent;

private:
	std::string		m_word;
};


// ===================================================================== //
//								SENTENCE
// ===================================================================== //
class Sentence_t : public Text_t
{
public:
	
	typedef std::vector<Word_t*>	stcVec;
	typedef stcVec::iterator 		stcItr;
	
	virtual	~Sentence_t();
	explicit Sentence_t() : Text_t() {};
	
			int		GetLength() { return m_component.size(); }
	
	virtual void*	GetChildren() throw(const char*) { return &m_component; }
	
	virtual void 	Add(Word_t* _child)    throw(const char*);
	virtual void 	Remove(Word_t* _child) throw(const char*);
	
	virtual void 	Print();
	
// inherited:
//	Text_t*	m_parent;

private:
	stcVec				m_component;
	PrintImp<Word_t> 	PrintWord;
};
// ===================================================================== //

// ===================================================================== //
//								CHAPTER
// ===================================================================== //
class Chapter_t : public Text_t
{
public:
	
	typedef std::vector<Sentence_t*>	chVec;
	typedef chVec::iterator 			chItr;
	
	virtual	~Chapter_t();
	
	// non-explicit on purpose, can accept char* etc.
	Chapter_t(std::string _title) : Text_t() { m_title = _title; }
	
			int		GetLength() { return m_component.size(); }
			
	virtual void*	GetChildren() throw(const char*) { return &m_component; }
	
	virtual void 	Add(Sentence_t* _child)    throw(const char*);
	virtual void 	Remove(Sentence_t* _child) throw(const char*);
	
	virtual void 	Print();
	
// inherited:
//	Text_t*	m_parent;

private:
	std::string	 m_title;
	chVec		 m_component;
	
	PrintImp<Sentence_t> 	PrintSen;
};



// ===================================================================== //
//								STORY
// ===================================================================== //
template <class TXT>
class Story_t : public Text_t
{
public:
	
	typedef std::vector<TXT*>			stVec;
	typedef typename stVec::iterator 	stItr;
	
	virtual	~Story_t();
	
	// non-explicit on purpose, can accept char* etc.
	Story_t(std::string _title) : Text_t() { m_title = _title; }
	
	virtual void*	GetChildren() throw(const char*) { return &m_component; }
	
	virtual void 	Add(TXT* _child)    throw(const char*);
	virtual void 	Remove(TXT* _child) throw(const char*);
	
	virtual void 	Print();
	
// inherited:
//	Text_t*	m_parent;

private:
	std::string		m_title;
	stVec	 		m_component;
	
	PrintImp<TXT> 	PrintStory;
};

// ===================================================================== //

#endif  /* __STORY_H__ */
