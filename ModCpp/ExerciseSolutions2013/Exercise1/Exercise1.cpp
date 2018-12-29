#include <iostream>
#include <iterator>
#include <fstream>
#include <map>
#include <functional>
#include <string>
#include <vector>
#include <algorithm>

void read_all_words(
	std::string const& filename,
	std::vector<std::string>& words)
{
	std::ifstream input(filename.c_str());
	std::copy(
		std::istream_iterator<std::string>(input),
		std::istream_iterator<std::string>(),
		std::back_inserter(words)
		);
}

std::pair<
	std::map<std::string, size_t>,
	std::vector<std::string>
> get_frequencies(std::vector<std::string> const& words)
{
	std::map<std::string, size_t> freqs;
	for (auto const& word : words)
	{
		if (freqs.count(word) == 0)
		{
			freqs[word] = 1;
		}
		else
		{
			++freqs[word];
		}
	}
	std::multimap<size_t, std::string, std::greater<size_t>> reverse_freqs;
	for (auto const& pair : freqs)
	{
		reverse_freqs.insert(std::make_pair(
			pair.second, pair.first));
	}
	std::vector<std::string> ten_highest;
	int i = 0;
	for (auto const& freq_and_word : reverse_freqs)
	{
		if (i++ >= 10) break;
		ten_highest.push_back(freq_and_word.second);
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

	auto frequencies = get_frequencies(words);
	std::cout << "Ten most frequent words: " << std::endl;
	for (auto const& word : frequencies.second)
	{
		std::cout << "\t" << word << std::endl;
	}
	std::cout << "All word frequencies: " << std::endl;
	for (auto const& word_and_freq : frequencies.first)
	{
		std::cout << "\t" << word_and_freq.first << " occurred "
				  << word_and_freq.second << " times"
				  << std::endl;
	}

	return 0;
}