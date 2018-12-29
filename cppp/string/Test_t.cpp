#include <iostream>

#include "string1.h"

using namespace std;
using namespace String;

#define PRINT_LINE cout << "-----------------------------------------" << endl;


int main() 
{
	PRINT_LINE
	cout << "String_t str;" << endl; 
	String_t str;
	PRINT_LINE;

	String_t str1("s1");
	cout << "String_t str1('s1');  => " << str1 << endl;
	PRINT_LINE;
	
	String_t str2 = "s2";
	cout << "String_t str2 = 's2';  => " << str2 << endl;
	PRINT_LINE;
	
	String_t str2B = str2;
	cout << "String_t str2B = str2;  => " << str2B << endl;
	PRINT_LINE;
	
	str = str2;
	cout << "str = str2;  => " << str << endl;
	PRINT_LINE;
	
	str = "s";
	cout << "str = 's';  => " << str << endl;
	PRINT_LINE;
	
	String_t str3(str);
	cout << "String_t str3(str);  => " << str3 << endl;
	PRINT_LINE;
	
	String_t str4("abcdefg");
	cout << "str4  => " << str4 << endl;
	cout << "str4[2]  => " << str4[2] << endl;
	PRINT_LINE;
	
	str4[2] = 'T';
	cout << "str4[2] = 'T'; =>  str4  => " << str4 << endl;
	PRINT_LINE;
	
	cout << "String_t(str4)[2]  => " << String_t(str4)[2] << endl;
	PRINT_LINE;
	
	cout << "String_t('t1234567')[2]  => " << String_t("t1234567")[2] << endl;
	PRINT_LINE;
	
	const String_t strConst("abcd");
	cout << "strConst[2]   => " << strConst[2] << endl;
	PRINT_LINE;
	
	cout << "str4.Length()  => " << str4.Length() << endl;
	PRINT_LINE;
	
	
	
	string strReal1("abc");
	string strReal2("123");
	string strReal3("777");
	
	(strReal1 = strReal2) = strReal3;
	
	
}


