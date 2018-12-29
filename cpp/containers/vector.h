/**************************************************************************************
    Author : Tomer Dery
    Creation date :      6.1.13
    Date last modified : 6.1.13
    Description : container
***************************************************************************************/
#ifndef __VECTOR_H__
#define __VECTOR_H__

#include "container.h"

using namespace std;

#define INIT_SIZE 10
#define MIN_INIT_SIZE 1

#define INIT_BLOCK_SIZE 10

/*--------------------------------------------------------------------------------*/

template<class ITEM>
class Vector_t : public Container_t<ITEM> { 

private: 	
	ITEM* m_items;
	
	int m_capacity;
	
	static int m_initSize;
	static int m_blockSize;
	
	/*private methods*/
	void copyVector(const Vector_t& _vec);	
	
	void incCapacity();
	void shiftR(int _index);
	void shiftL(int _index);
public: 	
	Vector_t();
	Vector_t(int _capacity); 
	
	Vector_t(const Vector_t& _vec);
	Vector_t& operator=(const Vector_t& _vec);
	
	virtual ~Vector_t(); 
	/*-------------------------------------------------*/
	/* static data members get\set */	
	static int getInitSize() { return m_initSize; }
	static void setInitSize(int _initSize) { m_initSize = _initSize; }
	
	static int getBlockSize() { return m_blockSize; }
	static void setBlockSize(int _blockSize) { m_blockSize = _blockSize; }	
	/*-------------------------------------------------*/	
	/* pure virtual methods implementation */	
	virtual bool Append(int _index, const ITEM& _item);
	virtual bool Prepend(int _index, const ITEM& _item);
	virtual bool Insert(const ITEM& _item);  //to end of container
	virtual ITEM Remove(int _index);
	virtual void RemoveAll();
	
	virtual bool Find(const ITEM& _itemToFind, ITEM* _foundItem, typename Container_t<ITEM>::CompFunc _CompFunc = DefaultCompFunc ) ;
	
	virtual void Print(typename Container_t<ITEM>::PrintFunc _PrintFunc = DefaultPrintFunc) const;

	virtual bool SaveToFile(const string&  _fileName) const ;

	virtual int	ForEach	(typename Container_t<ITEM>::DoFunc _DoFunc, void* _params); 
	/*-------------------------------------------------*/
};

/*--------------------------------------------------------------------------------*/
/*static data members initialization*/
template<class ITEM>
int Vector_t<ITEM>::m_initSize = INIT_SIZE;

template<class ITEM>
int Vector_t<ITEM>::m_blockSize = INIT_BLOCK_SIZE;

/*--------------------------------------------------------------------------------*/

template<class ITEM>
Vector_t<ITEM>::Vector_t() 
{
	m_capacity = m_initSize;
	m_items = new ITEM[ m_capacity ];
}  		

/*--------------------------------------------------------------------------------*/

template<class ITEM>
Vector_t<ITEM>::Vector_t(int _capacity) 
{
	if(_capacity >= MIN_INIT_SIZE){
		m_capacity = _capacity;
	}else{
		m_capacity = MIN_INIT_SIZE;
	}
	
	m_items = new ITEM[m_capacity];
}  	

/*--------------------------------------------------------------------------------*/

template<class ITEM>
Vector_t<ITEM>::Vector_t(const Vector_t& _vec)  
{  	
	copyVector(_vec);
} 

/*--------------------------------------------------------------------------------*/

template<class ITEM>
Vector_t<ITEM>& Vector_t<ITEM>::operator=(const Vector_t& _vec)
{
	if(this != &_vec ){
		delete[] m_items;
		copyVector(_vec);
	}
	return *this;
}

/*--------------------------------------------------------------------------------*/

template<class ITEM>
Vector_t<ITEM>::~Vector_t() 
{ 
	delete[] m_items;
	m_items = 0;
}	

/*--------------------------------------------------------------------------------*/

template<class ITEM>
bool Vector_t<ITEM>::Append(int _index, const ITEM& _item)
{
	int numOfItems = this->getNumOfItems();
	
	if(_index >= numOfItems || _index < 0 ){
		return false;
	}
	
	if(m_capacity < numOfItems + 1 ){
		incCapacity();
	}
	
	shiftR(_index+1);
	
	m_items[_index+1] = _item;
	this->incNumOfItems();
	
	return true;	
}

/*--------------------------------------------------------------------------------*/

template<class ITEM>
bool Vector_t<ITEM>::Prepend(int _index, const ITEM& _item)
{
	int numOfItems = this->getNumOfItems();
	
	if(_index > numOfItems || _index < 0){
		return false;
	}
	
	if(m_capacity < numOfItems + 1 ){
		incCapacity();
	}
	
	shiftR(_index);
	
	m_items[_index] = _item;
	this->incNumOfItems();
	
	return true;	
}

