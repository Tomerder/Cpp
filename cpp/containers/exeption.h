/**************************************************************************************
    Author : Tomer Dery
    Creation date :      5.1.13
    Date last modified : 5.1.13 - 5.1.13
    Description : exeption
***************************************************************************************/
#ifndef __EXEPTION_H__
#define __EXEPTION_H__

using namespace std;

template<class EXP_OBJ>

class TExeption_t{ 

private: 	
	EXP_OBJ m_obj;
	string m_dsc;
	const string m_fileName;
	const int m_lineNum;
			
public: 
	
	TExeption_t(const string& _fileName, int _lineNum) : m_fileName(_fileName) , m_lineNum(_lineNum) { }  		
	TExeption_t(const string& _fileName, int _lineNum, const EXP_OBJ& _obj) : m_fileName(_fileName) , m_lineNum(_lineNum) , m_obj(_obj) { }  	
	TExeption_t(const string& _fileName, int _lineNum ,const EXP_OBJ& _obj , const string& _dsc) 
						: m_fileName(_fileName) , m_lineNum(_lineNum) , m_obj(_obj) , m_dsc(_dsc) { }  	
	
	TExeption_t(const TExeption_t& _exp): m_fileName(_exp.m_fileName) , m_lineNum(_exp.m_lineNum) , m_obj(_exp.m_obj) , m_dsc(_exp.m_dsc) { } 
	
	TExeption_t& operator=(const TExeption_t& _exp)
	{
		if(this != &_exp ){
			m_obj = _exp.m_obj;
			m_dsc = _exp.m_dsc;
		}
		return *this;
	}
		
	virtual ~TExeption_t() {}	
	
	const string& getDsc() const {return m_dsc;}
	void setDsc(const string& _dsc) { m_dsc = _dsc; }
	
	const EXP_OBJ& getObj() const {return m_obj;}
	void setObj(const EXP_OBJ& _obj) { m_obj = _obj; }
	
	virtual void Print() const;
	
};

//example of implementation outside the class
template<class EXP_OBJ>
void TExeption_t<EXP_OBJ>::Print() const
{
		cout << "Exeption : " << "file : " << m_fileName << " , line : " << m_lineNum << " , dsc : " << m_dsc << " , val : " << m_obj  << endl; 
}




#endif /*__EXEPTION_H__*/


