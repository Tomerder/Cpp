// RvalueRefsPerfImprovement.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <string.h>
#include <string>
#include <vector>
#include <iostream>
#include <Windows.h>

using namespace std;

class lame_string {
private:
	char* _chars;
	int _length;
public:
	lame_string(const char* str) : _chars(strdup(str)), _length(strlen(str)) { }
	~lame_string() {
		delete[] _chars;
	}
	lame_string(const lame_string& other) : _chars(strdup(other._chars)), _length(other._length) {
	}
	lame_string& operator=(const lame_string& other) {
		if (this == &other) return *this;
		delete[] _chars;
		_chars = strdup(other._chars);
		_length = other._length;
	}
	char operator[](int i) const {
		return _chars[i];
	}
	char& operator[](int i) {
		return _chars[i];
	}
	int length() const {
		return _length;
	}
};

class lame_string_improved {
private:
	char* _chars;
	int _length;
public:
	lame_string_improved(const char* str) : _chars(strdup(str)), _length(strlen(str)) { }
	~lame_string_improved() {
		delete[] _chars;
	}
	lame_string_improved(const lame_string_improved& other) : _chars(strdup(other._chars)), _length(other._length) {
	}
	lame_string_improved& operator=(const lame_string_improved& other) {
		if (this == &other) return *this;
		delete[] _chars;
		_chars = strdup(other._chars);
		_length = other._length;
	}
	lame_string_improved(lame_string_improved&& other) {
		*this = move(other);
	}
	lame_string_improved& operator=(lame_string_improved&& other) {
		_chars = other._chars;
		_length = other._length;
		other._chars = nullptr;
		other._length = 0;
		return *this;
	}
	char operator[](int i) const {
		return _chars[i];
	}
	char& operator[](int i) {
		return _chars[i];
	}
	int length() const {
		return _length;
	}
};

template <typename Function>
void time_call(Function fn, string description) {
	DWORD begin = GetTickCount();
	fn();
	cout << description << ": " << GetTickCount() - begin << " ms" << endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	time_call([]() {
		vector<lame_string> v;
		for (int i = 0; i < 10000000; ++i) {
			v.push_back("Hello, World");
		}
	}, "lame_string");
	time_call([]() {
		vector<lame_string_improved> v;
		for (int i = 0; i < 10000000; ++i) {
			v.push_back("Hello, World");
		}
	}, "lame_string_improved");

	return 0;
}

