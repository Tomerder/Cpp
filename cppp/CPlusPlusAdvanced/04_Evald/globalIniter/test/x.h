/***************************************************************************
	Author: Stav Ofer
	Creation date:  		2013-11-14
	Last modified date:		2013-11-14
	Description: 	global initializer test - header for test class
***************************************************************************/

#ifndef __X_H__
#define __X_H__


//=======================================================================//
// test class for global 
class X
{
public:	
	X() : m_data(0) {}
	// using generated DTOR, copy, assignment
	
	int GetData() const { return m_data; }
	void SetData(int _num) { m_data = _num; }
	
private:
	int m_data;
};
//=======================================================================//



#endif /* __X_H__ */
