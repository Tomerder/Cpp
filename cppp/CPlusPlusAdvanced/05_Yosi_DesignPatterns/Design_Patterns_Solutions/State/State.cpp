#include <iostream>               
using namespace std;               
 
class State;
                                  
class Machine {                    
public:
	Machine();
	void setCurrent( State* s ) { current = s; }
	void on();
	void off();
private:
	class State* current;
};

class State {
public:
	virtual void on ( Machine* m ) { cout << " already ON  " << endl; }
	virtual void off( Machine* m ) { cout << " already OFF " << endl; }
};


class ON : public State {
public:
			ON()  { cout << "   ON-ctor ";  };
			~ON() { cout << "   dtor-ON " << endl; };
	void	off( Machine* m );
};

class OFF : public State {
public:
			OFF()  { cout << "   OFF-ctor ";  };
			~OFF() { cout << "   dtor-OFF " << endl; };
	void	on( Machine* m );
};

Machine::Machine()	{ current = new OFF();  cout << endl; }
void Machine::on()  { current->on ( this );}
void Machine::off() { current->off( this );} 


void ON::off( Machine* m ) {
	cout << "   going from ON to OFF";
	m->setCurrent( new OFF() );
	delete this;
}

void OFF::on( Machine* m ) {
	cout << "   going from OFF to ON";
	m->setCurrent( new ON() );
	delete this;
}	

void main( void ) {
   void (Machine::*ptrs[])() = {& Machine::off, & Machine::on };
   Machine fsm;
   int num;
   while (1) {
      cout << "Enter 0/1: ";
      cin >> num;
      (fsm.*ptrs[num])();
	} 
}


