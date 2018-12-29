#include "pimpl.h"

#include <Windows.h>
#include <vector>

struct buffered_log::impl
{
	std::string filename_;
	HANDLE file_;
	std::vector<std::string> buffer_;
	size_t buffer_size_;

	impl(std::string filename, size_t buffer_size) : filename_(std::move(filename)), buffer_size_(buffer_size)
	{
		file_ = CreateFileA(filename_.c_str(), GENERIC_READ | GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, 0, nullptr);
	}

	void write(std::string message)
	{
		buffer_.push_back(std::move(message));
		if (buffer_.size() >= buffer_size_)
		{
			flush();
		}
	}

	void flush()
	{
		for (auto const& message : buffer_)
		{
			DWORD written;
			WriteFile(file_, message.c_str(), message.size(), &written, nullptr);
		}
		buffer_.clear();
	}

	~impl()
	{
		CloseHandle(file_);
	}
};

buffered_log::buffered_log(std::string filename, size_t buffer_size)
	: pimpl_{ std::make_unique<impl>(std::move(filename), buffer_size) }
{
}

void buffered_log::write(std::string message)
{
	pimpl_->write(std::move(message));
}

void buffered_log::flush()
{
	pimpl_->flush();
}

buffered_log::~buffered_log() = default;

void use_buffered_log()
{
	buffered_log log{ "log.txt", 3 };
	log.write("Message 1");
	log.write("Message 2");
	log.write("Message 3");
}