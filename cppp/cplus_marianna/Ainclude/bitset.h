/**************************************************************************************
    Author: Marianna Shvartsman
    Creation date :      2013-11-04
    Last modified date:  2013-11-04
    Description : BitSet Declaration
***************************************************************************************/
#ifndef __BITSET_H__
#define	__BITSET_H__

//Description:
// A BitSet stores bits (elements with two posible values)
//A class emulate array of bits with fixed size

//Operations:
//Random access to each element
//disjunction and conjunction of bitsets with same size


//Note:
//The class have nested class Proxy, don't worry , this will allow you to use [] for random access 
//BitSet will be large object need to be allocated on the heap

//example:
// BitSet bs<7>
// bs[3] = true
// if(bs[3])
// bs1[3] = bs2[8]
// bs1 |= bs2
// bs2 &= bs2
// bs1 <<=7

#include	<cstddef>
#include	<iostream>
#include	<algorithm>
#include	<vector>
#define __DEBUG__
typedef	enum OrAndOpr{OrOpr = 0, AndOpr}OrAndOpr;
typedef enum {LEFT,RIGHT} Direction;
typedef size_t(*OrAndFunc)(size_t,size_t);

namespace m7
{
using std::size_t; 
using std::vector;
using std::cout;
using std::endl;

//**********************************************************************
//		Declaration
//**********************************************************************

//Description:
//	Service base class of template class BitSet, contain implementation of long complex functions

class BitSetService
{
protected:
		
	//bitwise or
	static	void	OrAndAssignment(vector<size_t>* _this, const vector<size_t>* _o, OrAndFunc _func); 

	static	void	LeftShiftAssignment(vector<size_t>* _this, size_t _shift, size_t _S);
	//shifts bitset right _num bits
	static	void	RightShiftAssignment(vector<size_t>* _this, size_t _shift);
		
	static	size_t	OrFunc(size_t _word1,size_t _word2);
					
	static	size_t	AndFunc(size_t _word1, size_t _word2);
	
	//data mem
	static	const	size_t BITS_IN_WORD = sizeof(size_t)*8;
	
#ifdef __DEBUG__
	static void	PrintBits(size_t _num);	
#endif	
private:
	class ShiftFunctor
	{
	public:		
		explicit ShiftFunctor(size_t _shift, Direction _dir);
		size_t operator()(size_t _val);
	private:
		size_t m_prev;
		size_t m_shift;
		Direction m_dir; // shift direction
	};

};


template<size_t S>
class BitSet: private BitSetService
{
	class Proxy; //uses return type of operator[], provide convenient implementation of random access
public:
	//CTOR initialize bitset of requested size 
	explicit	BitSet (); 
	
	//generated copy CTOR, DTOR and operator=  
	
	
	//uses to set value at given position 
	inline	Proxy	operator[](size_t _pos);
	//returns value of of bitset on given position
	inline	bool	operator[](size_t _pos)const;
	
	//bitwise or
	BitSet&	operator|=(const BitSet& _o);
	//bitwise and 
	BitSet& operator&=(const BitSet& _o);
	//shifts bitset left _num bits
	BitSet& operator<<=(size_t _num);
	//shifts bitset right _num bits
	BitSet& operator>>=(size_t _num);
	
	//returns value of of bitset on given position
	inline	bool	Get(size_t _pos)const;
	//set value at given position 
	inline	bool	Set(size_t _pos,bool _val);
#ifdef __DEBUG__
	void	Display()const;	
#endif	

private:
	
	vector<size_t>	m_bitset;
	static	const	size_t NUM_WORDS = (S%BITS_IN_WORD == 0)? S/BITS_IN_WORD : S/BITS_IN_WORD + 1;
	static 	const	size_t m_numbits = S;
	//provide convenient implementation of random access
	class Proxy
	{
	public:
		explicit Proxy(BitSet* _bitset, size_t _pos);
		
		inline bool	operator=(const Proxy& _o);
		inline bool	operator=(bool _val);
		