/*--------------------------------------------------------------------------------*/

template<class ITEM>
bool Vector_t<ITEM>::Insert(const ITEM& _item)  //to end of container
{
	int numOfItems = this->getNumOfItems();
	
	if(m_capacity < numOfItems + 1 ){
		incCapacity();
	}
	
	m_items[numOfItems] = _item;
	this->incNumOfItems();
	
	return true;
}

/*--------------------------------------------------------------------------------*/

template<class ITEM>	
ITEM Vector_t<ITEM>::Remove(int _index)
{
	int numOfItems = this->getNumOfItems();
	
	if(_index >= numOfItems || _index < 0){
		throw TExeption_t<int>(__FILE__, __LINE__, _index , "index error!!!");    //throw exeption    //throw exeption
	}
	
	ITEM item = m_items[_index];
	shiftL(_index);
	this->decNumOfItems();
	
	return item;
}

/*--------------------------------------------------------------------------------*/

template<class ITEM>		
void Vector_t<ITEM>::RemoveAll()
{
	delete[] m_items;
	this->setNumOfItems(0);
	
	m_capacity = m_initSize;
	m_items = new ITEM[m_capacity];	
}

/*--------------------------------------------------------------------------------*/

template<class ITEM>
bool Vector_t<ITEM>::Find(const ITEM& _itemToFind, ITEM* _foundItem , typename Container_t<ITEM>::CompFunc _CompFunc) 
{
	int numOfItems = this->getNumOfItems();
	for(int i = 0 ; i < numOfItems ; i++){
		if( _CompFunc( m_items[i] , _itemToFind) ){
			*_foundItem = m_items[i];
			return true;
		}
	}

	return false;
}

/*--------------------------------------------------------------------------------*/

template<class ITEM>
void Vector_t<ITEM>::Print(typename Container_t<ITEM>::PrintFunc _PrintFunc) const
{
	int numOfItems = this->getNumOfItems();
	for(int i = 0 ; i < numOfItems ; i++){
		_PrintFunc(m_items[i]);
		cout << " , ";	
	}
	cout << endl;
}

/*--------------------------------------------------------------------------------*/

template<class ITEM>
void Vector_t<ITEM>::incCapacity() 
{
	int itemsNum = this->getNumOfItems();
	ITEM* itemsArr = new ITEM[itemsNum];
	
	//saves data
	for(int i=0; i < itemsNum ; i++ ){ 
		itemsArr[i] = m_items[i];
	} 
	
	delete[] m_items;
	
	//enlarge
	int newCapacity = m_capacity + getBlockSize();
	m_items = new ITEM[newCapacity];
	m_capacity = newCapacity;
	
	//restore data
	for(int i=0; i < itemsNum ; i++ ){
		m_items[i] = itemsArr[i]; 
	}

	delete[] itemsArr;
}

/*--------------------------------------------------------------------------------*/

template<class ITEM>
void Vector_t<ITEM>::shiftR(int _index) 
{
	int numOfItems = this->getNumOfItems();
	for(int i=numOfItems ; i > _index  ; i--){
		m_items[i] = m_items[i-1];
	}
}

template<class ITEM>
void Vector_t<ITEM>::shiftL(int _index) 
{
	int numOfItems = this->getNumOfItems();
	for(int i=_index; i <  numOfItems - 1; i++){
		m_items[i] = m_items[i+1];
	}
}

/*--------------------------------------------------------------------------------*/

template<class ITEM>
void Vector_t<ITEM>::copyVector(const Vector_t& _vec)
{
	this->m_numOfItems = _vec.getNumOfItems();	
	m_capacity = _vec.m_capacity;
	
	int numOfItems = this->getNumOfItems();
	m_items = new ITEM[m_capacity];

	for(int i=0; i < numOfItems ; i++){
		m_items[i] = _vec.m_items[i];
	}
}

/*--------------------------------------------------------------------------------*/

template<class ITEM>
int Vector_t<ITEM>::ForEach(typename Container_t<ITEM>::DoFunc _DoFunc, void* _params)
{
	int good=0;
	int numOfItems = this->getNumOfItems();
	
	for(int i = 0 ; i < numOfItems ; i++){
		if(_DoFunc(m_items[i] ,_params)){
			good++;		
		}
	}
	return good;
}

/*--------------------------------------------------------------------------------*/

template<class ITEM>
bool Vector_t<ITEM>::SaveToFile(const string&  _fileName) const 
{
	ofstream file;
  	file.open (_fileName.c_str() );	
	if(!file.is_open()){
		return false;
	}
	
	int numOfItems = this->getNumOfItems();
	file.write((char*)(m_items), sizeof(ITEM) * numOfItems);

	file.close();

	return true;
}

/*--------------------------------------------------------------------------------*/

#endif /*__LIST_H__*/


