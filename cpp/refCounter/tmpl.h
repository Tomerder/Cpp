/**************************************************************************************
    Author : Tomer Dery
    Creation date :      21.1.13
    Date last modified : 21.1.13
    Description : reference counter
***************************************************************************************/
#ifndef __TMPL_H__
#define __TMPL_H__

#include "tmplRC.h"

using namespace std;

/*-----------------------------------------------------------------------------------------------*/

template<class T>

class Tmpl{ 

private: 	
	TmplRC<T>* m_dataPtr;
			
public: 	
	Tmpl();
	Tmpl(const T& _data);
	
	Tmpl(const Tmpl& _tmpl);
	Tmpl& operator=(const Tmpl& _tmpl);
		
	virtual ~Tmpl() ;
	
	const T& GetData() const { return ( m_dataPtr->GetData() ) ; }
	
	void SetData(const T& _data);
	
	size_t GetRefCount() const { return m_dataPtr->GetRefCount(); }

};

/*-----------------------------------------------------------------------------------------------*/
template<class T>
Tmpl<T>::~Tmpl() 
{
	if(m_dataPtr != 0){
		m_dataPtr->DecCount();	
		m_dataPtr = 0;
	}
}
/*-----------------------------------------------------------------------------------------------*/

template<class T>
Tmpl<T>::Tmpl() 
{
	m_dataPtr = new TmplRC<T>;	
}


template<class T>
Tmpl<T>::Tmpl(const T& _data)
{
	m_dataPtr = new TmplRC<T>(_data);	
}

/*-----------------------------------------------------------------------------------------------*/
template<class T>
Tmpl<T>::Tmpl(const Tmpl& _tmpl)
{
	/*point to same adr*/
	m_dataPtr = _tmpl.m_dataPtr;	
	
	/*inc ref count*/ 
	m_dataPtr->IncCount();
}


template<class T>
Tmpl<T>& Tmpl<T>::operator=(const Tmpl& _tmpl)
{
	if(this != &_tmpl){	
		m_dataPtr->DecCount();	 /*dec count of cur ref*/

		m_dataPtr = _tmpl.m_dataPtr;   
		m_dataPtr->IncCount();	/*inc  count of new ref*/ 
	}

	return *this;
}

/*-----------------------------------------------------------------------------------------------*/

template<class T>
void Tmpl<T>::SetData(const T& _data)
{
	m_dataPtr->DecCount();	
    m_dataPtr = new TmplRC<T>(_data);	
}

/*-----------------------------------------------------------------------------------------------*/

#endif /*__TMPL_H__*/