		//implicit conversion to provide correct behavior if(_b[3])
		inline operator bool() const; 
	private:
		BitSet*	const   m_bitset;
		const  size_t	m_index;
	};
};


//***********************************************************************
//		BitSet CTOR
//***********************************************************************
template <size_t S>
BitSet<S>::BitSet(): m_bitset(NUM_WORDS,0) {} 
	
//***********************************************************************
//		operator|=
//***********************************************************************
template <size_t S>	
BitSet<S>&	BitSet<S>::operator|=(const BitSet& _o)
{
	OrAndAssignment(&m_bitset,&_o.m_bitset,OrFunc);
	return *this;
}

//***********************************************************************
//		operator&=
//***********************************************************************
template <size_t S>	
BitSet<S>&	BitSet<S>::operator&=(const BitSet& _o)
{
	OrAndAssignment(&m_bitset,&_o.m_bitset,AndFunc);
	return *this;
}

//***********************************************************************
//		operator<<=
//***********************************************************************
template <size_t S>	
BitSet<S>&	BitSet<S>::operator<<=(size_t _num)
{
	LeftShiftAssignment(&m_bitset,_num, S);
	return *this;
}

//***********************************************************************
//		operator >>=
//***********************************************************************
template <size_t S>	
BitSet<S>&	BitSet<S>::operator>>=(size_t _num)
{
	RightShiftAssignment(&m_bitset,_num);
	return *this;
}

//***********************************************************************
//		Get
//***********************************************************************	
template <size_t S>
inline	bool	BitSet<S>::Get(size_t _pos)const
{
	//assert(_pos < S);
	return m_bitset[_pos/BITS_IN_WORD] & 1u << _pos%BITS_IN_WORD;
	
}

//***********************************************************************
//		Set
//***********************************************************************
template <size_t S>
inline	bool	BitSet<S>::Set(size_t _pos,bool _val)
{
	//assert(_pos < S);

	if(_val)
	{
		m_bitset[_pos/BITS_IN_WORD] |= 1u << _pos%BITS_IN_WORD;
	}
	else
	{
		m_bitset[_pos/BITS_IN_WORD] &= ~(1u << _pos%BITS_IN_WORD);
	}
	
	return _val;
}


//***********************************************************************
//		Proxy operator[] 
//***********************************************************************
template<size_t S>
inline typename BitSet<S>::Proxy	BitSet<S>::operator[](size_t _pos)
{
	return Proxy(this,_pos);
}

//***********************************************************************
//		bool operator
//***********************************************************************
template<size_t S>
inline	bool	BitSet<S>::operator[](size_t _pos)const
{
	return Get(_pos);
}

//***********************************************************************
//		Display
//***********************************************************************
#ifdef __DEBUG__
template<size_t S>
void	BitSet<S>::Display()const
{
	for_each(m_bitset.rbegin(),m_bitset.rend(),PrintBits);
	cout << endl;
}
#endif
//########################################################################
//		proxy class implementation
//########################################################################


//***********************************************************************
//		proxy CTOR
//***********************************************************************
template<size_t S>
BitSet<S>::Proxy::Proxy(BitSet* _bitset, size_t _pos): m_bitset(_bitset), m_index(_pos) {}


//***********************************************************************
//		operator= uses to support bs[2]=bs[3] 
//***********************************************************************
template<size_t S>
inline bool	BitSet<S>::Proxy::operator=(const Proxy& _o)
{
	 return m_bitset->Set(m_index,(_o.m_bitset)->Get(_o.m_index));
}

//***********************************************************************
//		operator= uses to support bs[2]=true
//***********************************************************************
template<size_t S>
inline bool	BitSet<S>::Proxy::operator=(bool _val)
{

	return m_bitset->Set(m_index,_val);
	
}

//***********************************************************************
//		implicit conversion to provide correct behavior if(_b[3])
//***********************************************************************
template<size_t S>
inline BitSet<S>::Proxy::operator bool() const
{
	return m_bitset->Get(m_index);
}




}//end of namespace bitset
#endif //__BITSET_H__

