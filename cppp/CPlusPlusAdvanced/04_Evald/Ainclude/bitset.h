/***************************************************************************
	Author: Stav Ofer
	Creation date:  		2013-11-04    
	Last modified date:		2013-11-14
	Description: 	Interface for bitset class: used to store a large number of
    				binary (on/off) variables.
    				Each size is a different class.
    				
    				- member access - random access through operator [] or GetBit, SetBit functions
    				- other operators: bitwise logical assignment operators |=, &= (between Bitsets),
    				  and left/right shift <<=, >>=
    				- additional functionality: Clear - to set all to 0, and Print.
    				
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
#include <cassert>


//######################################################################//
//	private service functions, ignore contents of this namespace
//######################################################################//
namespace bitset_service
{

using std::size_t;
using std::vector;

//---------- definitions ------------------/

// to distinguish between index and array/vector element
typedef size_t element;
typedef enum Sides { LEFT, RIGHT } Sides;

const size_t BITS_IN_WORD = 8*sizeof(element);

//------------ functions ------------------/

// bitwise OR, AND, shift left/right
void AndOr(vector<element>& _this, const vector<element>& _other, element(*_func)(element, element));
void Shift(vector<element>& _this, size_t _move, void(*_func)(vector<element>&, size_t, size_t, size_t));

void PrintImp(vector<element>& _this, size_t _numBits);

// implementations of AND/OR
inline element AndImp(element _numThis, element _numOther);
inline element  OrImp(element _numThis, element _numOther);

//implementations of shift right/left
void ShiftRight(vector<element>& _this, size_t _shift, size_t _jump, size_t _range);
void ShiftLeft(vector<element>& _this, size_t _shift, size_t _jump, size_t _range);

// INLINE FUNCTIONS

inline element AndImp(element _numThis, element _numOther)
{
	 return (_numThis & _numOther);
}
//---------------------------------------------------------------------
inline element OrImp(element _numThis, element _numOther)
{
	return (_numThis | _numOther);
}
//---------------------------------------------------------------------
}
// ############### END namespace bitset_service #########################//



//######################################################################//
//							BITSET NAMESPACE
//######################################################################//
namespace bitset_namespace
{

using namespace bitset_service;
using std::size_t;
using std::vector;

//---------------------------------------------------------------------//
//					CLASS BITSET (template in bitset size)
//---------------------------------------------------------------------//
template <size_t S>
class Bitset
{
	// foreward declatation - Proxy used as return type in operator []
	// user need not worry about it.
	class Proxy;
	
public:
	
	inline explicit Bitset();
	// using generated copy CTOR, DTOR, assignment operators
	
	/// temp
	Bitset(const Bitset& _other) : m_bitset(_other.m_bitset) {}

	
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
	
	inline void Print();
	
private:
	// actual bitset
	vector<element> m_bitset;
	
	// bitset size in words
	static const size_t NUM_WORDS = ( S % BITS_IN_WORD ) ? S/BITS_IN_WORD + 1 : S/BITS_IN_WORD;
	
	// PROXY class for bit manipulation through operator []
	// contains ptr to Bitset as array, & index of bit to manipulate
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
//------------------------- END class Bitset -----------------------------//


//######################################################################//
//							INLINE FUNCTIONS
//######################################################################//

// CTOR - initialize bitset to all-zero
template <size_t S>
inline Bitset<S>::Bitset() : m_bitset(NUM_WORDS, 0)
{}
//---------------------------------------------------------------------
//---------------------------------------------------------------------


//--------------------------- operators -----------------------------//

// return value of Bitset[_index]
template <size_t S>
inline bool Bitset<S>::operator [](size_t _index) const
{
	return GetBit(_index);
}
//---------------------------------------------------------------------

// use to set value of Bitset[_index]
template <size_t S>
inline  typename Bitset<S>::Proxy Bitset<S>::operator [](size_t _index)
{
	return Proxy(this, _index);
}
//---------------------------------------------------------------------

// OR - calling AndOr and OrImp from bitset_service
template <size_t S>
inline Bitset<S>& Bitset<S>::operator |=(const Bitset<S>& _o)
{
	AndOr(m_bitset, _o.m_bitset, OrImp);
	return *this;
}
//---------------------------------------------------------------------
// AND - calling AndOr and AndImp from bitset_service
template <size_t S>
inline Bitset<S>& Bitset<S>::operator &=(const Bitset<S>& _o)
{
	AndOr(m_bitset, _o.m_bitset, AndImp);
	return *this;
}
//---------------------------------------------------------------------

// shift left
template <size_t S>
inline Bitset<S>& Bitset<S>::operator <<=(size_t _move)
{
	if( _move < S )
	{
		Shift(m_bitset, _move, ShiftLeft);
	}
	else {
		Clear();
	}
	return *this;
}
//---------------------------------------------------------------------
// shift right
template <size_t S>
inline Bitset<S>& Bitset<S>::operator >>=(size_t _move)
{
	if( _move < S )
	{
		// clear garbage bits in last element
		if(S % BITS_IN_WORD)
		{
			size_t mask = ~( (size_t)0 ) << (S % BITS_IN_WORD);
			*(m_bitset.rbegin()) &= ~mask;
		}
		
		Shift(m_bitset, _move, ShiftRight);
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
template <size_t S>
inline bool Bitset<S>::GetBit(size_t _index) const
{
	assert(_index <= S);
	
	int vecIndex = _index/BITS_IN_WORD;
	int mask = 1 << (_index % BITS_IN_WORD);
	
	return ( m_bitset[vecIndex] & mask );
}
//---------------------------------------------------------------------

// SetBit
template <size_t S>
inline void Bitset<S>::SetBit(size_t _index, bool _val)
{
	assert(_index <= S);
	
	int vecIndex = _index/BITS_IN_WORD;
	int mask = 1 << (_index % BITS_IN_WORD);
	
	if(_val)
	{
		m_bitset[vecIndex] |= mask;
	}
	else {
		m_bitset[vecIndex] &= ~mask;
	}
}
//---------------------------------------------------------------------

// set all bits to 0
template <size_t S>
inline void Bitset<S>::Clear()
{
	m_bitset.assign(m_bitset.size(), 0);
}
//---------------------------------------------------------------------

template <size_t S>
inline void Bitset<S>::Print()
{
	PrintImp(m_bitset , S);
}

//---------------------------------------------------------------------//
//---------------------- class Proxy functions ------------------------//
//---------------------------------------------------------------------//

// CTOR
template <size_t S>
inline Bitset<S>::Proxy::Proxy(Bitset<S>* _bitset, size_t _index) :
	m_bitset(_bitset), m_index(_index)
{}
//---------------------------------------------------------------------

template <size_t S>
inline bool Bitset<S>::Proxy::operator =(const typename Bitset<S>::Proxy& _o)
{
	m_bitset->SetBit(m_index, _o);
	return _o;
}
//---------------------------------------------------------------------
template <size_t S>
inline bool Bitset<S>::Proxy::operator =(bool _val)
{
	m_bitset->SetBit(m_index, _val);
	return _val;
}
//---------------------------------------------------------------------
template <size_t S>
inline Bitset<S>::Proxy::operator bool() const
{
	return m_bitset->GetBit(m_index);
}
//---------------------------------------------------------------------


}
//################ END namespace bitset_namespace #######################//

#endif  /* __BITSET_H__ */

