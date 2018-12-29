#include "ctors.h"

#include <Windows.h>

file::file(char const* name, filemode fm)
{
	DWORD disposition = fm == filemode::create ? CREATE_ALWAYS : OPEN_EXISTING;
	h_ = CreateFileA(name, GENERIC_READ | GENERIC_WRITE, 0, nullptr, disposition, 0, nullptr);
}

file::~file()
{
	CloseHandle(h_);
}

char const* file::get_temp_filename()
{
	return "temp_file.tmp";
}
