/***************************************************************************
    Author: Stav Ofer
    Creation date:  		2013-00-00    
    Last modified date:		2013-00-00
    Description: 	
****************************************************************************/

//#include <cstdio>
#include <iostream>
using namespace std;

#include "Polygon.h"

int main()
{
	CPolygon p1(4,3);
	
	CPolygon p2 = p1;
	
	cout << p1.get_width() << " " << p1.get_height() << endl;
	cout << p2.get_width() << " " << p2.get_height() << endl;
	
	return 0;
}

