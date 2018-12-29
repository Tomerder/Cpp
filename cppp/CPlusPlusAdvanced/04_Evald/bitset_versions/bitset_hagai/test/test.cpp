/**************************************************************************************
    Author: Hagai Moshe
    Creation date :      
    Last modified date:  
    Description : .
***************************************************************************************/


#include <iostream>
using namespace std;
#include "bitset.h"


const size_t NBITS = 100;




static void PrintWord(BitSet_t<NBITS>& _bitSet){
	bool p;
	size_t wordNum=NBITS/BITS_IN_WORD;

	for(int i=(NBITS-1); i>=0; --i){

		if( (int)(BITS_IN_WORD*wordNum-1) == i){
			cout << " ";
			--wordNum;
		}

		p = _bitSet.GetBit(i);
		cout << p;
	}
	cout << endl;
}




int main()
{

cout << "test ------------- " << endl;

	BitSet_t<NBITS> a;
	a[1]=1;
	a[2] = a[1];
//	a[33]=1;
//	a[66]=1;

PrintWord(a);	
//	
//	a <<= 34;

//PrintWord(a);

return 0;
}/*main*/






