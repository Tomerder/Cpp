// state_machine.cpp
//
//	What's this?
//	Author: Tomer Deri 
//	Created on:
//	Last modified:

#include <iostream>
#include <stdio.h>

#include "state_machine.h"

using namespace std;


/*-------------------------------------------------------------*/

void NullFunc() 
{ 
	cout << "NullFunc" << endl; 
}

/*-------------------------------------------------------------*/

StateMatrix::StateMatrix(unsigned _statesNum, unsigned _eventsNum)
{
	m_numOfStates = _statesNum;

	m_statesFuncsArr = new StateFuncs[_statesNum];
	
	//m_matrix = new MatrixEntry[_statesNum][_eventsNum];	
	m_matrix = new MatrixEntry*[_statesNum];
	for(unsigned int i = 0; i < _statesNum; ++i) {
		m_matrix[i] = new MatrixEntry[_eventsNum];
		
		//set nextState as curState
		for(unsigned int j = 0; j < _eventsNum; ++j) {
			m_matrix[i][j].m_nextState = i;
		}	
	}

	

}

StateMatrix::~StateMatrix()
{
	delete[] m_statesFuncsArr; 
	
	//delete[][] m_matrix; 
	for(unsigned int i = 0; i < m_numOfStates; ++i) {
    	delete[] m_matrix[i];
	}
	delete[] m_matrix;
} 

/*-------------------------------------------------------------*/

void StateMatrix::SetTransaction(unsigned _state, unsigned _event, unsigned _nextState, Func _transFunc)
{
	m_matrix[_state][_event].m_nextState = _nextState;
	m_matrix[_state][_event].m_transFunc = _transFunc;	
}

void StateMatrix::SetStateFuncs(unsigned _state, Func _onState, Func _onEntry, Func _onExit)
{
	m_statesFuncsArr[_state].m_onState = _onState;
	m_statesFuncsArr[_state].m_onEntry = _onEntry;
	m_statesFuncsArr[_state].m_onExit = _onExit;
}

/*-------------------------------------------------------------*/

void StateMatrix::ReportEvent(unsigned _event)
{
	unsigned nextState = m_matrix[m_curState][_event].m_nextState;

	//execute trans func
	m_matrix[m_curState][_event].m_transFunc();

	//if state has changed
	if(nextState != m_curState){
		m_statesFuncsArr[m_curState].m_onExit();
		m_statesFuncsArr[nextState].m_onEntry();

		//change state		
		m_curState = nextState;
	}
}

/*-------------------------------------------------------------*/

void StateMatrix::TickHappened()
{
	m_statesFuncsArr[m_curState].m_onState();
}

/*-------------------------------------------------------------*/






