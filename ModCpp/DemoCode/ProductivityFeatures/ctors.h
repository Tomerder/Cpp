#pragma once

#include <string>

enum class filemode
{
	open,
	create
};

class file
{
private:
	void* h_;
public:
	file(char const* name, filemode fm);
	file(std::string name) : file(name.c_str(), filemode::open) 
	{
	}
	file() : file(get_temp_filename(), filemode::create)
	{
	}
	~file();
private:
	char const* get_temp_filename();
};