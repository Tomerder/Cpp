#pragma once

#include <memory>
#include <string>

class buffered_log
{
public:
	buffered_log(std::string filename, size_t buffer_size);
	void write(std::string message);
	void flush();
	~buffered_log();
	// destructor is default, but must not be inline so that it doesn't attempt to delete the incomplete 'impl' type

private:
	struct impl;
	std::unique_ptr<impl> pimpl_;
};

void use_buffered_log();