#include "Singleton.h"
 
int main() { 
	Singleton* ps1 = Singleton::createObj(); 
	Singleton* ps2 = Singleton:: createObj (); 

	Singleton::Destroy();	// was created by static mem-function, so have to be destroyed in similar way
} 



