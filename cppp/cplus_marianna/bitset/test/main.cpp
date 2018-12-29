/**************************************************************************************
    Author: Marianna Shvartsman
    Creation date :      2013-11-12
    Last modified date: 2013-11-12
    Description : BitSet main
***************************************************************************************/
#include "bitset.h"

using namespace m7;

static const size_t S = 100; 
int main()
{
	
	BitSet<S> b;
	
	//test inline	void	Set(size_t _pos,bool _val);
	b.Set(0,true);
	b.Set(1,true);
	b.Set(25,true);
	b.Set(28,true);
	b.Set(56,true);
	b.Set(57,true);
	b.Set(58,true);
	b.Set(70,true);	
	b.Set(98,true);
	for(int i = 70; i < 97; ++i)
	{
		b.Set(i,true);
	}
//	b.Display();
	
	//test Get
	cout << b.Get(0) << endl;
	
	//test inline	Proxy	operator[](size_t _pos);
	//uses to set value at given position 
//	b[1] = false;
//	b.Display();
	
	//test inline	bool	operator[](size_t _pos)const;
	//returns value of of bitset on given position
//	b[0] = b[1];
//	b.Display();
	//test inline BitSet<S>::Proxy::operator bool() const
	if(b[25]) cout << "test" <<endl;
	
	BitSet<S> b2;
	
	for(int i = 1; i < 20; ++i)
	{
		b2.Set(i,true);
	}	
	
	for(int i = 45; i < 70; ++i)
	{
		b2.Set(i,true);
	}
	
	
	
	
	b.Display();
//	b2.Display();
	
	b >>= 35;
	b.Display();
	b <<= 35;
	b.Display();
	
//	b|= b2;
//	b.Display();
//	
//	b&= b2;
//	b.Display();
		
	return 0;
}

