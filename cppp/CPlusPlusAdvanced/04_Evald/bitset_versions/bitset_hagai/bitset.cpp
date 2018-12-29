/**************************************************************************************
    Author: Hagai Moshe
    Creation date :      
    Last modified date:  
    Description : .
***************************************************************************************/

#include <iostream>
using namespace std;
#include "bitset.h" 






// ------------------------------------------------------------------------------------------------

typedef vector<size_t>::iterator Iterator;


// ------------------------------------------------------------------------------------------------

bool BitSetImp_t::GetBit(size_t _index, const vector<size_t>& _bitVec)
{
	size_t mask = 1 << (_index%BITS_IN_WORD);
	size_t word = _index/BITS_IN_WORD;

	return mask & _bitVec.at(word);
}




void BitSetImp_t::SetBit(size_t _index, bool _value, vector<size_t>& _bitVec)
{

	int mask = 1 << (_index%BITS_IN_WORD);
	int word = _index/BITS_IN_WORD;

	if(_value){
		_bitVec.at(word) |= mask;
	}
	else{
		_bitVec.at(word) &= ~mask;	
	}
}




void BitSetImp_t::OrAssingment( vector<size_t>& _bitVecToChange, const vector<size_t>& _bitVecB)
{
	for(size_t i=0; i<_bitVecB.size(); ++i){
		_bitVecToChange.at(i) |= _bitVecB.at(i);
	}
}




void BitSetImp_t::AndAssingment( vector<size_t>& _bitVecToChange, const vector<size_t>& _bitVecB)
{
	for(size_t i=0; i<_bitVecB.size(); ++i){
		_bitVecToChange.at(i) &= _bitVecB.at(i);
	}
}





void BitSetImp_t::LeftShiftAssingment( size_t _shift, size_t _numOfBits, std::vector<size_t>& _bitVec)
{
//	int lSide = 0;
//	int rSide = 0;
//	int NOShiftedWords = _shift/BITS_IN_WORD;
//	int shiftInWord = _shift - NOShiftedWords*BITS_IN_WORD;
//	

//	for(Iterator itr = _bitVec.rbegin(); itr!=_bitVec.rend(); --itr){

//		lSide = *(itr - NOShiftedWords) << shiftInWord;

//		rSide = (itr-NOShiftedWords != _bitVec.rend()) ? *(itr -(1+NOShiftedWords)):0 ;
//		rSide >>= (BITS_IN_WORD - shiftInWord);

//		*itr = lSide | rSide;
//	}

}



//cout << __LINE__ << endl;
//	size_t forCondition = _bitVec.size()-NOShiftedWords ;

/*
	for(int i=_bitVec.size()-1; i>=NOShiftedWords; --i){

		lSide = _bitVec.at(i - NOShiftedWords) << shiftInWord;

		rSide = (i-NOShiftedWords) ? _bitVec.at(i-1 - NOShiftedWords):0 ;
		rSide >>= (BITS_IN_WORD - shiftInWord);

		_bitVec.at(i) = lSide | rSide;
	}
*/
// ------------------------------------------------------------------------------------------------








/*

	size_t lSide = 0;
	size_t rSide = 0;

	for(size_t i=0; i<_bitVec.size(); ++i){
		
		rSide = lSide;									//the former word's left side is the current word's right side
		lSide = _bitVec.at(i) >> (BITS_IN_WORD-_shift);	//saves left side of the word
		_bitVec.at(i) <<= _shift;						//shift
		_bitVec.at(i) |= rSide;
	}

*/
