#include <iostream>

#include "stateM.h"

using namespace std;


int main()
{
	StateMatrix stateM(2,3);
	
	stateM.TickHappened();

	cout << stateM.GetCurrentState() << endl;

	stateM.ReportEvent(1);

	cout << stateM.GetCurrentState() << endl;

	return 0;
}


	
