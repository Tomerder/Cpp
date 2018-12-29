#include <cstdio>
#include <cstdlib>

using namespace std;

/*-----------------------------------------------------------*/

extern int globExtU;
int globU;     /*week symbol*/
static int globStatU;

extern int globExt = 57;
int glob = 7;
static int globStat = 5;

int Foo();
static int FooStat();

int main()
{
	static int locStatU;	
	static int locStat = 55;	
	int loc = 77;	

	return 0;
}

/*-----------------------------------------------------------*/
