#include <Windows.h>

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <regex>

#include <ppl.h>
#include <concurrent_vector.h>

using namespace std;
using namespace Concurrency;

int usage()
{
	cout << "Usage:   pgrep <file specifier> <regex to search>" << endl;
	cout << "Example: pgrep *.cpp ^(#include|#pragma)" << endl;
	return 1;
}

struct SearchResult
{
	wstring file;
	unsigned int line;
	wstring match;

	SearchResult(wstring f, unsigned int l, wstring m) : file(f), line(l), match(m) {}
};

void process_file(wstring file, wstring searchRegex, concurrent_vector<SearchResult>& results)
{
	wregex regexp(searchRegex);
	wifstream os(file.c_str());
	wstring line;
	unsigned int lineNumber = 0;
	while (getline(os, line))
	{
		if (regex_search(line, regexp))
		{
			results.push_back({ file, lineNumber, line });
		}
		++lineNumber;
	}
}

int wmain(int argc, wchar_t* argv[])
{
	if (argc != 3)
	{
		return usage();
	}

	const wchar_t* fileSpecifier = argv[1];
	const wchar_t* searchRegex = argv[2];

	WIN32_FIND_DATA findData = { 0 };
	HANDLE hFindFile;
	hFindFile = FindFirstFile(fileSpecifier, &findData);
	if (hFindFile == INVALID_HANDLE_VALUE)
	{
		cout << "No files matching the given specifier or an error occurred" << endl;
		return 2;
	}

	vector<wstring> matchingFiles;
	do
	{
		if ((findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0)
			continue;
		matchingFiles.push_back(findData.cFileName);
	} while (FindNextFile(hFindFile, &findData));
	FindClose(hFindFile);

	concurrent_vector<SearchResult> results;
	parallel_for_each(begin(matchingFiles), end(matchingFiles), [&](std::wstring file) {
		process_file(file, searchRegex, results);
	});

	parallel_sort(begin(results), end(results), [](const SearchResult& a, const SearchResult& b) {
		if (a.file == b.file)
			return a.line < b.line;
		return a.file < b.file;
	});

	for (const auto& result : results)
	{
		wcout << "[" << result.file << ":" << result.line << "] " << result.match << endl;
	}
	cout << "Total results found: " << results.size() << endl;

	return 0;
}

