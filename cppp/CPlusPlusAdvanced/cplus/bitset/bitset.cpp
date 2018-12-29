/***************************************************************************
	Author: Stav Ofer
	Creation date:  		2013-11-04    
	Last modified date:		2013-11-05
	Description: 	Bitset class implementation
***************************************************************************/

#include <cassert>
#include <vector>
#include <algorithm>

#include "bitset.h"

using namespace std;
using namespace bitset_service;
using namespace bitset_namespace;

typedef size_t(*ShiftFunc)(size_t _num, size_t _shift);


// continue work on shift functions


// !!! to put in namespace bitset_service

//void RightShiftImp(vector<size_t>::iterator _itr, size_t _jump, size_t _shift);
//void LeftShiftImp(vector<size_t>::reverse_iterator _itr, size_t _jump, size_t _shift);


//######################################################################//


// and/or
void AndOr(vector<size_t>& _this, const vector<size_t>& _other, ShiftFunc _func)
{
	assert( _this.size() == _other.size() );	// ???
	
	// get ptr to relevant function
//	size_t(*func)(size_t, size_t);
//	func = (_andOr == AND) ? AndImp : OrImp;
	
	// act on the range [_this.begin, _this.end) and the range starting at _other.begin,
	// storing the results in the range starting at _this.begin, applying func
	transform( _this.begin(), _this.end(), _other.begin(), _this.begin(), _func );
}

//----------------------- functions for transform ----------------------------//

size_t AndImp(size_t _numThis, size_t _numOther)
{
	 return (_numThis & _numOther);
}
//---------------------------------------------------------------------
size_t OrImp(size_t _numThis, size_t _numOther)
{
	return (_numThis | _numOther);
}
//---------------------------------------------------------------------
//######################################################################//


// shift left/right
void Shift(vector<size_t>& _this, size_t _move, Sides _side)
{
	size_t jump = _move/BITS_IN_WORD;
	size_t shift = _move % BITS_IN_WORD;
	size_t complement = BITS_IN_WORD - _move;
	
	
	// !!! clean - check big/little endian !!!
	
	
	
	if(_side==RIGHT)
	{
		vector<size_t>::iterator rightItr = _this.begin();	// iterator for shift right
		vector<size_t>::iterator rightItr2 = rightItr+jump;
		
		
		transform( , , , , );  //_this.begin(), _this.end(), _other.begin(), _this.begin(), func );
		
	}
	else {
		vector<size_t>::reverse_iterator leftItr = _this.rbegin(); // reverse itr for shift left
		
		
		
		
	}
}
//######################################################################//


//--------------------- functors for transform --------------------------//

struct ShiftFunctor
{
	inline explicit ShiftFunctor(size_t _shift, size_t _prev);
	inline size_t operator()(size_t _new);
	
	size_t m_shift;
	size_t m_prev;
	
	static size_t(*m_func)(size_t, size_t, size_t, ShiftFunc, ShiftFunc);
};


ShiftFunctor::m_func = ShiftImp;

inline ShiftFunctor::ShiftFunctor(size_t _shift, size_t _prev) :
		m_shift(_shift), m_prev(_prev), 
		{}
//---------------------------------------------------------------------

inline size_t ShiftFunctor::operator()(size_t _new, ShiftFunc _func1, ShiftFunc _func2)
{
	size_t temp - m_prev;
	m_prev = _new;
	return m_func(_orig, _new, temp, m_shift, _func1, _func2);
}
//---------------------------------------------------------------------



size_t ShiftImp(size_t _new, size_t _prev, size_t _shift, ShiftFunc _func1, ShiftFunc _func2)
{
	return  _func1(_prev,_shift) | _func2(_new, BITS_IN_WORD - _shift);
}
//---------------------------------------------------------------------

// actual shift left/right
size_t RightShiftImp(size_t _num, size_t _shift)
{
	return _num >> _shift;
}
//---------------------------------------------------------------------
size_t LeftShiftImp(size_t _num, size_t _shift)
{
	return _num << _shift;
}
//---------------------------------------------------------------------





// shift left/right
//void Shift(vector<size_t>& _this, size_t _move, Sides _side)
//{
//	size_t jump = _move/BITS_IN_WORD;
//	size_t shift = _move % BITS_IN_WORD;
//	size_t complement = BITS_IN_WORD - _move;
//	
//	
//	// !!! clean - check big/little endian !!!
//	
//	
//	
//	if(_side==RIGHT)
//	{
//		vector<size_t>::iterator rightItr = _this.begin();	// iterator for shift right
//		for(size_t i=0; i<_this.size()-jump; ++i, ++rightItr)
//		{
//			*rightItr = ( *(rightItr + jump) >> shift );
//			
//			size_t temp = (*(rightItr+1) << complement);
//			*rightItr |= temp;
//		}
//		
//	}
//	else {
//		vector<size_t>::reverse_iterator leftItr = _this.rbegin(); // reverse itr for shift left
//		for(size_t i=0; i<_this.size()-jump; ++i, ++leftItr)
//		{
//			*leftItr = (*(leftItr + jump) << shift);
//			
//			size_t temp = (*(leftItr+1) >> complement);
//			*leftItr |= temp;
//		}
//	}
//}
//######################################################################//










// old - for_each not good b/c acting on *iterator, but here we need to go back and forth
// along the vector with the iterator, so dereferenced is not good enough

//// shift left/right
//void BitsetService::BitsetService::Shift(vector<size_t>& _this, size_t _move, Sides _side)
//{
//	size_t jump = _move/BITS_IN_WORD;
//	size_t shift = _move % BITS_IN_WORD;
//	
//	vector<size_t>::iterator rightItr = _this.begin();	// iterator for shift right
//	vector<size_t>::reverse_iterator leftItr = _this.rbegin(); // reverse itr for shift left
//	
//	// use for_each with relevant function (left/right)
//	if(_side==RIGHT)
//	{
//		for_each(rightItr, _this.end(), ShiftFunctor(jump, shift, RightShiftImp)); // ??
//	}
//	else {
//		for_each(leftItr, _this.rend(), ShiftFunctor(jump, shift, LeftShiftImp)); // ??
//	}
//	
//	
//	
//	
//}


////--------------------- functors for for_each --------------------------//

//struct ShiftFunctor
//{
//	inline explicit ShiftFunctor(size_t _jump, size_t _shift, /*void(*_func)()*/ );
//	inline void operator()(size_t& _num);
//	
//	size_t m_jump;
//	size_t m_shift;
////	void(*)(/**/) m_func;
//};
////---------------------------------------------------------------------

//inline ShiftFunctor::ShiftFunctor(size_t _jump, size_t _shift, /*void(*_func)()*/ ) :
//		m_jump(_jump), m_shift(_shift) // , m_func(_func)
//		{}
////---------------------------------------------------------------------
//inline void ShiftFunctor::operator()(size_t& _num)
//{
//	m_func(_num, m_jump, m_shift);
//}
////---------------------------------------------------------------------




