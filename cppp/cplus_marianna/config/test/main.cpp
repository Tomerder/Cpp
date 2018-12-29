/**************************************************************************************
    Author: Marianna Shvartsman
    Creation date :      2013-12-10
    Last modified date: 2013-12-10 
    Description : Registry test
***************************************************************************************/
#include <iostream>
using namespace std;

#include "config.h"
using namespace config_m7;

int main()
{
	CONF_VAL(int, VAL, 3);
	cout << VAL << endl;

	CONF_VAL(string, STR, "another string");
	cout << STR << endl;

	//CONF_VAL(Person, PERSON, Person());
	//cout << PERSON << endl;

	int temp;
	cin >> temp;
	return 0;
}