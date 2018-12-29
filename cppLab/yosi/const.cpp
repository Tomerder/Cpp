#include <iostream>
#include <string.h>

using namespace std;


/*------------------------------------------------------------------------------------*/


class A
{
	private:
		string m_str;
	
	public:
		A(const string& _str) : m_str(_str) {}
		
		void SetStr(const string& _str) { cout << "const string&" << endl ;  m_str = _str; }
		void SetStr(string& _str) {  cout << "string&" << endl ;  m_str = _str;  m_str = _str; }
};

/*------------------------------------------------------------------------------------*/

void func(const string& _str)
{
	string str;
	str = _str; 
}

/*------------------------------------------------------------------------------------*/

int main() 
{
	const string str = "ttt";
	string str2 = "zzz";
	
	A a(str);
	
	a.SetStr("yyy");
	a.SetStr(str);
	a.SetStr(str2);
	
	func(str);
	func(str2);
	
	return 0;
}


/*------------------------------------------------------------------------------------*/





