/************************************************************************
Observer design pattern
Author: Dan Bar-On.
Creation Date: 15.05.14 
Modified at:
Description: 
************************************************************************/
#ifndef OBSERVER_H
#define OBSERVER_H

#include <vector>
#include <algorithm> 
#include <cassert> 

#include "uncopyable.h" 

// Template requirements:
// T - has to be copyable
// CONC_SUBJ - has to have Register and Unregister, that CallBackBase can approach.

template <class T, class CONC_SUBJ>
class CallBackBase;

//========================================================================

template <class T, class CONC_SUBJ>
class Subject;
// use of this class: as a data member of your broadcasting entity, or inherit from it.
// When you create a CallBack it registers itself to the Subject.
// You can Notify your observers using Notify(T).
template < class T, class CONC_SUBJ>
class Subject : private Uncopyable
{
typedef CallBackBase<T, CONC_SUBJ> Cb;	
public:
	~Subject();	// Not virtual. If you want to inherit from this class - use only private inheritance! (TODO)
	
	void Notify(T _msg);	//broadcasts

	void Register(Cb* );	// Do not use this functions! Only CallBackBase does this.
	void Unregister(Cb* );	// Do not use this functions! Only CallBackBase does this.

private:
	std::vector<Cb* > m_callBacks;
};

//========================================================================

template <class T, class CONC_SUBJ>
class CallBackBase : private Uncopyable
{
public:
	CallBackBase(CONC_SUBJ*);	//register check pointer not null
	virtual ~CallBackBase();	//unregister check if pointer is not null unregister
	
private:
	CONC_SUBJ* m_concSubj;

	friend class Subject<T, CONC_SUBJ>;
	virtual void Notify(T) = 0;
	void Detach();	//unregister check pointer not null
};

//========================================================================

// When creating an observer create a CallBack object.
// WhenEver your subject broadcasts, your function FUNC (member-function) will be executed.
template <class T, class CONC_SUBJ, class CONC_OBSERVER, class RET, RET (CONC_OBSERVER::*FUNC)(T) >
class CallBack : public CallBackBase<T, CONC_SUBJ>
{
public:
	explicit CallBack(CONC_OBSERVER*, CONC_SUBJ*);

private:
	virtual void Notify(T);	//	CONC_OBSERVER::ACTION()
	CONC_OBSERVER* m_observer;
};

//========================================================================
//Subject implementation
template < class T, class CONC_SUBJ>
Subject<T,CONC_SUBJ>::~Subject()
{
	for (typename std::vector<Cb*>::iterator it = m_callBacks.begin(); it != m_callBacks.end(); ++it)
	{
		if (*it)
		{
			(*it)->Detach();
		}
	}
}

template < class T, class CONC_SUBJ>
void Subject<T,CONC_SUBJ>::Notify(T _msg)
{
	for (typename std::vector<Cb*>::iterator it = m_callBacks.begin(); it != m_callBacks.end(); )
	{
		if (*it)
		{
			(*it)->Notify(_msg);
			++it;
		}
		else
		{
			it = m_callBacks.erase(it);
		}
	}
}

template < class T, class CONC_SUBJ>
void Subject<T,CONC_SUBJ>::Register(Cb* _c)
{
	m_callBacks.push_back(_c);	// is that safe?
}

template < class T, class CONC_SUBJ>
void Subject<T,CONC_SUBJ>::Unregister(Cb* _c)
{
	typename std::vector<Cb*>::iterator it = find(m_callBacks.begin(), m_callBacks.end(), _c);
	assert(it != m_callBacks.end() );
	*it = 0;	
}
//========================================================================
//CallBackBase implementation
template <class T, class CONC_SUBJ>
CallBackBase<T, CONC_SUBJ>::CallBackBase(CONC_SUBJ* _concSubj)
{
	m_concSubj = _concSubj;
	m_concSubj->Register(this);
}

template <class T, class CONC_SUBJ>
CallBackBase<T, CONC_SUBJ>::~CallBackBase()
{
	if (m_concSubj)
	{
		m_concSubj->Unregister(this);
	}
}

template <class T, class CONC_SUBJ>
void CallBackBase<T, CONC_SUBJ>::Detach()
{
	m_concSubj = 0;
}

// ========================================================================
// CallBack implementation
template <class T, class CONC_SUBJ, class CONC_OBSERVER, class RET, RET (CONC_OBSERVER::*FUNC)(T) >
CallBack<T, CONC_SUBJ, CONC_OBSERVER, RET, FUNC>::CallBack(CONC_OBSERVER* _concObserver, CONC_SUBJ* _concSubj)
:CallBackBase<T,CONC_SUBJ>(_concSubj),
m_observer(_concObserver)
{}

template <class T, class CONC_SUBJ, class CONC_OBSERVER, class RET, RET (CONC_OBSERVER::*FUNC)(T) >
void CallBack<T, CONC_SUBJ, CONC_OBSERVER, RET, FUNC>::Notify(T _msg)
{
	(m_observer->*FUNC)(_msg);
}


#endif // OBSERVER_H



