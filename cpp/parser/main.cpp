#include <iostream>
#include <string.h>

#include "parser.h"

using namespace std;


void CheckParser(const string& _fileName);

/*------------------------------------------------------------------------------------*/

int main() 
{
	CheckParser("prog");	

	return 0;
}

/*------------------------------------------------------------------------------------*/

void CheckParser(const string& _fileName)
{
	Parser parser;
	
	if( ! parser.GetLinesFromFile("prog") ) {
		cout << "file is not open" << endl;
		return;
	}

	parser.ParseFile();

}

/*------------------------------------------------------------------------------------*/
