/***************************************************************************
    Author: Stav Ofer
    Creation date:  		2013-00-00    
    Last modified date:		2013-00-00
    Description: 	
****************************************************************************/

#ifndef __XXX_H__
#define __XXX_H__

template <typename T>
class Xxx_t
{
public:
	
	// CTOR, DTOR
	Xxx_t();
	Xxx_t(T _x);
	~Xxx_t() = 0;
	
	// copy, assignment
	Xxx_t<T> 				(const Xxx_t<T>& _x);
	Xxx_t<T>& operator =	(const Xxx_t<T>& _x);
	
	
protected:
	
	
private:
	
	
};
/*######################################################################*/

// def. CTOR
template <class T>
Xxx_t<T>::	Xxx_t()
{
	//
}
/*-------------------------------------------------------------*/





#endif  /* __XXX_H__ */
