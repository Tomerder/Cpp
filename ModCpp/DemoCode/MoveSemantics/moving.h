#pragma once

#include "smart_ptr.h"

#include <iostream>
#include <vector>
#include <string>

smart_ptr<std::string> initialize()
{
	std::string* pstr = new std::string("Hello, world!");
	return smart_ptr<std::string>(pstr);	// move
}

void moving()
{
	smart_ptr<std::string> pstring{ initialize() };	// move
	std::cout << *pstring << std::endl;
}

// Large, expensive to copy
struct toolbarbutton
{
	toolbarbutton(std::string title)
	{
	}
};

// Even larger and more expensive to copy
struct toolbar : std::vector<toolbarbutton>
{
};

class window
{
private:
	toolbar toolbar_;
public:
	void set_toolbar(toolbar tb)
	{
		toolbar_ = std::move(tb);
	}
};

void using_toolbar()
{
	toolbar tb;
	tb.push_back(toolbarbutton{ "Add" });
	tb.push_back(toolbarbutton{ "Copy" });
	tb.push_back(toolbarbutton{ "Paste" });
	tb.push_back(toolbarbutton{ "Exit" });

	window main_window;
	main_window.set_toolbar(std::move(tb)); // force move, 'tb' is now in unusable state
}