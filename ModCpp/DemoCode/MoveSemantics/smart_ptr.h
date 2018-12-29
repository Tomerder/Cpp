#pragma once

template <typename T>
class smart_ptr
{
private:
	T* ptr_ = nullptr;
public:
	smart_ptr() = default;
	smart_ptr(T* ptr) : ptr_(ptr)
	{
	}

	smart_ptr(smart_ptr const&) = delete;
	smart_ptr& operator=(smart_ptr const&) = delete;

	smart_ptr(smart_ptr&& rhs)
	{
		*this = std::move(rhs);
	}
	smart_ptr& operator=(smart_ptr&& rhs)
	{
		std::swap(ptr_, rhs.ptr_);
		return *this;
	}

	T* operator->()
	{
		return ptr_;
	}
	T* operator->() const
	{
		return ptr_;
	}
	T& operator*()
	{
		return *ptr_;
	}
	T const& operator*() const
	{
		return *ptr_;
	}

	~smart_ptr()
	{
		delete ptr_;
	}
};