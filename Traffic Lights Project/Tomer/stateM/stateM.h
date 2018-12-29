#ifndef _STATE_M_
#define _STATE_M_

#include <iostream>
#include <stdio.h>

using namespace std;

/*-------------------------------------------------------------*/

typedef void (*Func)(void);

void NullFunc(); 

struct MatrixEntry{
	unsigned m_nextState;
	Func m_transFunc;

	MatrixEntry() : m_nextState(0) , m_transFunc(NullFunc) {}   
};

struct StateFuncs{
	Func m_onState;
	Func m_onEntry;
	Func m_onExit;

	StateFuncs() : m_onState(NullFunc), m_onEntry(NullFunc), m_onExit(NullFunc) {}   
};

/*-------------------------------------------------------------*/

class StateMatrix
{
public:
	StateMatrix(unsigned _statesNum, unsigned _eventsNum);
	~StateMatrix(); 

	void SetTransaction(unsigned _state, unsigned _event, unsigned _nextState, Func _transFunc = NullFunc);
	void SetStateFuncs(unsigned _state, Func _onState, Func _onEntry = NullFunc, Func _onExit = NullFunc); 

	void ReportEvent(unsigned _event);

	void TickHappened();

	void TickGenerate(unsigned _everyMilisecs);

	unsigned GetCurrentState() const {return m_curState;}

private:
	//uncopyable , unassignable
	StateMatrix(const StateMatrix&);
	StateMatrix& operator=(const StateMatrix&);

	unsigned m_numOfStates;
	unsigned m_curState;
	
	//states array
	StateFuncs* m_statesFuncsArr;

	//trans matrix
	MatrixEntry** m_matrix;		
};

/*-------------------------------------------------------------*/

#endif  //_STATE_M_
