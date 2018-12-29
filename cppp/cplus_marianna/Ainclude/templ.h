/**************************************************************************************
    Author: Marianna Shvartsman
    Creation date :      2013-12-15
    Last modified date: 2013-12-15 
    Description : Template + Dll
***************************************************************************************/
#ifndef __TEMPLATE_DLL_H__
#define __TEMPLATE_DLL_H__

#include <iostream>

template<class T>
class TestTemplateDll {
public:
	void Print() {std::cout << ++s_size << std::endl;}
private:
	static T s_size;
};

template <class T> T TestTemplateDll<T>::s_size = 15;

#endif //__TEMPLATE_DLL_H__