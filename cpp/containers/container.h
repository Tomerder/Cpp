/**************************************************************************************
    Author : Tomer Dery
    Creation date :     6.1.13
    Date last modified : 6.1.13 
    Description : container
***************************************************************************************/
#ifndef __CONTAINER_H__
#define __CONTAINER_H__

using namespace std;

#include <fstream>

#include "exeption.h"

/*--------------------------------------------------------------------------------*/

template<class ITEM>
bool DefaultCompFunc(const ITEM& _item1 , const ITEM& _item2)
{
	return _item1 == _item2;
}

template<class ITEM>
void DefaultPrintFunc(const ITEM& _item)
{
	cout << _item;
}

/*--------------------------------------------------------------------------------*/

template<class ITEM>
class Container_t{ 

private: 	
	int m_numOfItems;
	
protected:
	void setNumOfItems(int _numOfItems) { m_numOfItems = _numOfItems; }
	
	void incNumOfItems() { m_numOfItems++; }
	void decNumOfItems() { m_numOfItems--; }

public: 	
	Container_t() :  m_numOfItems(0)  {}  	  			

	virtual ~Container_t() {}	
		
	int getNumOfItems() const { return m_numOfItems; }

	virtual bool GetFromFile(const string& _fileName);

	/*pure virtual methods*/
	virtual bool Append(int _index, const ITEM& _item)=0;
	virtual bool Prepend(int _index, const ITEM& _item)=0;
	virtual bool Insert(const ITEM& _item)=0;  //to end of container
	virtual ITEM Remove(int _index)=0;   //throws exeption
	virtual void RemoveAll()=0;
	
	typedef bool (*CompFunc)(const ITEM& _item1, const ITEM& _item2);	
	virtual bool Find(const ITEM& _itemToFind, ITEM* _foundItem , CompFunc _CompFunc = DefaultCompFunc ) =0;
	
	typedef void (*PrintFunc)(const ITEM& _item);
	virtual void Print(PrintFunc _PrintFunc = DefaultPrintFunc) const=0;

	virtual bool SaveToFile(const string& _fileName) const=0;
	
	typedef bool (*DoFunc) (ITEM, void*);
	virtual int	ForEach	(DoFunc _DoFunc, void* params)=0;

};

/*--------------------------------------------------------------------------------*/

template<class ITEM>
bool Container_t<ITEM>::GetFromFile(const string& _fileName) 
{
	ifstream file;
  	file.open (_fileName.c_str() );	
	if(!file.is_open()){
		return false;
	}
	
	ITEM* item = new ITEM;	
	
	while(true){
		file.read((char*)item , sizeof(ITEM));
		if( file.eof() ) break;
		Insert(*item);
	}
	
	delete item;
	file.close();

	return true;
}

/*--------------------------------------------------------------------------------*/

#endif /*__CONTAINER_H__*/


