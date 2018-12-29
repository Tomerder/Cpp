/*************************************************
    Author: Yiftach Ariel
    Creation date :      9.12.13
    Last modified date:  9.12.13
    Description : test for conf.
**************************************************/
#include <iostream>
#include <string>
#include "conf.h"
using namespace std;

//class Person {};

int main()
{
	CONF_VAL(int, VAL, 3, true);
	cout << VAL << endl;

	CONF_VAL(std::string, STR, "another string", true);
	cout << STR << endl;

	//CONF_VAL(Person, PERSON, Person());
	//cout << PERSON << endl;

	int temp;
	cin >> temp;

	return 0;
}