#include <iostream>
#include "config.h"

using namespace std;

int main()
{
	Config con("Experis");

	//set
	con.Set<int>("myint", 24);
	con.Set<double>("mydouble", 2.4);
	con.Set<string>("str", "str changed");

	//get
	cout << "myint " <<con.Get<int>("myint",0) << " mydouble " << con.Get<double>("mydouble",0) << " str " << con.Get<string>("str","") << endl;

	//get default val
	cout << "myint " <<con.Get<int>("bla",0) << " mydouble " << con.Get<double>("bla",0) << " str " << con.Get<string>("bla","empty") << endl;

	return 0;
} 
