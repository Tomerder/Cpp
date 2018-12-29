/***************************************************************************
	Author: Stav Ofer
	Creation date:  		2013-11-05    
	Last modified date:		2013-11-05
	Description: 	
****************************************************************************/

#ifndef __SHARED_PTR_H__
#define __SHARED_PTR_H__

template <class T>
class SharedPtr
{
public:
	
	// CTOR, DTOR
	~SharedPtr();
	explicit SharedPtr();
	SharedPtr(const SharedPtr* _shrdPtr);
	
	
	
	
private:
	T*	m_obj;
	unsigned int m_counter;
	
	void FreePtr();	// delete m_obj
};
//######################################################################//
//---------------------------------------------------------------------

#endif  /* __SHARED_PTR_H__ */
