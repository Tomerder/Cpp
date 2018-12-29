#include <iostream>
#include <string>
#include "Date.h"

void main() {
	int i;
	Date*  Dates[2];
	Dates[0] = new Date("Hebrew",  2, 12);
	Dates[1] = new Date("Arabic", 14, 11);
	for ( i=0; i < 2; i++)
		Dates[i]->tell();
}

