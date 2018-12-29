#include <iostream>
#include <string>

#include "lab.h"

using namespace std;

int main(int  argc , char** argv)
{
	/*both will use specialize because it is week symbol*/
	lab1();
	lab2();

	cout << "---------------------------------------------------------------------------------" << endl;
	cout << "template is placed twice , once for each compilation unit , but same code is called => compiler makes funcs as WEEK SYMBOL" << endl;
	cout << "---------------------------------------------------------------------------------" << endl;

	return 0;
}
