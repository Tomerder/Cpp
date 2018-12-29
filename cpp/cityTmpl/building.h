/**************************************************************************************
    Author : Tomer Dery
    Creation date :      5.1.13
    Date last modified : 5.1.13 - 5.1.13
    Description : city
***************************************************************************************/
#ifndef __BUILDING_H__
#define __BUILDING_H__

using namespace std;

template<class ID>

class Building_t{ 

private: 	
	ID m_id;
		
public: 
	
	Building_t()  {};  	
	Building_t(const ID& _id)  {m_id = _id;};  	
	
	
	Building_t(const Building_t& _bld) { m_id = _bld.m_id; }	
	
	Building_t& operator=(const Building_t& _bld)
	{
		if(*this != _bld ){
			m_id = _bld.m_id;
		}
		return *this;
	}
		
	virtual ~Building_t() {}	
	
	const ID& getId() const {return m_id;}
	void setId(const ID& _id) { m_id = _id; }

};


	
#endif /*__BUILDING_H__*/


