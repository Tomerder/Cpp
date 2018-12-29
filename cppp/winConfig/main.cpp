#include <iostream>
#include "config.h"
using namespace std;

int main()
{
	Config conf("Experis"); 


	conf.Set<int>( "myint", 24);
	conf.Set<double>( "mydouble", 2.4);
	conf.Set<string>("str","str changed!");


	// int
	int myint = conf.Get<int>("myint", 0);
	cout << "The int from the registry is: " << myint << endl;
	cout << "write wrong value name and get the default: " << conf.Get<int>("falseName", 0) << endl;

	//string
	string str = conf.Get<string>("str", "get failed");
	cout <<"the string from the registry: " << str << endl;
	cout << "write wrong value name and get the default: " << conf.Get<string>("falseName", "false") << endl;

	//double
	double mydouble = conf.Get<double>("mydouble", -1.1);
	cout <<"the double from the registry: " << mydouble << endl;
	cout << "write wrong value name and get the default: " << conf.Get<double>("falseName", -1.1) << endl;



	return 0;
}