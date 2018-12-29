/************************************************************************
BitSet class. h file.
Author: Dan Bar-On.
Creation Date: 30.3.14 
Modified at:
Description:
************************************************************************/
#ifndef __BITSET_H__
#define __BITSET_H__

#include <stdlib.h>
#include <cstdio>
#include <iostream> 	//cout
#include <climits>		//CHAR_BIT
#include <cstring>		//memset
#include <algorithm>	//transform

namespace m10{
static const size_t BITS_WORD = CHAR_BIT*sizeof(size_t);


template <size_t N>
class BitSet {
class BitProxy;
public:
	inline BitSet();			//initialize(make zero)
	BitSet(const bool* _boolArray);	// MUST be at least size of N
	
	bool GetBit(size_t) const;
	void SetBit(size_t _index, bool _val);
	
	inline bool operator[] (size_t _index) const;	//GetBit
	inline BitProxy operator[] (size_t _index);	//SetBit
	
	BitSet& operator|= (const BitSet& _rhs);
	BitSet& operator&= (const BitSet& _rhs);
	BitSet& operator^= (const BitSet& _rhs);
	BitSet& operator<<= (size_t _moves);
	BitSet& operator>>= (size_t _moves);

	const BitSet operator~ () const;

	inline const BitSet operator<< ( size_t _moves) const;
	inline const BitSet operator>> ( size_t _moves) const;

	inline const BitSet operator| (const BitSet<N>& _rhs) const;
	inline const BitSet operator& (const BitSet<N>& _rhs) const;
	inline const BitSet operator^ (const BitSet<N>& _rhs) const;

	bool operator== (const BitSet<N>& _rhs) const;
	inline bool operator!= (const BitSet<N>& _rhs) const;
	
	size_t CountOn() const;
	
	void Print() const;

private:
	static const size_t m_arraySize = (N % BITS_WORD) ? N/BITS_WORD +1 : N/BITS_WORD;
	
	size_t m_data[ m_arraySize];

	class BitProxy {
	public:
		inline BitProxy(BitSet* _bitSet, size_t _index):m_bitSet(_bitSet), m_index(_index){};
		inline operator bool(){ return m_bitSet->GetBit(m_index);}
		inline bool operator=(bool _val){ m_bitSet->SetBit(m_index, _val); return _val; }
		inline BitProxy& operator=(const BitProxy& _bp){ m_bitSet->SetBit(m_index, (_bp.m_bitSet)->GetBit(m_index) ); return *this;}

