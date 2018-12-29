/**************************************************************************************
    Author : Tomer Dery
    Creation date :      5.1.13
    Date last modified : 5.1.13 - 5.1.13
    Description : city
***************************************************************************************/
#ifndef __STREET_H__
#define __STREET_H__

#include <vector>
#include <algorithm>

#include "building.h"

using namespace std;


template<class ID, class ID_BLD>

class Street_t{ 

private: 	
	ID m_id;
	
	vector< Building_t<ID_BLD>*  > m_buildings; 
		
public: 
	
	Street_t()  {};  	
	Street_t(const ID& _id)  {m_id = _id;}	
	
	
	Street_t(const Street_t& _street) 
	{
		m_id = _street.m_id; 
		copy(_street.m_buildings.begin() , _street.m_buildings.end() , back_inserter(m_buildings) ) ;	
	}	
	
	Street_t& operator=(const Street_t& _street)
	{
		if(this != &_street ){
			m_id = _street.m_id;
			m_buildings.clear();
			copy(_street.m_buildings.begin() , _street.m_buildings.end() , back_inserter(m_buildings) ) ;
		}
		return *this;
	}
		
	virtual ~Street_t() {}	
	
	const ID& getId() const {return m_id;}
	void setId(const ID& _id) { m_id = _id; }
	
	void addBuilding2Street( Building_t<ID_BLD>* _bld)
	{
		m_buildings.push_back(_bld);
	}
		
	const Building_t<ID_BLD>* getBuilding (const ID_BLD& _bldId) 
	{
		 typename vector<  Building_t<ID_BLD>*  >::iterator it;
		 for (it = m_buildings.begin() ; it != m_buildings.end(); ++it){
		 	if( (*it)->getId() ==  _bldId){
		 		return *it;
		 	}
		 }
		 return NULL;	
	}
	

};


	
#endif /*__STREET_H__*/


