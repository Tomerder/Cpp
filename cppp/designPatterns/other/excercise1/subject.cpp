/***************************************************************************
    Author: Stav Ofer
    Creation date:  		2013-11-03    
    Last modified date:		2013-11-05
    Description: 	subject to observers - ABC
****************************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#include "observer.h"
#include "subject.h"

// ATTACH
void Subject_t::Attach(Observer_t* _ob)
{ 
	m_observers.push_back(_ob);
} 
//-----------------------------------------------

// DETACH
void Subject_t ::Detach(Observer_t* _ob)
{ 
	vector<Observer_t*>::iterator remove = find(m_observers.begin(), m_observers.end(), _ob);
	
	if( remove != m_observers.end() )
	{
		m_observers.erase(remove);
	}
} 
//-----------------------------------------------

// NOTIFY - protected - not called from outside
void Subject_t :: Notify(void* _params, char* _txt)
{ 	
	for (size_t i = 0; i < m_observers.size(); i++)
	{
		m_observers[i]->Update(this, _txt); // call Update func. in observers
	}
	
//	for_each( m_observers.begin(), m_observers.end(), _func);
}
//-----------------------------------------------

