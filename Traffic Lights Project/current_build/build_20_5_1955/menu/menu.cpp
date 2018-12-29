// menu.cpp
//
//	What's this?
//	Author: Vladimir Krapp
//	Created on:
//	Last modified:

#include "menu.h"



#include <iostream>
#include <string>
#include <utility>
#include <algorithm>

#include "menu.h"

using namespace std;
//
//Menu_t::Menu_t(){;}
//
//Menu_t::Menu_t(string _optList[], size_t _len)
//{
//	for(size_t i = 0; i < _len; ++i)
//	{
//		 m_options.push_back(make_pair(i+1, _optList[i] ));
//	}
//}
//		
//Menu_t::Menu_t(vector<string> _optList)
//{
//	for(size_t i = 0; i < _optList.size(); ++i)
//	{
//		 m_options.push_back(make_pair(i+1, _optList[i]));
//	}
//}
//
//void Menu_t::AddOption(Option _opt)
//{
//	m_options.push_back(_opt);
//}
//	
//void Menu_t::PrintOptions()
//{
//	for_each(m_options.begin(), m_options.end(), PrintOption());
//}
//
//int Menu_t::PresentOption()
//{
//	int chosenOpt = -1;
//	PrintOption();
//	cout << "Please make selection:" << endl;
//	cin >> chosenOpt;	
//	while (chosenOpt < 0 || chosenOpt > int(m_options.size()))
//	{
//		cout << "Invalid option, choose again, 0 to quit." << endl;
//		cin >> chosenOpt;
//	}
//
//	return chosenOpt;
//}
//
//
//
//
