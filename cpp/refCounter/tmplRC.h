/**************************************************************************************
    Author : Tomer Dery
    Creation date :      21.1.13
    Date last modified : 21.1.13
    Description : reference counter
***************************************************************************************/
#ifndef __TMPL_RC_H__
#define __TMPL_RC_H__

using namespace std;

/*-----------------------------------------------------------------------------------------------*/

template<class T>

class TmplRC{ 

private: 	
	T* m_data;
	size_t m_refCount;
	
	/*will never be used*/
	TmplRC(const TmplRC& _tmplRc);
	TmplRC& operator=(const TmplRC& _tmplRc);
			
public: 	
	TmplRC();
	TmplRC(const T& _data);
		
	virtual ~TmplRC();
	
	void IncCount() { ++m_refCount; }
	void DecCount();
	
	const T& GetData() const { return *m_data; }
	size_t GetRefCount() const { return m_refCount; }
	
};

/*-----------------------------------------------------------------------------------------------*/

template<class T>
TmplRC<T>::~TmplRC() 
{
	delete m_data; 
	m_data = 0; 
} 

/*-----------------------------------------------------------------------------------------------*/

template<class T>
TmplRC<T>::TmplRC() 
{
	m_data = new T;
	m_refCount = 1;
}


template<class T>
TmplRC<T>::TmplRC(const T& _data)
{
	m_data = new T(_data);
	m_refCount = 1;	
}

/*-----------------------------------------------------------------------------------------------*/

template<class T>
void TmplRC<T>::DecCount()
{	
	if(m_refCount == 1){
		TmplRC<T>::~TmplRC();
		delete this;	/*Suicide*/
	}else{
		--m_refCount;
	}
}

/*-----------------------------------------------------------------------------------------------*/

#endif /*__TMPL_RC_H__*/


