/***************************************************************************
    Author: Stav Ofer
    Creation date:  		2013-10-26    
    Last modified date:		2013-10-26
    Description: 	make function X.Foo available only to class M, without
    				making M a friend
****************************************************************************/

#ifndef __FRIENDS_H__
#define __FRIENDS_H__


// giving M access to X.Foo() but not anything else
// all CTORs are private, so can be created only by friends
class FooAc
{
public:
//	friend class X;
	friend class M;
	
private:
	FooAc() {};
	FooAc(const FooAc& _copy) {};
};


// class with function Foo giving access to data member m_a
class X
{
public:
	void SetA(int _a) { m_a = _a; };
	int Foo(FooAc _fake = FooAc() )
		{ return m_a; };
	
	void Print() { std::cout << "X: " << m_a << std::endl; }
private:
	int m_a;
};

// needs access to X.m_a
class M
{
public:
	void SetB(X _x) { m_b = _x.Foo(FooAc()); }
	
	void Print() { std::cout << "M: " << m_b << std::endl; }
private:
	int m_b;
};



#endif  /* __FRIENDS_H__ */
