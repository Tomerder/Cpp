/************************************************************************
Uncopyable
Author: Dan Bar-On.
Creation Date: 23.04.14
Modified at:
Description: Prevents class from copying(ctor or assignment)
************************************************************************/
#ifndef __UNCOPYABLE_H__
#define __UNCOPYABLE_H__

// Private inherit from this class to achieve non-copyability

class Uncopyable{
protected:
	Uncopyable(){}
	~Uncopyable(){}
private:
	Uncopyable(const Uncopyable&);
	Uncopyable& operator=(const Uncopyable&);
};

#endif // #ifndef __UNCOPYABLE_H__
