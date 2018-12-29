/**************************************************************************************
    Author: Marianna Shvartsman
    Creation date :      2013-11-04
    Last modified date: 2013-11-04
    Description : Proxy and BitSetService implementation
***************************************************************************************/
#include <iostream>
#include "bitset.h"

using namespace std;
using namespace m7;

//########################################################################
//		BitSetService class implementation
//########################################################################

size_t BitSetService::OrFunc(size_t _word1,size_t _word2)
{

		return (_word1 | _word2);
}

//------------------------------------------------------------------------
size_t BitSetService::AndFunc(size_t _word1, size_t _word2)
{
	return (_word1 & _word2);
}
//------------------------------------------------------------------------
//bitwise or
void	BitSetService::OrAndAssignment(vector<size_t>* _this, const vector<size_t>* _o, OrAndFunc _func)
{	 
 
	transform (_this->begin(), _this->end(), _o->begin(), _this->begin(), _func);
}

//------------------------------------------------------------------------
//shifts bitset left _shift bits

void	BitSetService::LeftShiftAssignment(vector<size_t>* _bitset, size_t _shift ,size_t _S)
{
	 //before left shift need to clean garbage
	size_t bitsToClear = _bitset->size() * BITS_IN_WORD - _S;
	(*_bitset)[_bitset->size() - 1] &= ((-1) >> bitsToClear);
		
	size_t bitsToShiftInWord = _shift%BITS_IN_WORD;//numBits = bitsToShiftInWord
	size_t wordsToShift = _shift/BITS_IN_WORD; //words to erase
	
	transform(_bitset->rbegin(), _bitset->rend(), _bitset->rbegin(), ShiftFunctor(bitsToShiftInWord, LEFT));
	
	_bitset->insert(_bitset->end(), wordsToShift, 0);
	_bitset->erase(_bitset->begin(), _bitset->begin() + wordsToShift);
}
//------------------------------------------------------------------------
//shifts bitset right _shift bits
void	BitSetService::RightShiftAssignment(vector<size_t>* _bitset, size_t _shift)
{
	size_t bitsToShiftInWord = _shift%BITS_IN_WORD; //numBits = bitsToShiftInWord
	size_t wordsToShift = _shift/BITS_IN_WORD; //words to erase
	
	transform(_bitset->begin(), _bitset->end(), _bitset->begin(),ShiftFunctor(bitsToShiftInWord, RIGHT));

	_bitset->insert(_bitset->begin(), wordsToShift, 0);
	_bitset->erase(_bitset->end() - wordsToShift, _bitset->end());
}


//-------Debugmod func PrintBits-----------------------------------------

#ifdef __DEBUG__
void	BitSetService::PrintBits(size_t _num)
{
	int len = BITS_IN_WORD;
	char arr[BITS_IN_WORD+1];
	int i = _num;

//	printf("Binary representation of num ");	
	
	for(i = len-1; i >=0;--i )
	{
		arr[i]  = (_num&1) + '0';
		_num>>=1;
	}
	
	arr[len] = '\0';
	cout << arr<<" ";	

}
#endif
//########################################################################
//		Shift Functor class implementation
//########################################################################
BitSetService::ShiftFunctor::ShiftFunctor(size_t _shift, Direction _dir):
m_prev(0),m_shift(_shift), m_dir(_dir){}

//------------------------------------------------------------------------
size_t BitSetService::ShiftFunctor::operator()(size_t _word)
{
	size_t tempWord = 0;
	
	if(m_dir == RIGHT)
	{
		tempWord |= (_word) >> (BITS_IN_WORD - m_shift);
		_word <<= m_shift;
	}
	else
	{
		tempWord |= (_word) << (BITS_IN_WORD - m_shift);
		_word >>= m_shift;
	}
	_word |= m_prev;
	m_prev = tempWord;
	
	return _word;
}
//------------------------------------------------------------------------

