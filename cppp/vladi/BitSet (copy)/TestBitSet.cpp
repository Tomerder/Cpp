// TestBitSet.cpp
//
//	Tests for the BitSet class
//	Author: Vladimir Krapp
//	Created on: 30/3/14
//	Last modified:

#include <iostream>

#include "BitSet.h"

using namespace std;

int main()
{
    BitSet<30> a;
    cout << "a: " << a << endl;

    BitSet<30> b(true);
    cout << "b: " << b << endl;

    a.SetBit(2);
    a.SetBit(4);
    a.SetBit(8);
    a.SetBit(10);
    a.SetBit(11);
    a.SetBit(20);
    a.SetBit(21);
    a.SetBit(22);

    cout << "a: " << a << endl;

    b ^= a;

    cout << "b: " << b << endl;

    BitSet<30>tmp = ~b;

    cout << "b: " << b << endl;
    cout << "tmp: " << tmp << endl;

    tmp <<= 1;
    cout << "tmp: " << tmp << endl;
    tmp <<= 10;
    cout << "tmp: " << tmp << endl;

    tmp = ~b;
	
    cout << "tmp: " << tmp << endl;
    tmp >>= 1;
    cout << "tmp: " << tmp << endl;
    tmp >>= 10;
    cout << "tmp: " << tmp << endl;

    cout << endl << endl;

    BitSet<20> bs;
    bs[1] = true;
    bs[10] = true;
    cout << bs << endl;
    
    bool what = bs[9];
    cout << "what is bs[9]: " << what << endl;
    what = bs[10];
    cout << "what is bs[10]: " << what << endl;
    bs[1] = bs[2] = bs[3] = bs[4] = bs[5] = bs[10];
    cout << bs << endl;

    return 0;
}









