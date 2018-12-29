/***************************************************************************
    Author: Stav Ofer
    Creation date:  		2013-00-00    
    Last modified date:		2013-00-00
    Description: 	
****************************************************************************/

#include <stdio.h>



int main()
{
	float a = 1825811.0;
	int b = 1825811;
	
	
	Foo(&a);
	Foo(&b);
	Bar(&a);
	Bar(&b);
	PrintBinary(&a);
	PrintBinary(&b);
	
	++a;
	++b;
	
	Foo(&a);
	Foo(&b);
	Bar(&a);
	Bar(&b);
	PrintBinary(&a);
	PrintBinary(&b);
	
	++a;
	++b;
	
	Foo(&a);
	Foo(&b);
	Bar(&a);
	Bar(&b);
	PrintBinary(&a);
	PrintBinary(&b);
	
	
	return 0;
}

/*######################################################################*/



void Foo(int* ptr)
{
	printf("%d\n", *ptr);
}
/*######################################################################*/

void Bar(float* num)
{
	printf("%f\n", *num);
}
/*######################################################################*/


/* print an integer in binary */
void PrintBinary(int* _num)
{
	unsigned int mask = 1 << (32 - 1);
	int i;
	
	for(i=0 ; mask > 0; mask >>= 1, ++i )
	{
		if( !(i%8) && i) {
			printf("|");
		}
		printf("%d", ( (*_num & mask) != 0 ) );
	}
	printf("\n");
}
/*######################################################################*/

