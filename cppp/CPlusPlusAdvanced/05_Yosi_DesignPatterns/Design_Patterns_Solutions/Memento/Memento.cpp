#include <list> 
#include <string> 
#include <iostream> 

using namespace std;
 
class Originator { 
private: 
   
	string state_; 
public: 
    
	class Memento {   
	private:         
		string state_;  
	public:        
		Memento(const string& stateToSave) : state_(stateToSave) { }        
		const string& getSavedState() { return state_; }     
	}; 
 
  
	void set(const string& state) {   
		cout << "Setting state to: " << state << endl; 
		state_ = state;   
	} 
   
	Memento* saveState() {     
		cout << "Saving state to Memento." << endl;        
		return new Memento(state_);     
	} 
	
	void restoreState(Memento* memento) { 
		state_ = memento->getSavedState();      
		std::cout << "Restoring state from Memento: " << state_ << std::endl;    
	} 
};



int main() {
	list<Originator::Memento*> savedStates;    
	Originator* originator = new Originator();    
	originator->set("StateA");   
	originator->set("StateB"); 
	savedStates.push_back(originator->saveState()); 
	originator->set("StateC");   
	savedStates.push_back(originator->saveState());  
	originator->set("StateD"); 
	originator->restoreState(savedStates.back()); 

	return 0; 
}