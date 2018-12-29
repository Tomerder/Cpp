#include "text_file.h"

struct io_handler_base
{
	void process(DWORD error_code, DWORD bytes_transferred)
	{
		if (error_code != ERROR_SUCCESS)
		{
			throw std::runtime_error("error in file I/O operation");
		}
		process_success(bytes_transferred);
	}
	virtual void process_success(DWORD bytes_transferred) = 0;
};

template <typename T>
struct io_handler : io_handler_base
{
	concurrency::task_completion_event<T> tce_;

	concurrency::task<T> task()
	{
		return concurrency::task<T>{tce_};
	}
};

struct read_handler : io_handler<std::string>
{
	std::unique_ptr<char[]> buffer_;

	read_handler(size_t size) : buffer_(std::make_unique<char[]>(size))
	{
	}

	void process_success(DWORD bytes_transferred) override
	{
		tce_.set(std::string(buffer_.get(), bytes_transferred));
	}
};

struct write_handler : io_handler<DWORD>
{
	void process_success(DWORD bytes_transferred) override
	{
		tce_.set(bytes_transferred);
	}
};

struct simple_overlapped : OVERLAPPED
{
	std::unique_ptr<io_handler_base> handler_;

	simple_overlapped(std::unique_ptr<io_handler_base> handler) : handler_(std::move(handler))
	{
		this->hEvent = nullptr;
		this->Internal = 0;
		this->InternalHigh = 0;
		this->Offset = 0;
		this->OffsetHigh = 0;
		this->Pointer = 0;
	}
	void set_offset(size_t offset)
	{
		this->Offset = static_cast<DWORD>((offset & 0x00000000ffffffffull));
		this->OffsetHigh = static_cast<DWORD>((offset & 0xffffffff00000000ull) >> 32);
	}
};

text_file::text_file(std::wstring filename, filemode mode, fileshare share_mode, filedisposition disposition)
{
	file_ = CreateFile(filename.c_str(), static_cast<DWORD>(mode), static_cast<DWORD>(share_mode), nullptr, static_cast<DWORD>(disposition), FILE_FLAG_OVERLAPPED, nullptr);
	if (file_ == INVALID_HANDLE_VALUE)
	{
		throw std::runtime_error("error opening file");
	}
	BindIoCompletionCallback(file_, text_file::io_completion_callback, 0);
}

concurrency::task<std::string> text_file::read_async(unsigned count, size_t offset)
{
	auto handler = std::make_unique<read_handler>(count);
	auto buffer = handler->buffer_.get();
	auto task = handler->task();
	auto ovl = new simple_overlapped(std::move(handler));
	ovl->set_offset(offset);
	if (FALSE == ReadFile(file_, buffer, count, nullptr, ovl) &&
		GetLastError() != ERROR_IO_PENDING)
	{
		throw std::runtime_error("error reading from file");
	}
	return task;
}

concurrency::task<DWORD> text_file::write_async(std::string const& text, size_t offset)
{
	auto handler = std::make_unique<write_handler>();
	auto task = handler->task();
	auto ovl = new simple_overlapped(std::move(handler));
	ovl->set_offset(offset);
	if (FALSE == WriteFile(file_, text.c_str(), static_cast<DWORD>(text.size()), nullptr, ovl) &&
		GetLastError() != ERROR_IO_PENDING)
	{
		throw std::runtime_error("error writing to file");
	}
	return task;
}

text_file::text_file(text_file&& rhs) noexcept
{
	*this = std::move(rhs);
}

text_file& text_file::operator=(text_file&& rhs) noexcept
{
	std::swap(file_, rhs.file_);
	return *this;
}

text_file::~text_file() noexcept
{
	if (file_ != nullptr && file_ != INVALID_HANDLE_VALUE)
	{
		CloseHandle(file_);
	}
}

void __stdcall text_file::io_completion_callback(DWORD error_code, DWORD bytes_transferred, LPOVERLAPPED o)
{
	auto ovl = std::unique_ptr<simple_overlapped>(reinterpret_cast<simple_overlapped*>(o));
	ovl->handler_->process(error_code, bytes_transferred);
}