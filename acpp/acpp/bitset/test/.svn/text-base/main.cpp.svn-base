#include <iostream>

#include "bitset.h"

using namespace std;
using namespace m10;

int main()
{
	// Unit test
	string pass = "pass";
	// Case 1: Default CTOR, CTOR from bool* , copy CTOR, Print function, SetBit
	BitSet<64> bs1;
	bool boolArray[64] = {0};
	BitSet<64> bs2(boolArray);
	bs1.SetBit(3,true);
	BitSet<64> bs3(bs1);

	bs1.Print();
	bs2.Print();
	bs3.Print();

	if (!(bs1 == bs3 && bs1 != bs2 )) pass = "fail";
	cout << "Default CTOR, CTOR from bool* , copy CTOR, Print function, SetBit test: " << pass << endl;
	

	// Case 2: GetBit, SetBit
	BitSet<64> bs4;
	bs4.SetBit(3, true);
	bs4.SetBit(3, false);
	bs4.SetBit(1, true);
	bs4.SetBit(63, true);
	bs4.SetBit(31, true);
	bs4.SetBit(32, true);
	bs4.SetBit(33, true);

	if (!(bs4.GetBit(3) == false && bs4.GetBit(1) == true && bs4.GetBit(63) == true && 
		bs4.GetBit(31) == true && bs4.GetBit(32) == true && bs4.GetBit(33) == true)) pass = "fail";
	cout << "GetBit, SetBit test: " << pass << endl;	

	// Case 3: Operator [], operator[] const
	BitSet<64> bs5;
	bs5[3] = true;
	bs5[3] = false;
	bs5[1] = true;
	bs5[63] = true;
	bs5[31] = true;
	bs5[32] = true;
	bs5[33] = true;

	if (!(bs5[3] == false && bs5[1] == true && bs5[63] == true && 
		bs5[31] == true && bs5[32] == true && bs5[33] == true)) pass = "fail";
		cout << "Operator [], operator[] const test: " << pass << endl;	

	// Case 4: Operator | (uses operator |=)
	BitSet<64> bs6;
	bs6[3] = true;
	bs6[55] = true;
	BitSet<64> bs7;

	bs7 = bs7 | bs6;
	if (!(bs7 == bs6)) pass = "fail";
	cout << "Operator | (uses operator |=) test: " << pass << endl;	

	// Case 5: Operator & (uses operator &=)
	BitSet<64> bs8;
	bs8[3] = true;
	bs8[55] = true;
	BitSet<64> bs9;
	bs9[3] = true;

	bs8 = bs8 & bs9;
	if (!(bs8[3] == true && bs8[55] == false)) pass = "fail";
	cout << "Operator & (uses operator &=) test: " << pass << endl;	

	// Case 6: Operator ^ (uses operator ^=)
	BitSet<64> bs10;
	bs10[3] = true;
	bs10[55] = true;
	BitSet<64> bs11;
	bs11[3] = true;

	bs10 = bs10 ^ bs11;
	if (bs10[3] != false || bs10[55] != true) pass = "fail";
	cout << "Operator ^ (uses operator ^=) test: " << pass << endl;	


	// Case 7: Count bits on
	BitSet<64> bs100;
	bs100[3] = true;
	bs100[55] = true;
	if (bs100.CountOn() != 2 ) pass = "fail";
	cout << "Count bits on test: " << pass << endl;	

	// Case 8: Operator << (uses operator <<=)
	BitSet<64> bs12;
	bs12[3] = true;
	bs12[55] = true;

	bs12 <<= 2;

	if (bs12[3] != false || bs12[1] != true || bs12[55] != false || bs12[53] != true) pass = "fail";

	bs12 = bs12 << 40;

	if (bs12[3] != false || bs12[1] != false || bs12[13] != true) pass = "fail";

	cout << "Operator << (uses operator <<=) test: " << pass << endl;	


	pass = "pass";
	// Case 7: Operator >>(uses operator >>=)
	BitSet<64> bs13;
	bs13[3] = true;
	bs13[55] = true;
	bs13[30] = true;

	bs13 = bs13 >> 2;

	if (bs13[3] != false || bs13[5] != true || bs13[55] != false || bs13[57] != true) pass = "fail";
	if (bs13[32] != true) pass = "fail";

	bs13 = bs13 >> 40;
	if (bs13[45] != false || bs13[5] != false || bs13[13] != true) pass = "fail";

	cout << "Operator >>(uses operator >>=) test: " << pass << endl;	

	BitSet<64> bs14;
//	for (int i=0; i< 64; i+=2) bs14[i] = true;
//	bs14[5] = 1;bs14[7] = 1;bs14[11] = 1;bs14[27] = 1;bs14[35] = 1;bs14[44] = 1;bs14[56] = 1;bs14[62] = 1;
	bs14[55] = 1;
	bs14.Print();
	bs14 <<= 50;
	bs14.Print();

	bs14 >>= 50;
	bs14.Print();




	return 0;
}
