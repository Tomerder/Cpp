// BitSet.h
//
//	BitSet template class
//
//	Author: Vladimir Krapp
//	Created on: 30/3/14
//	Last modified:

#ifndef __BITSET_H__
#define __BITSET_H__

#include <algorithm>
#include <iostream>

#include <cassert>
#include <climits>
#include <cstddef>
#include <cstring>

typedef unsigned char Word;

// positive n for shift left, negative for shift right
//static inline Word shiftCirc(Word a, int n)
//{
//	n %= sizeof(Word) * CHAR_BIT;
//	return (a << n) | (a >> ((sizeof(Word) * CHAR_BIT)- n) );
//}

inline Word LeftBits(size_t _nBits, Word* _word)
{
    return *_word & ~((1 << (_nBits + 1)) - 1);
}

inline Word RightBits(size_t _nBits, Word* _word)
{
    return *_word & ((1 << ((sizeof(Word) * CHAR_BIT) - _nBits + 1)) - 1);
}

inline Word ClearLeftBits(size_t _nBits, Word* _word)
{
    return *_word &= ((1 << (_nBits+1)) - 1);
}


static size_t countOnes_one(size_t a)
{
    size_t count = 0;
    int i = sizeof(size_t)*CHAR_BIT -1;
    for (;i >= 0; --i)
    {
        count += (a & 1<<i)?1:0;
    }
    return count;
}


template <size_t N>
class BitSet
{

    public:
        friend class Bit;

        explicit BitSet(bool _initial = false); // V
        explicit BitSet(const bool* _arr);

        // Using compiler generated copy CTOR
        //  BitSet(const BitSet& _src); 

        // Using compiler generated DTOR
        //  ~BitSet 

        // Using compiler generated assignment op
        // BitSet& operator=(const BitSet& _src);

       
        void SetAll(bool _val);                 // V
        void SetBit(size_t _index);             // V
        void ClearBit(size_t _index);           // V

        bool GetBit(size_t _index) const;       // V

        size_t NumSetBits() const;              // V
      
        bool operator[](size_t _index) const;               // V
        typename BitSet<N>::Bit operator[](size_t _index);   // V

        bool operator==(const BitSet& _rhs);

        BitSet& operator&=(const BitSet& _src);         // V
        BitSet operator&(const BitSet& _src) const;         // V

        BitSet& operator|=(const BitSet& _src);         // V
        BitSet operator|(const BitSet& _src) const;         // V

        BitSet& operator^=(const BitSet& _src);         // V
        BitSet operator^(const BitSet& _src) const;         // V

        BitSet operator~() const;                       // V
 


        BitSet& operator<<=(size_t _shiftVal);          // V
        BitSet& operator>>=(size_t _shiftVal);          // V
        BitSet operator<<(size_t _shiftVal) const;      // V
        BitSet operator>>(size_t _shiftVal) const;      // V

        std::ostream& Print(std::ostream& _os) const;   // V


    public:
        class Bit
        {
            friend class BitSet<N>;

            public:
                bool operator=(bool _val);
                const Bit& operator=(const Bit&);
                operator bool() const;

            private:

                Bit(const BitSet<N> *_bitset, size_t _index)
                    :m_word(const_cast<Word*>(_bitset->m_data) + _index / m_bitsPerWord),
                    m_offset(_index % m_bitsPerWord)
                {
                }

                // Bit(const Bit&); // using generated copy CTOR
                
                void Set();
                void Clear();
                void Flip();
    
                // no copy 
                Bit(const Bit&);
                // no assignment
        

                Word * const m_word;
                const size_t m_offset;
       }; // class Bit


    private:

        static const size_t m_bitsPerWord = (sizeof(Word) * CHAR_BIT);
        static const size_t m_numWords = (N / m_bitsPerWord + 1);

        Word m_data[m_numWords];

        void SetData(bool _val)
        {
            memset(m_data, _val?(~0):0, sizeof(Word) * m_numWords);
        }
       
};

template <size_t N>
std::ostream& operator<<(std::ostream& _os, const BitSet<N>& _bitset)
{
    return _bitset.Print(_os);
}

template <size_t N>
BitSet<N>::
BitSet(bool _initial)
{
    SetData(_initial);
}


template <size_t N>
void BitSet<N>::
SetAll(bool _val)
{
    SetData(_val);
}



template <size_t N>
bool BitSet<N>::
GetBit(size_t _index) const
{
    return Bit(this, _index);
}

template <size_t N>
void BitSet<N>::
SetBit(size_t _index)
{
    assert (_index < N);

    Bit(this, _index).Set();
}

template <size_t N>
void BitSet<N>::
ClearBit(size_t _index)
{
    assert (_index < N);

    Bit(this, _index).Clear();
}


template <size_t N>
size_t BitSet<N>::
NumSetBits() const
{
    size_t count = 0;
    for(size_t i = 0; i < m_numWords; ++i) // Last word is ok, 
    {                                      //because zeroed out in CTOR
        count += countOnes_one(m_data[i]);
    }  

    return count;
}

static Word opAnd(Word _lhs, Word _rhs)
{
    return _lhs & _rhs;
}
static Word opOr(Word _lhs, Word _rhs)
{
    return _lhs | _rhs;
}
static Word opXor(Word _lhs, Word _rhs)
{
    return _lhs ^ _rhs;
}
static Word opNot(Word _word)
{
    return ~_word;
}


template <size_t N>
BitSet<N>& BitSet<N>::
operator&=(const BitSet<N>& _src)
{
    std::transform(_src.m_data, _src.m_data + m_numWords, 
                   m_data, m_data, opAnd ); 
    return *this;
}

