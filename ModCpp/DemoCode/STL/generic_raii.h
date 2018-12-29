#pragma once

#include <Windows.h>
#include <iostream>
#include <utility>

// RAII - Resource Acquisition Is Initialization
template <typename Resource, typename Deleter>
class raii
{
private:
	Resource resource_;
	Deleter deleter_;
	bool should_delete_ = true;

public:
	raii(Resource resource, Deleter deleter) : resource_{ std::move(resource) }, deleter_{ std::move(deleter) }
	{
	}
	operator Resource() const
	{
		return resource_;
	}
	~raii()
	{
		if (should_delete_)
		{
			deleter_(resource_);
		}
	}

	raii(raii&& rhs) noexcept(std::is_nothrow_move_constructible<Resource>::value && std::is_nothrow_move_constructible<Deleter>::value)
		: resource_{ std::move(rhs.resource_) }, deleter_{ std::move(rhs.deleter_) }
	{
		rhs.should_delete_ = false;
	}
	raii& operator=(raii&& rhs)
		noexcept(noexcept(std::swap(resource_, rhs.resource_) && noexcept(std::swap(deleter_, rhs.deleter_))))
	{
		std::swap(resource_, rhs.resource_);
		std::swap(deleter_, rhs.deleter_);
		return *this;
	}

	raii(raii const&) = delete;
	raii& operator=(raii const&) = delete;
};

template <typename Resource, typename Deleter>
auto make_raii(Resource&& resource, Deleter&& deleter)
{
	return raii<Resource, Deleter>{std::forward<Resource>(resource), std::forward<Deleter>(deleter)};
}

using file_handle = raii<HANDLE, decltype(&CloseHandle)>;

file_handle create_file(std::wstring const& file)
{
	return make_raii(CreateFile(file.c_str(), GENERIC_READ | GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, 0, nullptr), &CloseHandle);
}

void use_raii()
{
	auto fh = create_file(L"raii.txt");
	std::string hello{ "Hello, World" };
	DWORD written;
	WriteFile(fh, hello.c_str(), hello.size(), &written, nullptr);
}