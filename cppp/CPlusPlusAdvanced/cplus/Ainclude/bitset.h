/***************************************************************************
	Author: Stav Ofer
	Creation date:  		2013-11-04    
	Last modified date:		2013-11-04
	Description: 	Interface for bitset class: used to store a large number of
    				binary (on/off) variables.
    				Each size is a different class.
    				
    				- member access - random access through operator [] or GetBit, SetBit functions
    				- other operators: bitwise logical assignment operators |=, &= (between Bitsets),
    				  and left/right shift <<=, >>=
    				- additional functionality: Clear, to set all to 0.
    				
    				- contains class Proxy for use in the [] operator, user need not know anything about it.
    				
    				- examples of usage:
    				  
    				  Bitset<20> bs1;
    				  bs1[5] = true;
    				  bs1[12] = bs1[5];
					  Bitset<20> bs2(bs1);
					  bs2 <<= 3;
					  bs1 |= bs2;
					  if(bs1[15]) {...}
					  
****************************************************************************/

#ifndef __BITSET_H__
#define __BITSET_H__

#include <vector>


typedef enum Sides { LEFT, RIGHT } Sides;
typedef enum LogicAndOr { AND, OR } LogicAndOr;


namespace bitset_namespace
{

using std::size_t;
using std::vector;

// private class for non-template functionality
class BitsetService;

//######################################################################//
//								CLASS BITSET
//######################################################################//
template <size_t S>
class Bitset : private BitsetService
{
	// foreward declatation - Proxy used as return type in operator []
	// user need not worry about it.
	class Proxy;	

public:
	
	inline explicit Bitset();
	// using generated copy CTOR, DTOR, assignment operators
	
	// operator [] for access to specific bits
	inline bool  operator [](size_t _index) const; 	// return value of Bitset[_index]
	inline Proxy operator [](size_t _index); 		// use to set value of Bitset[_index]
	
	// bitwise OR, AND, <<, >>
	inline Bitset& operator |=(const Bitset& _o);
	inline Bitset& operator &=(const Bitset& _o);
	inline Bitset& operator <<=(size_t _move);
	inline Bitset& operator >>=(size_t _move);
	
	// explicit functions to access specific bits
	inline bool GetBit(size_t _index) const;
	inline void SetBit(size_t _index, bool _val);
	
	inline void Clear();	// set all bits to false
	
private:
	// bitset size in words
	static const size_t NUM_WORDS = ( S % BITS_IN_WORD ) ? S/BITS_IN_WORD + 1 : S/BITS_IN_WORD;
	
	// actual bitset
	vector<size_t> m_bitset;
	
	// PROXY class for bit manipulation through operator []
	// contains ptr to Bitset's array, & index of bit to manipulate
	class Proxy
	{	
	public:
		inline explicit Proxy(Bitset* _bitset, size_t _index);	
		
		// assignment - doesn't change the proxy object,
		// changes the relevant bit in the bitset
		inline bool operator =(const Proxy& _o);
		inline bool operator =(bool _val);
		
		inline operator bool() const;
		
	private:
		Bitset* const m_bitset;
		const size_t  m_index;
	};
	// end PROXY
};
//------------------------- end class Bitset -----------------------------//


//######################################################################//
//								PRIVATE
//######################################################################//


//---------------------------------------------------------------------//
//							Class BitService
//---------------------------------------------------------------------//
class BitsetService
{
//public:
// uses generated CTORs, DTOR, assignment operator
	
protected:
	// bitwise OR, AND, shift left/right
	static void AndOr(vector<size_t>& _this, const vector<size_t>& _other, LogicAndOr _andOr);
	static void Shift(vector<size_t>& _this, size_t _move, Sides _side);
		
	// constants for size calculation
	static const size_t BITS_IN_WORD = 8*sizeof(size_t);
	
private:
	// service functions
	size_t AndImp(size_t _numThis, size_t _numOther);
	size_t  OrImp(size_t _numThis, size_t _numOther);
};
//---------------------- end class BitsetService -------------------------//


//######################################################################//
//							INLINE FUNCTIONS
//######################################################################//

// CTOR - initialize bitset to all-zero
inline Bitset() : m_bitset(NUM_WORDS, 0)
{}
//---------------------------------------------------------------------
//---------------------------------------------------------------------


//--------------------------- operators -----------------------------//

// return value of Bitset[_index]
inline bool  operator [](size_t _index) const
{
	return GetBit(_index);
}
//---------------------------------------------------------------------

// use to set value of Bitset[_index]
inline Proxy operator [](size_t _index)
{
	return Proxy(&m_bitset, _index);
}
//---------------------------------------------------------------------

// OR
inline Bitset<S>& operator |=(const Bitset<S>& _o)
{
	BitsetService(m_bitset, _o.m_bitset, OR);
	return *this;
}
//---------------------------------------------------------------------
// AND
inline Bitset<S>& operator &=(const Bitset<S>& _o)
{
	BitsetService(m_bitset, _o.m_bitset, AND);
	return *this;
}
//---------------------------------------------------------------------

// shift left
inline Bitset<S>& operator <<=(size_t _move)
{
	if( _move < S )
	{
		Shift(m_bitset, _move, LEFT);
	}
	else {
		Clear();
	}
	return *this;
}
//---------------------------------------------------------------------
// shift right
inline Bitset<S>& operator >>=(size_t _move)
{
	if( _move < S )
	{
		Shift(m_bitset, _move, RIGHT);
	}
	else {
		Clear();
	}
	return *this;
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------


//--------------------------- functions -----------------------------//

// GetBit
inline bool GetBit(size_t _index) const
{
	assert(_index <= S); // ???
	
	int vecIndex = _index/BITS_IN_WORD;
	int mask = 1 << (_index % BITS_IN_WORD);
	
	return ( m_bitset[vecIndex] & mask );
}
//---------------------------------------------------------------------

// SetBit
inline void SetBit(size_t _index, bool _val);
{
	assert(_index <= S); // ???
	
	int vecIndex = _index/BITS_IN_WORD;
	int mask = 1 << (_index % BITS_IN_WORD);
	
	if(_val)
	{
		m_bitset[vecIndex] |= mask;
	}
	else {
		m_bitset[vecIndex] &= ^mask;
	}
}
//---------------------------------------------------------------------

// set all bits to 0
inline void Clear()
{
	m_bitset.assign(m_bitset.size(), 0);
}
//---------------------------------------------------------------------


//---------------------------------------------------------------------//
//---------------------- class Proxy functions ------------------------//
//---------------------------------------------------------------------

// CTOR
inline Proxy:: Proxy(Bitset* _bitset, size_t _index) :
	m_bitset(_bitset), m_index(_index)
{}
//---------------------------------------------------------------------

inline bool Proxy:: operator =(const Proxy& _o)
{
	return m_bitset->GetBit(_o.m_index);
}
//---------------------------------------------------------------------

inline bool Proxy:: operator =(bool _val)
{
	m_bitset->SetBit(m_index, _val);
	return _val;
}
//---------------------------------------------------------------------

inline Proxy:: operator bool() const
{
	return m_bitset->GetBit(m_index);
}
//---------------------------------------------------------------------


} // end namespace bitset_namespace

#endif  /* __BITSET_H__ */