template <size_t N>
BitSet<N> BitSet<N>::
operator&(const BitSet<N>& _src) const
{
    BitSet<N> result = *this;
    return result &= _src;
}

template <size_t N>
BitSet<N>& BitSet<N>::
operator|=(const BitSet& _src)
{
    std::transform(_src.m_data, _src.m_data + m_numWords, 
                   m_data, m_data, opOr ); 
    return *this;
}

template <size_t N>
BitSet<N> BitSet<N>::
operator|(const BitSet<N>& _src) const
{
    BitSet<N> result = *this;
    return result |= _src;
}

template <size_t N>
BitSet<N>& BitSet<N>::
operator^=(const BitSet& _src)
{
    std::transform(_src.m_data, _src.m_data + m_numWords, 
                   m_data, m_data, opXor); 
    return *this;
}

template <size_t N>
BitSet<N> BitSet<N>::
operator^(const BitSet<N>& _src) const
{
    BitSet<N> result = *this;
    return result ^= _src;
}

template <size_t N>
BitSet<N> BitSet<N>::
operator~() const
{
    BitSet<N> result = *this;
    std::transform(result.m_data, result.m_data + m_numWords, 
                   result.m_data, opNot); 
    return result;
}

template <size_t N>
BitSet<N>& BitSet<N>::
operator<<=(size_t _shiftVal)
{
    if(_shiftVal == 0)
    {
        return *this;
    }

    // Shift whole words
    size_t wordsToShift = _shiftVal / m_bitsPerWord;
    if(wordsToShift)
    {
        if(wordsToShift >= m_numWords)
        {
            SetAll(false);
            return *this; 
        }

        for(size_t i = m_numWords ; i > wordsToShift; )
        {
            --i;
            m_data[i] = m_data[i - wordsToShift];
        }

        memset(m_data + wordsToShift - 1, 
                0, wordsToShift * sizeof(Word));
    }
    // Shift bits
    size_t bitsToShift = _shiftVal % m_bitsPerWord;
    if(bitsToShift == 0)
    {
        return *this;
    }

    for(size_t i = m_numWords - 1; i >= 1U; --i )
    {
        m_data[i] <<= bitsToShift;
        size_t leftbits = LeftBits(bitsToShift, m_data + i - 1);
        m_data[i] |= ( leftbits >> (m_bitsPerWord - bitsToShift));
    }
    m_data[0] <<= bitsToShift;

    return *this;
}


template <size_t N>
BitSet<N>& BitSet<N>::
operator>>=(size_t _shiftVal)
{
    if(_shiftVal == 0)
    {
        return *this;
    }

    // Shift whole words
    size_t wordsToShift = _shiftVal / m_bitsPerWord;
    if(wordsToShift)
    {
        if(wordsToShift >= m_numWords)
        {
            SetAll(false);
            return *this; 
        }

        for(size_t i = 0; i < m_numWords - wordsToShift; i++)
        {
            m_data[i] = m_data[i + wordsToShift];
        }

        memset(m_data + m_numWords - wordsToShift - 1, 
                0, wordsToShift * sizeof(Word));
    }
    // Shift bits
    size_t bitsToShift = _shiftVal % m_bitsPerWord;
    if(bitsToShift == 0)
    {
        return *this;
    }

    for(size_t i = 0; i < m_numWords - 1; ++i )
    {
        m_data[i] >>= bitsToShift;
        size_t rightBits = RightBits(bitsToShift, m_data + i + 1);
        m_data[i] |= ( rightBits << (m_bitsPerWord - bitsToShift));
    }
    m_data[m_numWords - 1] >>= bitsToShift;

    ClearLeftBits(m_bitsPerWord*m_numWords - N ,&m_data[m_numWords-1]);
    return *this;
}


template <size_t N>
BitSet<N> BitSet<N>::
operator<<(size_t _shiftVal) const
{
    BitSet<N> result = *this;
    return result <<= _shiftVal;
}


template <size_t N>
BitSet<N> BitSet<N>::
operator>>(size_t _shiftVal) const
{
    BitSet<N> result = *this;
    return result >>= _shiftVal;
}


template <size_t N>
typename BitSet<N>::Bit BitSet<N>::
operator[](size_t _index)
{
    return Bit(this, _index);
}


template <size_t N>
std::ostream& BitSet<N>::
Print(std::ostream& _os) const
{
    for(size_t i = N-1; i > 0; --i)
    {
        _os << GetBit(i);
    }
    return _os;
}




//== Bit Class Operations ====================================

template <size_t N>
const typename BitSet<N>::Bit& BitSet<N>::Bit::
operator=(const Bit& _src)
{
    if(_src)
    {
        this->Set();
    } 
    else
    {
        this->Clear();
    }
    return *this;
}



template <size_t N>
void BitSet<N>::Bit::
Set()
{
    *m_word = *m_word | (1UL << (m_offset));
}

template <size_t N>
void BitSet<N>::Bit::
Clear()
{
    *m_word = *m_word & ~(1UL << (m_offset));
}

template <size_t N>
void BitSet<N>::Bit::
Flip()
{
    *m_word = *m_word ^ (1UL << (m_offset));
}


template <size_t N>
BitSet<N>::Bit::
operator bool() const
{
    return ((*m_word) ==  (*m_word | (1UL << (m_offset))));
}


template <size_t N>
bool BitSet<N>::Bit::
operator=(bool _val)
{
    if(_val)
    {
        this->Set();
    } 
    else
    {
        this->Clear();
    }
    return _val;
}











#endif //__BITSET_H__
