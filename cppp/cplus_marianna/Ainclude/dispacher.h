/**************************************************************************************
    Author: Marianna Shvartsman, Ariel Lipovetzky, Stav Ofer
    Creation date :      2013-12-15
    Last modified date: 2013-12-15
    Description : Dispacher
***************************************************************************************/
#ifndef __DISPACHER_H__
#define __DISPACHER_H__
#include <list>

//DESCRIPTION: class Dispacher provides service of registration, unregistration and notification
// in case of change, according to client CallBack.	

//USAGE EXAMPLE: create a thremometer that notifies for any temperature change
//		typedef Disp<temperature, thermometr>
//		CB TermCB;
//
//		class DogTCB: public TermCB
//		{
//		public:
//			DTCB(Dog* _d);
//			Notify(Temperature t);
//			{
//				m_d -> Foo(t);
//			}
//		}
//.......... more easy for client
//		new TermMCB<Dog> cb(Dog::Foo);
//
// CallBack nested class in Desp
// Despacher inherit from DSpacher


template<class T,class D> //T - temperatura, D-thermometr
class Dispatcher
{ 
	class CallBackBase; //previous declaration

public:
	void Dispatch(const T& _t)const; //NotifyAll

	class CallBackBase
	{   
	public:
		CallBackBase(D* term) //D = thermometr //do register term->Register(this);
		virtual ~CallBackBase(); //do unregister
	private:
		D* m_dispach;
		virtual void Notify(const T& _t)=0;
		bool m_disconect; //if disconnect=false need UnRegister, else not need
		template<class T,class D> friend class Dispatcher;
	};

	template <class O>
	class ObserverCB: public typename Dispatcher<T,D>::CallBackBase
	{
	public:
		ObserverCB(D* _disp, O* _observ);
		virtual void Notify(const T& _t); //{m_d->NotifyMe(T)}
	private:
		O* m_observer;
	};


private:
	void Register(CallBackBase* _callback);
	void Unregister(CallBackBase* _callback);

	std::list<CallBackBase*> m_observers;
	template<class T,class D> friend class CallBackBase;
};


#endif



