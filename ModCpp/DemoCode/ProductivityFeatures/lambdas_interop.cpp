#include "lambdas_interop.h"

#include <Windows.h>

#include <vector>
#include <iostream>

void enum_windows1()
{
	EnumWindows([](HWND hwnd, LPARAM) {
		std::cout << hwnd << std::endl;
		return TRUE;
	}, 0);
}

void enum_windows2()
{
	std::vector<HWND> windows;
	EnumWindows([](HWND hwnd, LPARAM lp)
		{
			auto pw = reinterpret_cast<std::vector<HWND>*>(lp);
			pw->push_back(hwnd);
			return TRUE;
		},
		reinterpret_cast<LPARAM>(&windows)
	);
}