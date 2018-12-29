#include <stdio.h>
#include <stdlib.h>
#include <iostream> 
#include <string.h>
#include <string> 

#include "mystring.h"

using namespace std;
using namespace m10;

int main()
{
	/*Unit test*/
	const char* s1 = "dan";
	char* get, *get2;
	char pass[] = "pass", fail[]="fail";

	/*case 1: copy from char* + Cstr .*/
	String str1(s1);
	get = (char*)str1.Cstr();
	printf("CTOR + GetString test: %s\n",(!strcmp(get, s1)) ? pass : fail);

	/*case 2: default CTOR + assigment operator.*/
	String str2;
	str2 = str1;
	get = (char*)str1.Cstr();
	get2 = (char*)str2.Cstr();
	printf("default CTOR + assigment operator test: %s\n",(!strcmp(get, get2)) ? pass : fail);

	/*case 3: copy CTOR */
	String str3("blabla");
	String str4(str3);
	get = (char*)str3.Cstr();
	get2 = (char*)str4.Cstr();
	printf("copy CTOR test: %s\n",(!strcmp(get, get2)) ? pass : fail);

	/*case 4: Get const char reference. */
	String str6(s1);
	const char& getChar = str6[0];
	char getWithCharCopy = str6[0];
	printf("Get const char& with []: %s\n",(getChar == 'd' && getWithCharCopy ) ? pass : fail);

	/*case 5: Get char reference. */
	String str7(s1);
	char& getChar2 = str7[0];
	getChar2 = 'D';
	printf("Get char& with [], and change it: %s\n",(getChar2 == 'D' ) ? pass : fail);

	/*case 6: Check << operator. */
	String str8 = "Operator << check: pass";
	cout << str8 << endl;

	/*case 7: Double DTOR */
	String str9 = "lala";
	str9.~String();
	cout << "Double DTOR - pass" << endl;

	/*case 8: Length */
	String str10 = "lala";
	cout << "string length check: " << ((str10.Length() == 4) ? pass : fail) << endl;

	return 0;
}







