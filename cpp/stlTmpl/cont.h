/**************************************************************************************
    Author : Tomer Dery
    Creation date :      15.1.14
    Date last modified : 15.1.14 - 15.1.14
    Description : template container - STL 
***************************************************************************************/
#ifndef __CONTAINER_H__
#define __CONTAINER_H__

#include <vector>
#include <list>
#include <algorithm>
#include <typeinfo>

using namespace std;

#define _TYPE2_ 1

#if _TYPE2_
	template <class T , class CONT >
#else
	template <typename T , template<typename T2, typename ALC = std::allocator<T2> > class CONT >
#endif

class TContainer_t{ 

private: 
	#if _TYPE2_	
		CONT m_container;
		typedef typename CONT::iterator	iter_t;
	#else
		CONT<T*> m_container;
		typedef typename CONT<T*>::iterator	iter_t;
	#endif
	
	/*private methods*/
	iter_t FindImp(T _valToFind);
	
	/*copy not allowed*/
	TContainer_t(const TContainer_t& _cont);  	
	TContainer_t& operator=(const TContainer_t& _cont);

public: 		
	TContainer_t()  {} 
	~TContainer_t() {}	
	
	T* operator[](size_t _index);
	
	bool IsEmpty() const;
	int GetNumOfElements() const;
	
	void Insert( T* _toInsert);  /*insert to the end*/
	T* Remove(T _toRemove) ; 
	void RemoveAll() ; 
	void RemoveAndDelete(T _toRmvDlt) ; 
	void RemoveAndDeleteAll() ; 
	 
	T* Find(T _toFind) ; 
	 
	T* GetFirst() ; 
	T* GetLast() ; 
	
};

/*-------------------------------------------------------------------------------------*/
#if _TYPE2_
template <class T , class CONT >
#else
template <typename T , template<typename T2, typename ALC = std::allocator<T2> > class CONT >
#endif
bool TContainer_t< T , CONT >::IsEmpty() const
{
	return m_container.empty();
}
/*-------------------------------------------------------------------------------------*/
#if _TYPE2_
template <class T , class CONT >
#else
template <typename T , template<typename T2, typename ALC = std::allocator<T2> > class CONT >
#endif
int TContainer_t< T , CONT >::GetNumOfElements() const
{
	return m_container.size();
}

/*-------------------------------------------------------------------------------------*/
#if _TYPE2_
template <class T , class CONT >
#else
template <typename T , template<typename T2, typename ALC = std::allocator<T2> > class CONT >
#endif
void TContainer_t< T , CONT >::Insert( T* _toInsert)
{
	/*m_container.insert(m_container.end() , &_toInsert) ;*/
	m_container.push_back(_toInsert) ;
}
/*-------------------------------------------------------------------------------------*/
#if _TYPE2_
template <class T , class CONT >
#else
template <typename T , template<typename T2, typename ALC = std::allocator<T2> > class CONT >
#endif
T* TContainer_t< T , CONT >::GetFirst() 
{
	return *(m_container.begin());
} 
/*-------------------------------------------------------------------------------------*/
#if _TYPE2_
template <class T , class CONT >
#else
template <typename T , template<typename T2, typename ALC = std::allocator<T2> > class CONT >
#endif
T* TContainer_t< T , CONT >::GetLast() 
{
	return *(--m_container.end());
} 
/*-------------------------------------------------------------------------------------*/
/*FindImp*/
template <typename T>
struct eq{
    eq(const T compare_to_val) : compare_to_val(compare_to_val) { }
    bool operator()(T* _ptrT) const {return  *_ptrT == compare_to_val ;}  
private:
    const T compare_to_val;
};

#if _TYPE2_
template <class T , class CONT >
#else
template <typename T , template<typename T2, typename ALC = std::allocator<T2> > class CONT >
#endif
typename TContainer_t< T , CONT >::iter_t    TContainer_t< T , CONT >::FindImp(T _valToFind)
{
	iter_t itr;
	itr =  find_if (m_container.begin(), m_container.end(), eq<T>(_valToFind) );
	return itr;
}

/*-------------------------------------------------------------------------------------*/
/*Remove*/
#if _TYPE2_
template <class T , class CONT >
#else
template <typename T , template<typename T2, typename ALC = std::allocator<T2> > class CONT >
#endif
T* TContainer_t< T , CONT >::Remove(T _toRemove) 
{
	iter_t itr;
	T* toReturn = NULL;
	
	itr =  FindImp(_toRemove);
	if( itr != m_container.end() ){
		toReturn = *itr;
		m_container.erase(itr);
	}
	
	return toReturn;
}
/*-------------------------------------------------------------------------------------*/
/*Find*/
#if _TYPE2_
template <class T , class CONT >
#else
template <typename T , template<typename T2, typename ALC = std::allocator<T2> > class CONT >
#endif
T* TContainer_t< T , CONT >::Find(T _toFind) 
{
	iter_t itr;
	T* toReturn = NULL;
	
	itr =  FindImp(_toFind);
	if( itr != m_container.end() ){
		toReturn = *itr;
	}
	
	return toReturn;
}
/*-------------------------------------------------------------------------------------*/
/*RemoveAll*/
#if _TYPE2_
template <class T , class CONT >
#else
template <typename T , template<typename T2, typename ALC = std::allocator<T2> > class CONT >
#endif
void TContainer_t< T , CONT >::RemoveAll() 
{
	m_container.clear();
} 	
/*-------------------------------------------------------------------------------------*/	
/*RemoveAndDelete*/
#if _TYPE2_
template <class T , class CONT >
#else
template <typename T , template<typename T2, typename ALC = std::allocator<T2> > class CONT >
#endif
void TContainer_t< T , CONT >::RemoveAndDelete(T _toRmvDlt) 
{
	iter_t itr;
	T* toDel = NULL;
	
	itr =  FindImp(_toRmvDlt);
	if( itr != m_container.end() ){
		toDel = *itr;
		m_container.erase(itr);
		delete(toDel);
	}
	
}
/*-------------------------------------------------------------------------------------*/
/*RemoveAndDeleteAll*/
template <typename T>
void DelFunc (T _toDel) 
{ 
	delete(_toDel);	
}

#if _TYPE2_
template <class T , class CONT >
#else
template <typename T , template<typename T2, typename ALC = std::allocator<T2> > class CONT >
#endif
void TContainer_t< T , CONT >::RemoveAndDeleteAll() 
{
	for_each(m_container.begin() , m_container.end() , DelFunc<T*> );
	m_container.clear();
}
/*-------------------------------------------------------------------------------------*/
/*  operator[]  */
#if _TYPE2_
template <class T , class CONT >
#else
template <typename T , template<typename T2, typename ALC = std::allocator<T2> > class CONT >
#endif
T* TContainer_t< T , CONT >::operator[](size_t _index)
{
	/*
	if(typeid(m_container) == typeid(vector<T*>) ){
		return m_container[_index];
	}else{
	
	}*/
	
   iter_t itr = m_container.begin();
   advance(itr, _index);
   return *itr;
}

/*-------------------------------------------------------------------------------------*/	
#endif /*__CONTAINER_H__*/





























