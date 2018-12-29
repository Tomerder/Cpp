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
	
	Text_t(const Text_t& _other) : m_parent(0) {};
	Text_t operator =(const Text_t& _other) {}
	
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
	
	// copy/assignment
	Word_t(const Word_t& _other) 			{ m_word = _other.m_word; }
	Word_t& operator =(const Word_t& _other) { m_word = _other.m_word; }
	
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
	
	// copy/assignment
	Sentence_t(const Sentence_t& _other) { CopyImp(_other); }
	Sentence_t& operator =(const Sentence_t& _other)
		{
			if(this != &_other) { CopyImp(_other); }
			return *this;
		}
	
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
	
	void CopyImp(const Sentence_t& _other);
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
	
	// no copy/assignment
	Chapter_t(const Chapter_t& _other);
	Chapter_t& operator =(const Chapter_t& _other);
};


// ===================================================================== //
//								SHORT STORY
// ===================================================================== //
class SStory_t : public Text_t
{
public:
	
	typedef std::vector<Sentence_t*>	sstVec;
	typedef sstVec::iterator 			sstItr;
	
	virtual	~SStory_t();
	
	// non-explicit on purpose, can accept char* etc.
	SStory_t(std::string _title) : Text_t() { m_title = _title; }
	
	virtual void*	GetChildren() throw(const char*) { return &m_component; }
	
	virtual void 	Add(Sentence_t* _child)    throw(const char*);
	virtual void 	Remove(Sentence_t* _child) throw(const char*);
	
	virtual void 	Print();
	
// inherited:
//	Text_t*	m_parent;

private:
	std::string		m_title;
	sstVec	 		m_component;
	
	PrintImp<Sentence_t> 	PrintStory;
	
	// no copy/assignment
	SStory_t(const SStory_t& _other);
	SStory_t& operator =(const SStory_t& _other);
};


// ===================================================================== //
//								NOVEL
// ===================================================================== //
class Novel_t : public Text_t
{
public:
	
	typedef std::vector<Chapter_t*>	novVec;
	typedef novVec::iterator 		novItr;
	
	virtual	~Novel_t();
	
	// non-explicit on purpose, can accept char* etc.
	Novel_t(std::string _title) : Text_t() { m_title = _title; }
	
	virtual void*	GetChildren() throw(const char*) { return &m_component; }
	
	virtual void 	Add(Chapter_t* _child)    throw(const char*);
	virtual void 	Remove(Chapter_t* _child) throw(const char*);
	
	virtual void 	Print();
	
// inherited:
//	Text_t*	m_parent;

private:
	std::string		m_title;
	novVec	 		m_component;
	
	PrintImp<Chapter_t> 	PrintNovel;
	
	// no copy/assignment
	Novel_t(const Novel_t& _other);
	Novel_t& operator =(const Novel_t& _other);
};

// ===================================================================== //



#endif  /* __STORY_H__ */
