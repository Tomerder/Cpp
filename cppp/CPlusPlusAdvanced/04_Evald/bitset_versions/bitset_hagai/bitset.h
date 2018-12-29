/**************************************************************************************
    Author: Hagai Moshe
    Creation date :      
    Last modified date:  
    Description : .
***************************************************************************************/

#ifndef __BITSET_H__
#define __BITSET_H__


#include <vector>
#include <cstddef>
#include <cassert>
#include "bitsetImp.h"

// ------------------------------------------------------------------------------------------------

// two types of operator[]. one which returns bool, is for getting a bit value, the second is for the assignment operator

// template<std::size_t SIZE>.  to prevent operations between bitset of defferent size

// the operators |=, &= and <<= operate on the entire bitset

// class Proxy_t is used for operator[] 


// example:



// ------------------------------------------------------------------------------------------------



template <size_t SIZE>
class BitSet_t: private BitSetImp_t
{
	class Proxy_t; 
public:
	explicit BitSet_t(); //throw 
	
	//BitSet_t(const BitSet_t& _other);				using compiler generated
	//~BitSet_t();									using compiler generated
	//BitSet_t& operator=(const BitSet_t& _other);	using compiler generated
	
	inline bool 	operator[](size_t _index)const;		// return rvalue 
	inline Proxy_t	operator[](size_t _index);			// return lvalue

	inline BitSet_t& operator|=(const BitSet_t& _other);
	inline BitSet_t& operator&=(const BitSet_t& _other);
	inline BitSet_t& operator<<=(size_t _shift);
	inline BitSet_t& operator>>=(size_t _shift);

	inline bool GetBit(size_t _index)const;	
	inline void SetBit(size_t _index, bool _value);	
	
private:
	std::vector<size_t> m_bitVec;													


	class Proxy_t
	{
	public:	
		explicit Proxy_t(BitSet_t* _bitSet, size_t _index);

		inline	void operator=(const Proxy_t& _other);	
		inline	void operator=(bool _value);
		inline	operator bool()const;

	private:
		const size_t m_index;
		BitSet_t* const m_bitSet;
	
	};//Proxy_t

};





// ---------------------------------------------------BitSet_t---------------------------------------------



static const size_t BITS_IN_WORD = sizeof(size_t)*8 ;

template <size_t SIZE>
	BitSet_t<SIZE>:: BitSet_t():
	m_bitVec( SIZE/BITS_IN_WORD + bool( SIZE%BITS_IN_WORD ), 0)
{}




template <size_t SIZE>
inline bool BitSet_t<SIZE>:: operator[](size_t _index)const
{
	return BitSetImp_t:: GetBit( _index, m_bitVec);
}




template <size_t SIZE>
inline typename BitSet_t<SIZE>::Proxy_t	BitSet_t<SIZE>:: operator[](size_t _index)
{
	return BitSet_t<SIZE>::Proxy_t( this, _index);
}


// ------------------------------------------------------


template <size_t SIZE>
inline BitSet_t<SIZE>& BitSet_t<SIZE>::operator|=(const BitSet_t& _other)
{

	BitSetImp_t:: OrAssingment( m_bitVec, _other.m_bitVec);
	return *this;
}


template <size_t SIZE>
inline BitSet_t<SIZE>& BitSet_t<SIZE>::operator&=(const BitSet_t& _other)
{
	BitSetImp_t:: AndAssingment( m_bitVec, _other.m_bitVec);
	return *this;
}


template <size_t SIZE>
inline BitSet_t<SIZE>& BitSet_t<SIZE>::operator<<=(size_t _shift)
{
	BitSetImp_t:: LeftShiftAssingment(_shift, SIZE, m_bitVec);
	
	return *this;
}


// ------------------------------------------------------


template <size_t SIZE>
inline bool BitSet_t<SIZE>::GetBit(size_t _index)const
{

	assert(_index < SIZE);	

	return BitSetImp_t::GetBit( _index, m_bitVec);
}


template <size_t SIZE>
inline void BitSet_t<SIZE>::SetBit(size_t _index, bool _value)
{
	assert(_index < SIZE);

	BitSetImp_t:: SetBit( _index, _value, m_bitVec);
}


// ----------------------------------------------------Proxy_t--------------------------------------------


template <size_t SIZE>
BitSet_t<SIZE>::Proxy_t::Proxy_t(BitSet_t* _bitSet, size_t _index):
	m_index(_index),
	m_bitSet(_bitSet)
{}



template <size_t SIZE>
inline void BitSet_t<SIZE>::Proxy_t:: operator=(const BitSet_t<SIZE>::Proxy_t& _other)
{
	m_bitSet->SetBit( m_index, _other);
}




template <size_t SIZE>				
inline void BitSet_t<SIZE>::Proxy_t:: operator=(bool _value)
{
	m_bitSet->SetBit( m_index, _value);
}




template <size_t SIZE>	
inline BitSet_t<SIZE>::Proxy_t:: operator bool()const
{
	return m_bitSet->GetBit( m_index);
}

// ------------------------------------------------------------------------------------------------










#endif/*__BITSET_H__*/ 
