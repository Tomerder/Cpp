/**************************************************************************************
    Author : Tomer Dery
    Creation date :      29.12.13
    Date last modified : 29.12.13
    Description : bignum.h 
***************************************************************************************/
#ifndef __BIG_NUM_H__
#define __BIG_NUM_H__


class BigNum{

private: 
	char* m_numStr;
	int m_len;	
	
	/*creates m_numStr from parameter and sets m_len  */
	void createNum(const char* _num);
	
	/*creates m_numStr from int parameter and sets m_len  */	
	void createNumFromInt(int _num);

	/*returns true if _str is valid number*/
	bool checknumStr(const char* _str) const;

	/*adds num1 + num2 to res and returns res*/
	char* bigIntsSum(const char* num1 ,const char* num2, char* res) const;

	/*returns str reversed*/
	char* reverseStr(char* str) const;

	/*returns the number of digits of int*/
	int getNumLen (int _num) const;

	/*converts num to string*/
	void itoa(int num, char* str) const;
public: 
	BigNum();
	~BigNum();
	
	BigNum(const char* _numStr);
	BigNum(int _num);
		
	BigNum(const BigNum& _bigNumToCpy);
	
	BigNum& operator=(const BigNum& _bigNum);
	BigNum& operator=(int _num);

	BigNum operator+(const BigNum& _bigNum) const;
	
	bool operator==(const BigNum& _bigNum) const;
	bool operator<(const BigNum& _bigNum) const;
	bool operator>(const BigNum& _bigNum) const;
	
	void Print() const;
	
};


	
#endif /* __BIG_NUM_H__*/