	private:
		BitSet<N>* m_bitSet;
		size_t m_index;
	};
};


//-------------------------------------------------------------------------------
template <size_t N>
BitSet<N>::BitSet()
{
	memset(m_data, 0, m_arraySize * sizeof(size_t) );
}
//-------------------------------------------------------------------------------
template <size_t N>
BitSet<N>::BitSet(const bool* _boolArray)
{
	for (size_t i = 0; i < N; ++i)
	{
		SetBit( i, _boolArray[i]);
	}
}
//-------------------------------------------------------------------------------
template <size_t N>
bool BitSet<N>::GetBit(size_t _index) const 
{
	size_t mask = 1 << ( ( BITS_WORD-1) - _index %  BITS_WORD );
	return m_data[_index /  BITS_WORD] & mask;
}
//-------------------------------------------------------------------------------
template <size_t N>
void BitSet<N>::SetBit(size_t _index, bool _val)
{
	size_t word = 1 << ( ( BITS_WORD-1) - _index %  BITS_WORD );
	
	if (_val)
	{
		m_data[_index / BITS_WORD] |=  word;
	}
	else
	{
		m_data[_index / BITS_WORD] &=  ~word;
	}
}
//-------------------------------------------------------------------------------
template <size_t N>
bool BitSet<N>::operator[] (size_t _index) const
{
	return GetBit(_index);
}
//-------------------------------------------------------------------------------
template <size_t N>
typename BitSet<N>::BitProxy BitSet<N>::operator[] (size_t _index)
{
	return BitProxy(this, _index);
}
//-------------------------------------------------------------------------------
inline static size_t Or(size_t _numA, size_t _numB ) 
{
	return _numA |= _numB; 
}

template <size_t N>
BitSet<N>& BitSet<N>::operator|= (const BitSet& _rhs)
{
	std::transform(m_data, m_data + m_arraySize, _rhs.m_data, m_data, Or );
	return *this;
}
//-------------------------------------------------------------------------------
inline static size_t And(size_t _numA, size_t _numB ) 
{
	return _numA &= _numB; 
}

template <size_t N>
BitSet<N>& BitSet<N>::operator&= (const BitSet& _rhs)
{
	std::transform (m_data, m_data + m_arraySize, _rhs.m_data, m_data, And );
	return *this;
}
//-------------------------------------------------------------------------------
inline static size_t Xor(size_t _numA, size_t _numB ) 
{
	return _numA ^= _numB; 
}

template <size_t N>
BitSet<N>& BitSet<N>::operator^= (const BitSet& _rhs)
{
	std::transform (m_data, m_data + m_arraySize, _rhs.m_data, m_data, Xor );
	return *this;
}
//-------------------------------------------------------------------------------
template <size_t N>
const BitSet<N> BitSet<N>::operator| (const BitSet<N>& _rhs) const
{
	BitSet<N> bs = *this;
	return const_cast<BitSet<N>& > (bs) |= _rhs;
}
//-------------------------------------------------------------------------------
template <size_t N>
const BitSet<N> BitSet<N>::operator& (const BitSet<N>& _rhs) const
{
	BitSet<N> bs = *this;
	return const_cast<BitSet<N>& > (bs) &= _rhs;
}
//-------------------------------------------------------------------------------
template <size_t N>
const BitSet<N> BitSet<N>::operator^ (const BitSet<N>& _rhs) const
{
	BitSet<N> bs = *this;
	return const_cast<BitSet<N>& > (bs) ^= _rhs;
}
//-------------------------------------------------------------------------------
template <size_t N>
size_t BitSet<N>::CountOn() const
{
	size_t sum = 0;
    for (size_t i = 0; i < m_arraySize; ++i)
	{
		size_t word = m_data[i];

		for (size_t bit = 0; bit < BITS_WORD; ++bit)
		{
			sum += (word & 1);
			word >>= 1;
		}
	}
	return sum;
}
//------------------------------------------------------------------------
template<size_t N>
BitSet<N>& BitSet<N>::operator<<=(size_t _num)
{
	size_t bitsToShift = _num % BITS_WORD;
	size_t wordsToShift = _num / BITS_WORD;

	for(size_t i = 0; i < m_arraySize - wordsToShift; ++i)
	{
		if(wordsToShift)
		{
			m_data[i] = m_data[ i + wordsToShift];
		}
		m_data[i] <<= bitsToShift;
		if( i + wordsToShift < m_arraySize - 1)
		{
			m_data[i] |= m_data[ i + wordsToShift + 1] >> (BITS_WORD - bitsToShift);
		}
	}

	if (wordsToShift)
	{
		memset(&m_data[m_arraySize - wordsToShift ] , 0, (wordsToShift)*sizeof(size_t) );
	}
	return *this;
}
//------------------------------------------------------------------------

template<size_t N>
BitSet<N>& BitSet<N>::operator>>=(size_t _num)
{
	size_t bitsToShift = _num % BITS_WORD;
	size_t wordsToShift = _num / BITS_WORD;

	for(size_t i = m_arraySize - 1 ; i > wordsToShift; --i)
	{
		if(wordsToShift)
		{
			m_data[i] = m_data[ i - wordsToShift];
		}
		m_data[i] >>= bitsToShift;
		if( i - wordsToShift - 1 > 0)
		{
			m_data[i] |= m_data[ i - wordsToShift - 1] << (BITS_WORD - bitsToShift);
		}
	}

	if (wordsToShift)
	{
		memset(m_data, 0, (wordsToShift)*sizeof(size_t) );
	}
	return *this;
}

/*
template <size_t N>
BitSet<N>& BitSet<N>::operator>>= (size_t _num)
{
	while(_num) 
	{
		size_t bits = _num < N % BITS_WORD -1 ? _num : N % BITS_WORD -1;
	
		for(int i = m_arraySize - 1 ; i > 0 ; --i)
		{
			m_data[i] = (m_data[i] >> bits) | (m_data[i - 1] << (BITS_WORD - bits));	
		}
		m_data[0] >>= bits;
		_num -= bits;
	}
	 
	return *this;
}
*/
//------------------------------------------------------------------------
static size_t Not(size_t _num) 
{
	return ~_num; 
}

template <size_t N>
const BitSet<N> BitSet<N>::operator~ () const
{
	BitSet<N> bs;
	std::transform (m_data, m_data + m_arraySize,bs.m_data, Not );
	return bs;
}
//------------------------------------------------------------------------
template <size_t N>
const BitSet<N> BitSet<N>::operator<< ( size_t _moves) const
{
	BitSet<N> bs(*this);
	bs <<= _moves;
	return bs;	
}
//------------------------------------------------------------------------
template <size_t N>
const BitSet<N> BitSet<N>::operator>> ( size_t _moves) const
{
	BitSet<N> bs(*this);
	bs >>= _moves;
	return bs;	
}
//------------------------------------------------------------------------
template <size_t N>
bool BitSet<N>::operator== (const BitSet<N>& _rhs) const
{
	for (size_t i = 0; i < m_arraySize; ++i)
	{
		if (m_data[i] != _rhs.m_data[i]) return false;
	}
	return true;
}
//------------------------------------------------------------------------
template <size_t N>
bool BitSet<N>::operator!= (const BitSet<N>& _rhs) const
{
	return !(*this == _rhs);
}
//------------------------------------------------------------------------
template <size_t N>
void BitSet<N>::Print() const
{
		int c = N;
		
        for (size_t i = 0; i < m_arraySize; ++i)
        {
                size_t word = m_data[i];

                for (int bit = BITS_WORD -1; bit >=0  ; --bit)
                {
					std::cout << ((word & 1 << bit) != 0);
					if(!--c)
					{
						std::cout << std::endl;
						return;
					}
                }
        }
}
//------------------------------------------------------------------------
} // end of namespace m10
#endif	// #ifndef __BITSET_H__
