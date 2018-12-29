#pragma once
#pragma once

#include <ppltasks.h>

#include <string>

#include <Windows.h>

enum class filemode : DWORD
{
	read = GENERIC_READ,
	write = GENERIC_WRITE,
	readwrite = GENERIC_READ | GENERIC_WRITE
};

enum class fileshare : DWORD
{
	read = FILE_SHARE_READ,
	write = FILE_SHARE_WRITE,
	del = FILE_SHARE_DELETE,
	none = 0
};

enum class filedisposition : DWORD
{
	create = CREATE_ALWAYS,
	open = OPEN_EXISTING
};

class text_file
{
private:
	HANDLE file_ = nullptr;

public:
	text_file(std::wstring filename, filemode mode, fileshare share_mode, filedisposition disposition);
	concurrency::task<std::string> read_async(unsigned count, size_t offset);
	concurrency::task<DWORD> write_async(std::string const& text, size_t offset);

	text_file(text_file&& rhs) noexcept;
	text_file& operator=(text_file&& rhs) noexcept;

	text_file(text_file const&) = delete;
	text_file& operator=(text_file const&) = delete;

	~text_file() noexcept;

private:
	static void __stdcall text_file::io_completion_callback(DWORD error_code, DWORD bytes_transferred, LPOVERLAPPED o);
};