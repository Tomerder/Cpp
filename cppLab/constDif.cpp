#include <stdio.h>
#include <stdlib.h>

/*-----------------------------------------------------------*/

const int gi=3;

int main()
{
	const int i=5;

	int* p = (int*)&gi;
	printf("%d %d\n", gi, *p);	
	
	//*p = 7; seg fault 
	
	p = (int*)&i;
	printf("%d %d\n", i, *p);	
	
	*p = 7;
	
	printf("%d %d\n", i, *p);

	return 0;
}

/*-----------------------------------------------------------*/
