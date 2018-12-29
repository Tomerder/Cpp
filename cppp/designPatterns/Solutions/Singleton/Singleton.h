#ifndef SINGLETON_H
#define SINGLETON_H

// pointer based implementation

class Singleton { 
public: 
	static void Destroy()	{ delete sngPtr; sngPtr = 0; } 
	static Singleton* createObj() { 
		if (sngPtr == 0)	{ sngPtr = new Singleton; } 
			return sngPtr; 
	} 
protected: 
	virtual ~Singleton()	{ } 
private: 
	static Singleton* sngPtr; 
private: 
	Singleton() { }					// PRIVATE!!! 
	Singleton(const Singleton&);	// no  copy 
	void operator=(Singleton&);		// no copy 
}; 

#endif
