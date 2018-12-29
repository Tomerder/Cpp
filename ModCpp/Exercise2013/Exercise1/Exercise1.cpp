#include <iostream>
#include <iterator>
#include <fstream>
#include <sstream>
#include <map>
#include <functional>
#include <string>
#include <vector>
#include <algorithm>

void read_all_words(std::string const& filename, std::vector<std::string>& words)
{
	std::ifstream input(filename.c_str());
	// TODO 1
	//	Replace the whole loop that reads strings from the file with a std::copy
	//	call that uses std::istream_iterator and std::back_inserter. It should be 
	//	a single line of code, and you should be able to throw away the loop that
	//	tokenizes each line read from the file.
	std::string line;

	std::istringstream iss(line);

	while (std::getline(input, line))
	{
		// Tokenize the string by splitting it on ' ' (space) characters.
		size_t start = 0, end = 0;
		while (true)
		{
			end = line.find(' ', start);
			if (end == std::string::npos)
				break;
			words.push_back(line.substr(start, end-start));
			start = end + 1;
		}
	}
}

std::pair<std::map<std::string, size_t>, std::vector<std::string>> get_frequencies(std::vector<std::string> const& words)
{
	std::map<std::string, size_t> freqs;
	// TODO 2
	//	Use 'auto' and range-based 'for' to simplify the loops below.
	//for (std::vector<std::string>::const_iterator it = words.begin(); it != words.end(); ++it)
	for (auto const& it : words)
	{
		if (freqs.count(it) == 0)
		{
			freqs[it] = 1;
		}
		else
		{
			++freqs[it];
		}
	}

	std::multimap<size_t, std::string, std::greater<size_t>> reverse_freqs;
	//for (std::map<std::string, size_t>::const_iterator it = freqs.begin(); it != freqs.end(); ++it)
	for (auto const& it : freqs)
	{
		//reverse_freqs.insert(std::make_pair(it->second, it->first));
		reverse_freqs.insert(std::make_pair(it.second, it.first));
	}
	std::vector<std::string> ten_highest;
	int i = 0;
	//for (std::multimap<size_t, std::string, std::greater<size_t>>::const_iterator it = reverse_freqs.begin(); it != reverse_freqs.end(); ++it)
	for (auto const& it : reverse_freqs)
	{
		if (i++ >= 10) break;
		ten_highest.push_back(it.second);
	}
	return std::make_pair(freqs, ten_highest);
}

int main(int argc, char* argv[])
{


	if (argc < 2)
	{
		std::cerr << "Missing file name" << std::endl;
		return 1;
	}

	std::vector<std::string> words;
	read_all_words(argv[1], words);

	// TODO 3
	//	Simplify and shorten the code below as much as possible.

	auto frequencies = get_frequencies(words);
	std::cout << "Ten most frequent words: " << std::endl;

	//for (std::vector<std::string>::const_iterator it = frequencies.second.begin(); it != frequencies.second.end(); ++it)
	for (auto const& it : frequencies.second)
	{
		std::cout << "\t" << it << std::endl;
	}

	std::cout << "All word frequencies: " << std::endl;
	//for (std::map<std::string, size_t>::const_iterator it = frequencies.first.begin(); it != frequencies.first.end(); ++it)
	for (auto const& it : frequencies.first)
	{
		std::cout << "\t" << it.first << " occurred " << it.second << " times" << std::endl;
	}

	return 0;
}