/***************************************************************************
    Author: Stav Ofer
    Creation date:  		2013-00-00    
    Last modified date:		2013-00-00
    Description: 	
****************************************************************************/

//#include <cstdio>
#include <iostream>
#include <fstream>
using namespace std;



int main()
{
	fstream file;
	char buff[10] = {0};
	
	try {
		file.open("nofile.txt", fstream::in | fstream::out);
	}
	catch(exception& ex) {
		cout << ex.what() << endl;
		return 0;
	}
	
	if ( (file.rdstate() & fstream::failbit ) != 0 )
	{
    	cerr << "Error opening 'test.txt'\n";
    	return 0;
    }
	
	cout << "1" << endl;
	
	file << "hello";
	file.getline(buff, 10);
	
	cout << &file << endl;
	cout << "2" << endl;
	cout << buff << endl;
	
	return 0;
}

