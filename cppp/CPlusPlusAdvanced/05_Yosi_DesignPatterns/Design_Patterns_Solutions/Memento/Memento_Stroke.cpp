#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct Point {
	float x;
	float y;
};
// --------------------------------------------------------------------- //
class Stroke {			// Memento
public:
	Point	beginPoint;
	Point	endPoint;
};
// --------------------------------------------------------------------- //
class FactoryStrokes {
public:

	// TYPEDEFS
	typedef vector<Stroke*>				memento_t;
	typedef vector<Stroke*>::iterator	it_t;

	typedef vector<memento_t*>			mementos_t;		// vector of vectors
	typedef vector<memento_t*>::iterator			mit_t;		
	typedef vector<memento_t*>::reverse_iterator	mrit_t;		
	//----------------------------------------------------//
	
	void AddStroke( Stroke* lastStroke )
	{
		mrit_t it = m_mementos.rbegin();	// last element
		memento_t* lstMemento = *it;
		memento_t newMemento(lstMemento->size());	// new memento
		copy(lstMemento->begin(),lstMemento->end(),newMemento.begin()); // copy old memento
				
		newMemento.push_back(lastStroke);	// save last Stroke
		m_mementos.push_back(&newMemento);	// save new Memento
	}
	//----------------------------------------------------//
	
	memento_t* getAllStrokes()
	{
		memento_t* lstMemento = *(m_mementos.rbegin());
		return lstMemento;
	}
	//----------------------------------------------------//
	
	void Undo() {
		if (m_mementos.size() == 0) return;	// if empty
		mit_t lstMemento = m_mementos.end();
		--lstMemento;
		m_mementos.erase(lstMemento);	//remove the last memento		
		//	RefreshPicture();
	}
	//----------------------------------------------------//
	
private:
	mementos_t m_mementos;		// stores all application states
};

// --------------------------------------------------------------------- //
// --------------------------------------------------------------------- //

int main() {

	return 0;
}

