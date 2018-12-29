/***************************************************************************
    Author: Stav Ofer
    Creation date:  		2013-12-15    
    Last modified date:		2013-12-15
    Description: 	
****************************************************************************/

#ifndef __DISPATCHER_H__
#define __DISPATCHER_H__

#include <list>
#include <algorithm>

namespace m7
{


//=============================================================//
//		DISPATCHER
// T - dispatch type, D - dispatching class
// (e.g. D = class thermometer, dispatches the temperature: T = float)
//=============================================================//
template <class T, class D>
class Dispatcher
{
public:
	virtual ~Dispatcher();

	// callback object
	class CallBackBase
	{
	public:
		CallBackBase(D* _d);		// CTOR - also "register"
		virtual ~CallBackBase();	// DTOR - also "deregister"
	private:
		virtual void Notify(T _t) = 0;	// client classes must write implementation
		void Disconnect();	// called by dispatcher DTOR
		//D* m_dispatcher;
	};

private:

	friend class CallBackBase;

	void Dispatch(T _t) const; // call Notify of all observers
	void Register(CallBackBase* _cbb);

	std::list<CallBackBase*> m_observers;
};
//=============================================================//



// base class for callbacks
template <class T, class D, class O>
class ObserverCB : public Dispatcher<T,D>::CallBackBase<T,D>
{
public:
	ObserverCB(D* _d, O* _o);		// CTOR - does "register"
private:
	//client classes must write implementation
	//virtual void Notify(T _t) = 0;

	O* m_observer;
};
 //=============================================================//



} //----------------------- END namespace m7 -----------------------//

#endif  /* __DISPATCHER_H__ */
