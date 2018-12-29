/**************************************************************************************
    Author: Marianna Shvartsman
    Creation date :      2013-12-15
    Last modified date: 2013-12-21
    Description : Dispatcher
***************************************************************************************/
#ifndef __DISPACHER_H__
#define __DISPACHER_H__
#include <list>

//DESCRIPTION: class Dispacher provides service of registration, unregistration and notification
// in case of change, according to client CallBack.	
// CallBack created anly when some object want to observ the despatcher

//USAGE EXAMPLE: The dog want to get update about temperature change.
//
//		CREATE a Thremometer that notifies for any temperature change
//		INHERITE(private) Dispatcher that will manage observers incase of temeperature change
/*		class Term: private Disp<temperature, Term>
		{
		public:
			TempChange(temperature _degrees){ m_deg = _degrees; Dispatch(_degrees);}
		private:
			temperatura m_deg;
		} 
*/

//		FOR EASIER USAGE DEFINE:
//		typedef Dispatcher<temperature, thermometr>::CallBackBase TermCB;
//
//		INHERITE CallbackBase and IMPLEMENT your callBack class like this: 
/*		class DogTCB: public TermCB
		{
		public:
			DTCB(Dog* _d);
			Notify(Temperature t);
			{
				m_d -> Foo(t);
			}
		}
*/
//.......... MORE EASY usage
//		DEFINE your call back function NotifyMe(T) and ENJOY( my ObserverCB class will do all job)
//		typedef Dispatcher<temperature, termometer>::ObserverCB<Dog> TermEasyCB
//		TermEasyCB* cb = new TermEasyCB(Dog* _d); -------------> new TermEasyCB<Dog>	cb(Dog _d)
//

//****************************************************************************************
// Dispatcher and CallBack class definitions (CallBack nested class in Despatcher)
//****************************************************************************************
template<class T,class D> //T - Temperature, D-Thermometr
class Dispatcher
{ 
	class CallBackBase; //forword declaration
public:
	//ctor - generated
	~Dispatcher();
	void Dispatch(const T& _t); //NotifyAll

	class CallBackBase
	{   
	public:
		CallBackBase(D* term); //D = thermometr //do register term->Register(this);
		virtual ~CallBackBase(); //do unregister
	private:
		D* m_dispatch;
		virtual void Notify(const T& _t)=0;
		bool m_isConnected; //if m_isConnected=true need UnRegister, else not need
		template<class T,class D> friend class Dispatcher;
	}; //end ABC CallBackBase class

	template <class O> 
	class ObserverCB: public Dispatcher<T,D>::CallBackBase
	{
	public:
		ObserverCB(D* _disp, O* _observ);
		virtual void Notify(const T& _t); //{m_observer->NotifyMe(_t)}
	private:
		O* m_observer;
	}; //end ObserverCB


private:
	void Register(CallBackBase* _callback);
	void Unregister(CallBackBase* _callback);

	std::list<CallBackBase*> m_observers;
	template<class T,class D> friend class CallBackBase;
}; //end Dispatcher class

//***********************************************************************************
//	Implementation
//***********************************************************************************
//--------------------------------------------------------------
// Dispatcher DTOR
//--------------------------------------------------------------
template <class T, class D>
Dispatcher<T,D>::~Dispatcher()
{
	std::list<CallBackBase*>::iterator itr = m_observers.begin();
	for(;itr != m_observers.end(); ++itr)
	{
		(*itr)->m_isConnected = false;
	}
}
//---------------------------------------------------------------
// Dispatcher Register
//---------------------------------------------------------------
template <class T, class D>
void Dispatcher<T,D>::Register(CallBackBase* _callback)
{
	m_observers.push_back(_callback);
}

//--------------------------------------------------------------
// Dispatcher Unregister
//--------------------------------------------------------------
template <class T, class D>
void Dispatcher<T,D>::Unregister(CallBackBase* _callback)
{
	std::list<CallBackBase*>::iterator itr = m_observers.begin();
	for(;itr != m_observers.end(); ++itr)
	{
		if(*itr == _callback )
		{
			m_observers.erase(itr);
			return;
		}
	}

}

//--------------------------------------------------------------
// Dispatcher NotifyAll
//--------------------------------------------------------------
template <class T, class D>
void Dispatcher<T,D>::Dispatch(const T& _t)
{
	std::list<CallBackBase*>::iterator itr = m_observers.begin();
	//std::list<CallBackBase*>::iterator itr = m_observers.begin();
	for(;itr != m_observers.end(); ++itr)
	{
		(*itr)->Notify(_t);		
	}
}

//--------------------------------------------------------------
// CallBackBase CTOR
//--------------------------------------------------------------

template<class T,class D> 
Dispatcher<T,D>::CallBackBase::CallBackBase(D* term): m_dispatch(term), m_isConnected(true) 
{
	m_dispatch->Register(this);
}

//--------------------------------------------------------------
// CallBackBase DTOR
//--------------------------------------------------------------
template<class T,class D> 
Dispatcher<T,D>::CallBackBase::~CallBackBase() //do unregister
{
	if(m_isConnected)
	{
		m_dispatch->Unregister(this);
	}
}

//--------------------------------------------------------------
// ObserverCallBack CTOR
//--------------------------------------------------------------
template<class T,class D>
template <class O>
Dispatcher<T,D>::ObserverCB<O>::ObserverCB(D* _disp, O* _observ): CallBackBase(_disp), m_observer(_observ){}

//--------------------------------------------------------------
// ObserverCallBack NotifyFunc implementation
//--------------------------------------------------------------
template<class T,class D>
template <class O>
void Dispatcher<T,D>::ObserverCB<O>::Notify(const T& _t)
{
	m_observer->NotifyMe(_t);
}

#endif //__DISPACHER_H__



