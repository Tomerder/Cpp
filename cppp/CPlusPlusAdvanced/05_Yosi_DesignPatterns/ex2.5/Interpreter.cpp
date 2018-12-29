/***************************************************************************
    Author: Stav Ofer
    Creation date:  		2013-11-07    
    Last modified date:		2013-11-07
    Description: 	convert decimal number to roman numerals
****************************************************************************/


#include <iostream>
#include <string>

#include "Interpreter.h"

using namespace std;


// static data members - lookup tables
const char* Ones2Hundreds_t::OnesLookup[4] = { "I", "IV", "V", "IX" };
const char* Ones2Hundreds_t::TensLookup[4] = { "X", "XL", "L", "XC" };
const char* Ones2Hundreds_t::HundredsLookup[4] = { "C", "CD", "D", "CM" };

const char** Ones2Hundreds_t::Lookups[3] = {OnesLookup, TensLookup, HundredsLookup};

const char* Thousands_t::oneThousand = "M";


Dec2Roman_t::Dec2Roman_t()
{
	ones2hundreds = new Ones2Hundreds_t;
	thousands = new Thousands_t;
	
//	ones = new Ones2Hundreds_t;
//	tens = new Tens_t(1);
//	hundreds = new Hundreds_t;
}
// ===================================================================== //

Dec2Roman_t::~Dec2Roman_t()
{
	delete ones2hundreds;
	delete thousands;
	
//	delete ones;
//	delete tens;
//	delete hundreds;
}
// ===================================================================== //




// ===================================================================== //

string& Dec2Roman_t::interpret(int _num)
{
	if(_num <= 0)
	{
		throw "can't interpret non-positive numbers";
	}
	if(_num >= 4000)
	{
		throw "the upper limit is 3999";
	}
	
	ones2hundreds->interpretImp(_num, result);
	
	if(_num >= 1000)
	{
		thousands->interpretImp(_num, result);
	}
	
	return result;
}
// ===================================================================== //


void Ones2Hundreds_t::interpretImp(int _num, std::string& _result)
{
	int digit;
	char** lookup;
	
	for( int i=0; i<3; ++i )
	{
		lookup = const_cast<char**>(Lookups[i]);
		digit = _num%10;
		
		
		if( digit == 9 )
		{
			_result.insert(0, lookup[NINE]);
		}
		else if( digit == 4 )
		{
			_result.insert(0, lookup[FOUR]);
		}
		
		
		else if( digit >= 5 )
		{
			
		}
		
		_result.insert( 0, lookup[digit] );
		
		_num /= 10;
		
		if(0 == _num) {
			break;
		}
	}
}
// ===================================================================== //


void Thousands_t::interpretImp(int _num, std::string& _result)
{
	for( _num /= 1000; _num > 0; _result.insert( 0, oneThousand ), --_num );
}
// ===================================================================== //

