// menu.h
//
//	What's this?
//	Author: Vladimir Krapp
//	Created on:
//	Last modified:

#ifndef __MENU_H__
#define __MENU_H__


#include <iostream>
#include <utility>
#include <string>
#include <vector>
#include <algorithm>


template <class T>
class Menu_t
{


	public:
		Menu_t();
		Menu_t(T _optList[], size_t _len);		
		Menu_t(std::vector<T> _optList);
		void AddOption(T _opt);
		void PrintOptions(int);
		int PresentMenu(int);
		

	private:
		std::vector<T> m_options;

		struct PrintOption
		{
            PrintOption(int _i = 1){m_counter = _i;}
            size_t m_counter;
			void operator()(T _opt)
			{ std::cout << m_counter++ << '\t' << _opt << std::endl;	}
		};

};

template<class T>
Menu_t<T>::Menu_t(){;}

template<class T>
Menu_t<T>::Menu_t(T _optList[], size_t _len)
{
	for(size_t i = 0; i < _len; ++i)
	{
		 m_options.push_back(_optList[i]);
	}
}
		
template<class T>
Menu_t<T>::Menu_t(std::vector<T> _optList)
{
	for(size_t i = 0; i < _optList.size(); ++i)
	{
		 m_options.push_back(_optList[i]);
	}
}

template<class T>
void Menu_t<T>::AddOption(T _opt)
{
	m_options.push_back(_opt);
}

template<class T>
void Menu_t<T>::PrintOptions(int _numberStart = 1)
{
	for_each(m_options.begin(), m_options.end(), PrintOption(_numberStart));
}

template <class T>
int Menu_t<T>::PresentMenu(int _numberStart = 1)
{
	int chosenOpt = -1;

    PrintOptions(_numberStart);

    std::cout << "Please make selection:" << std::endl;
    std::cin >> chosenOpt;	
	while (chosenOpt < 0 || chosenOpt > int(m_options.size()))
	{
        std::cout << "Invalid option, choose again, 0 to quit." << std::endl;
        std::cin >> chosenOpt;
	}

	return chosenOpt;

}



#endif //__MENU_H__
