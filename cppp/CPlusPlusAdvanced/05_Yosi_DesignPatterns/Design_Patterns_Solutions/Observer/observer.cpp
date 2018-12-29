#include <iostream>
#include <vector>

using namespace std;

// each section should be in a separate h/cpp-file

//================================================================================

class Subject;

// OBSERVER - abstract base class
class Observer
{
public:
	virtual			~Observer() {}
    virtual void	Update(Subject* ChngSubject) = 0; // UPDATE function - (pure) virtual
protected:
	Observer() {}
	Subject* sbj;	// ptr to subject
};

//================================================================================

class Observer;

// SUBJECT
class Subject
{
public:
	virtual ~Subject() {}

    virtual void Attach(Observer*);	// func for observers to call
    virtual void Detach(Observer*);

protected:
	Subject() {}
	virtual void Notify();	// NOTIFY
private:
    vector<Observer*> m_observers; // list of observers (who called Attach)
};

//================================================================================

class Bank : public Subject
{ 
public: 
		Bank () {}; 
    	void	ChangePercent();// change in the bank 
}; 

//================================================================================

// observers:
// only commonality is being observers, otherwise not related to each other

class Account: public Observer
{ 
public: 
		Account (Subject*);		// attach to bank - not necessarily in CTOR, can have differenct function for attach
		~Account();		 		// detach from bank

    void	Update(Subject*);	// update itself 
}; 


class Newspaper: public Observer
{ 
public: 
		Newspaper(Subject*);		// attach to bank	
		~Newspaper();			// detach from bank

    void	Update(Subject*);	// update itself 
}; 

//================================================================================
// Subject Implemenation
//================================================================================

void Subject::Attach (Observer* ob) { 
	m_observers.push_back(ob); 
} 

void Subject ::Detach (Observer* ob) { 
	int i=0; 
	for (i = 0; i < m_observers.size(); i++) 
	{
		if (m_observers[i] == ob) break; 
	}
	m_observers.erase(m_observers.begin() + i); 
} 

// NOTIFY - protected - not called from outside
void Subject ::Notify () { 
	for (int i = 0; i < m_observers.size(); i++) 
		(m_observers[i])->Update(this); // call Update func. in observers
}

void Bank :: ChangePercent() {
	// do some things, then call Notify
	Notify();
}

//================================================================================
// Observer Implemenation
//================================================================================

// in this impl. the observer is attached only to one subject during its existence

Account:: Account(Subject* s) { 
	sbj = s; 
	sbj ->Attach(this); 
} 
Account :: ~Account() { 
	 sbj
	 ->Detach(this); 
} 
void Account::Update (Subject* ChngSubject) { 
	if (ChngSubject == sbj )
		cout << "Account is updated " << endl; 
} 


Newspaper:: Newspaper(Subject* s) { 
	sbj = s; 
	sbj ->Attach(this); 
} 
Newspaper :: ~Newspaper() { 
	 sbj ->Detach(this); 
} 
void Newspaper :: Update (Subject* ChngSubject) { 
	if (ChngSubject == sbj )
		cout << "Newspaper is informed " << endl; 
} 

//================================================================================
// Application
//================================================================================


int main()
{ 
	Bank		bnk; 
	Account		account(& bnk); 
	Newspaper 	paper(& bnk); 
	 bnk.ChangePercent();	// trigger
	// subject state change and update all it's observers
}



/*
class ClockTimer : public Subject {
public:
    ClockTimer();

    virtual int GetHour();
    virtual int GetMinute();
    virtual int GetSecond();

    void Tick();
};


void ClockTimer::Tick () {
    // update internal time-keeping state
    // ...
    Notify();
}


class Widget {
public:
    virtual void Draw();
};


class DigitalClock: public Widget, public Observer {
public:
    DigitalClock(ClockTimer*);
    virtual ~DigitalClock();

    virtual void Update(Subject*);
        // overrides Observer operation

    virtual void Draw();
        // overrides Widget operation;
        // defines how to draw the digital clock
private:
    ClockTimer* _subject;
};

DigitalClock::DigitalClock (ClockTimer* s) {
    _subject = s;
    _subject->Attach(this);
}

DigitalClock::~DigitalClock () {
    _subject->Detach(this);
}

void DigitalClock::Update (Subject* theChangedSubject) {
    if (theChangedSubject == _subject) {
        Draw();
    }
}

void DigitalClock::Draw () {
    // get the new values from the subject

    int hour = _subject->GetHour();
    int minute = _subject->GetMinute();
    // etc.

    // draw the digital clock
}

class AnalogClock : public Widget, public Observer {
public:
    AnalogClock(ClockTimer*);
    virtual void Update(Subject*);
    virtual void Draw();
    // ...
};


ClockTimer* timer = new ClockTimer;
AnalogClock* analogClock = new AnalogClock(timer);
DigitalClock* digitalClock = new DigitalClock(timer);

*/

