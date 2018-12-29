/***************************************************************************
    Author: Stav Ofer
    Creation date:  		2013-00-00    
    Last modified date:		2013-00-00
    Description: 	
****************************************************************************/

#include <iostream>




template <class T>
class Temp
{
public:
	T* GetPtr() { return s_ptr; }
	void SetPtr(T& _val) { *s_ptr = _val; }
	
private:
	static T* s_ptr;
};

template <class T>
T* Temp<T>::s_ptr = new T;


int main()
{
	Temp<int> myInt;
	Temp<int> myInt2;
	Temp<char> myChar;
	
	int one = 1;
	int two = 2;
	char A = 'a';
	
	myInt.SetPtr(one);
	myChar.SetPtr(A);
	
	myInt2.SetPtr(two);
	
	return 0;
}

/*######################################################################*/


