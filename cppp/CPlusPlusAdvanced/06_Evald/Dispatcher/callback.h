/***************************************************************************
    Author: Stav Ofer
    Creation date:  		2013-12-15    
    Last modified date:		2013-12-15
    Description: 	
****************************************************************************/

#ifndef __CALLBACK_H__
#define __CALLBACK_H__

#include <list>

namespace m7
{

//=============================================================//
//		CALLBACK BASE
//=============================================================//

//template <class T, class D>
//class CallBackBase
//{
//public:
//	CallBackBase(D* _d);	// does "register"
//	virtual ~CallBackBase();		// does "deregister"
//
//private:
//	// client classes must write implementation
//	virtual void Notify(T _t) = 0;
//
//	// called by dispatcher DTOR
//	void Disconnect();
//};
//=============================================================//


//=============================================================//
//		DISPATCHER
// T - dispatch type, D - dispatching class
// (e.g. D = class thermometer, dispatches the temperature: T = float)
//=============================================================//
template <class T, class D>
class Dispatcher
{
public:

	// callback object
	class CallBackBase
	{
	public:
		CallBackBase(D* _d);		// does "register"
		virtual ~CallBackBase();	// does "deregister"
	private:
		// client classes must write implementation
		virtual void Notify(T _t) = 0;
		// called by dispatcher DTOR
		void Disconnect();
	};


	virtual ~Dispatcher();

	void Register(CallBackBase* _cbb);

private:
	void Dispatch(T _t) const;
	
	std::list<CallBackBase*> m_callbacks;
};











} //----------------------- END namespace m7 -----------------------//

#endif  /* __CALLBACK_H__ */
