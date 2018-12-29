#include <iostream>
#include <string.h>
#include <cctype>

#include "big.h"

using namespace std;

#define MAX(A,B) ((A) > (B)) ? (A) : (B) 
/*--------------------------------------------------------------------------------*/


BigNum::BigNum()       //ctor
{
	createNum("0");  
}


BigNum::~BigNum()    //dtor
{   		  	
	delete[](m_numStr);
	m_numStr = NULL;   
}


BigNum::BigNum(const char* _numStr)   //ctor
{
	createNum(_numStr);
}


BigNum::BigNum(int _num)    //ctor
{
	createNumFromInt(_num);
}



BigNum::BigNum(const BigNum& _bigNumToCpy)   //copy ctor
{
	createNum( _bigNumToCpy.m_numStr  );
}


/*--------------------------------------------------------------------------------*/




BigNum& BigNum::operator=(const BigNum& _bigNum)  //operator= 
{	
	if(&_bigNum != this){	
		delete[] m_numStr;	
		createNum(_bigNum.m_numStr);
	}
	
	return *this;
}


BigNum& BigNum::operator=(int _num)           //operator= 
{
	delete[] m_numStr;	
   
	createNumFromInt(_num);
	
	return *this;
}


/*--------------------------------------------------------------------------------*/


BigNum BigNum::operator+(const BigNum& _bigNum) const
{	
	int maxLen = MAX(m_len , _bigNum.m_len) + 1;
	char* str =  new char[maxLen]; 

	bigIntsSum( m_numStr, _bigNum.m_numStr, str);

	BigNum toRet(str);

	delete[] str;

	return toRet;   //return by value
}



/*--------------------------------------------------------------------------------*/

void BigNum::createNumFromInt(int _num)    //private method 
{
	int len = getNumLen(_num) + 1;
	char* str = new char[len];	
	
	itoa(_num, str);

	createNum(str);

	delete[] str;	
}




void BigNum::createNum(const char* _str)    //private method 
{	
	bool chk = checknumStr( _str);	
	
	if(chk){
		m_len = strlen(_str);
		m_numStr = new char[ m_len + 1]; 
		strcpy(m_numStr, _str);
	}else{
		m_len = 1;
		m_numStr = new char[2];
		m_numStr[0] = '0';
		m_numStr[1] = '\0';
	}
}


bool BigNum::checknumStr(const char* _str) const{
	int i=0;

	if(!_str){
		return false;
	}

	while(_str[i] != '\0'){
		if(! isdigit(_str[i]) ){
			return false;
		}
		i++;
	}

	return true;

}



/*--------------------------------------------------------------------------------*/


bool BigNum::operator==(const BigNum& _bigNum) const
{
	if ( m_len == _bigNum.m_len   &&  !strcmp(m_numStr, _bigNum.m_numStr)  ){
		return true;
	}else{
		return false;
	}
}


bool BigNum::operator<(const BigNum& _bigNum) const
{
	if ( m_len < _bigNum.m_len   ||  strcmp(m_numStr, _bigNum.m_numStr) < 0 ){
		return true;
	}else{
		return false;
	}
}


bool BigNum::operator>(const BigNum& _bigNum) const
{
	if ( m_len > _bigNum.m_len   ||  strcmp(m_numStr, _bigNum.m_numStr) > 0 ){
		return true;
	}else{
		return false;
	}

}

/*--------------------------------------------------------------------------------*/


char* BigNum::bigIntsSum(const char* num1 , const char* num2, char* res) const{   /*return value is to the same address as res parameter*/

	int len1,len2,min,max,first;
	int i=0;
	int sum;
	int plus=0;
	char c;

	len1 = strlen(num1);
	len2 = strlen(num2);
	
	min = (len1>len2)?(len2):(len1);
	max = (len1>len2)?(len1):(len2);

	
	while(i<max){
		if(i<min){  /*small number didnt end*/ 
			sum = (num1[len1-i-1]-'0') + (num2[len2-i-1]-'0') + plus; 
		}else{      /* small number ended */
			if(len1>len2)
				sum = (num1[len1-i-1]-'0')	+ plus;
			else if(len2>len1)	
				sum =(num2[len2-i-1]-'0') + plus; 		
		}
	
		if(sum>9){
			first = sum - 10;
			plus = 1;
		}else{
			first = sum;
			plus = 0;
		}
		
		c=first+'0';
		
		res[i]= c;
		i++;
	}

	res[i] = '\0';
	
	reverseStr(res);

	return res;	
}


char* BigNum::reverseStr(char* str) const{  /*return value is to the same address as str parameter*/
	int i=0;
	char c;	
	int len = strlen(str) - 1;

	while(i <= len/2){
		c=str[len-i];
		str[len-i] = str[i];
		str[i] = c;
		i++;
	}

	return str;
}

/*--------------------------------------------------------------------------------*/


void BigNum::Print() const
{
	cout << m_numStr;
}


/*--------------------------------------------------------------------------------*/

int BigNum::getNumLen (int _num) const{
	int len = 1;
  
	while(_num > 0){
		len++; 
		_num/=10; 
	}
	
	return len;
}

/*--------------------------------------------------------------------------------*/


void BigNum::itoa(int n, char* s) const
{
     int i, sign;
 
     if ((sign = n) < 0)  /* record sign */
         n = -n;          /* make n positive */
     i = 0;
     do {       /* generate digits in reverse order */
         s[i++] = n % 10 + '0';   /* get next digit */
     } while ((n /= 10) > 0);     /* delete it */
     if (sign < 0)
         s[i++] = '-';
     s[i] = '\0';
     reverseStr(s);
 }

/*--------------------------------------------------------------------------------*/




