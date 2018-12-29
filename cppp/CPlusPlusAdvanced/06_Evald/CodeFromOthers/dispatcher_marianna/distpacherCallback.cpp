/**************************************************************************************
    Author: Marianna Shvartsman
    Creation date :      2013-12-21
    Last modified date: 2013-12-21
    Description : Dispatche test
***************************************************************************************/
#include <iostream>
using namespace std;

#include "dispatcherCallback.h"
typedef int Temperature;

class Thermometr: public Dispatcher<Temperature,Thermometr>
{
public:
	Thermometr(Temperature _deg = 0):m_deg(_deg){}
	void ChangeTemp(Temperature _deg){ m_deg = _deg ;Dispatch(_deg);}
private:
	Temperature m_deg;
};

class Dog
{
public:	
	void NotifyMe(Temperature _dig){cout << "Wow!" << endl;}

};

typedef Dispatcher<Temperature, Thermometr>::ObserverCB<Dog> TermEasyCB;

int main()
{
	Thermometr term(25);
	Dog bobbik;
	TermEasyCB* cb =  new TermEasyCB(&term,&bobbik);
	term.ChangeTemp(26);
	system("pause");

	return 0;
}