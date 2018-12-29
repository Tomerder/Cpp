// control.h
//
//	What's this?
//	Author: Vladimir Krapp
//	Created on:
//	Last modified:

#ifndef __CONTROL_H__
#define __CONTROL_H__

#include <iostream>

#include "system.h"
#include "hardware.h"
#include "state_machine.h"

using namespace std;

//namespace m10
//{

	struct StateData{
		StateData() : m_secsLimit(15) , m_nextState(ST_NORTH_SOUTH_STRAIGHT_AND_RIGHT) {}
	
		unsigned m_secsLimit;
		LightsState m_nextState;
	};

	
	enum CounterPeds{ NORTH_PED , SOUTH_PED , EAST_PED , WEST_PED , COUNTER_PED_NUM  };
	enum CounterCars{ NORTH_CAR , SOUTH_CAR , EAST_CAR , WEST_CAR , COUNTER_CAR_NUM  };
	

	class Control
	{
		private:
			Hardware m_hardware;
			//StateMatrix m_stateMachine;
			
			Control();  //singletone
			static Control* m_control;   //singletone
			
			unsigned m_counterPeds[COUNTER_PED_NUM ]; 
			unsigned m_counterCars[COUNTER_CAR_NUM ]; 
			
			StateData m_statesData[STATE_NUM];
			
			unsigned m_secsOnCurState;
			
			LightsState m_curState;
			
		public:
			static Control* GetInstance();     //singletone
			
			void BindInterupts();
			
			void InitStateMachine();
			
			void InterruptEmulate(EmulationEvent _event) { 
				cout << "Control::InterruptEmulate" << endl;
				m_hardware.InterruptEmulate(_event); 
			}
			
			//unsigned GetCurState() const  {  return m_stateMachine.GetCurrentState(); }
			LightsState GetCurState() const  {  return m_curState; }
			void SetCurState(LightsState _setState) { m_curState = _setState; }
			
			const unsigned* GetCounterPeds() const  {  return m_counterPeds; }
			const unsigned* GetCounterCars() const  {  return m_counterCars; }
			
			
			void IncCar(CounterCars _car) {  m_counterCars[_car]++;  }
			void IncPed(CounterPeds _ped) {  m_counterPeds[_ped]++;  }
			
			void DecCar(CounterCars _car) 
			{  
				if( m_counterCars[_car] > 0  ){ 
					m_counterCars[_car]--;  
				}
			}
			
			void DecPed(CounterPeds _ped) 
			{  
				if( m_counterPeds[_ped] > 0  ){ 
					m_counterPeds[_ped]--;  
				}
			}
			
			const unsigned GetSecsOnCurState() const  {  return m_secsOnCurState; }
			void IncCurStateSecCount() { m_secsOnCurState++;   }
			void ZeroStateSecCount() { m_secsOnCurState = 0;   }
			
			const StateData GetStateData( LightsState _state) const { return m_statesData[_state];  }
			

	};


//} // !namespace m10

#endif //__CONTROL_H__
