#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

// From https://stackoverflow.com/a/46931770, modified to use string_views
std::vector<std::string_view> split(std::string_view s, std::string_view delimiter) {
	size_t pos_start = 0, pos_end, delim_len = delimiter.length();
	std::vector<std::string_view> res;

	while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
		res.emplace_back(s.data() + (sizeof(*s.data()) * pos_start), pos_end - pos_start);
		// token = s.substr(pos_start, pos_end - pos_start);
		pos_start = pos_end + delim_len;
	}

	res.emplace_back(s.data() + (sizeof(*s.data()) * pos_start));
	return res;
}

std::string_view Trim(std::string_view in) {
	auto left = in.begin();
	for (;; ++left) {
		if (left == in.end())
			return {};
		if (!isspace(*left))
			break;
	}
	auto right = in.end() - 1;
	for (; right > left && isspace(*right); --right);
	return std::string_view(&(*left), std::distance(left, right) + 1);
}

void Day1(std::ifstream& inputFile)
{
	std::string line;
	int sum = 0;

	while (std::getline(inputFile, line))
	{
		std::vector<int> winners;
		int value = 0;

		std::vector<std::string_view> tokens = split(line, ": ");
		tokens = split(tokens[1], " | ");

		tokens[0] = Trim(tokens[0]);
		tokens[1] = Trim(tokens[1]);
		std::vector<std::string_view> winningNumbersData = split(tokens[0], " ");
		std::vector<std::string_view> ourNumbersData = split(tokens[1], " ");

		winners.reserve(winningNumbersData.size());
		for (const auto & number : winningNumbersData)
		{
			if (number.find_first_not_of(' ') == std::string::npos)
				continue;
			winners.emplace_back(std::stoi(std::string(number)));
		}

		for (const auto& number : ourNumbersData)
		{
			if (number.find_first_not_of(' ') == std::string::npos)
				continue;

			if (std::ranges::find(winners, std::stoi(std::string(number))) != winners.end())
			{
				if (value == 0)
					value = 1;
				else
					value *= 2;
			}
		}

		sum += value;
	}

	std::cout << sum << "\n";
}

struct Scratchcard
{
	// int Index;
	int Count = 1;
	std::vector<int> Winners;
	std::vector<int> Numbers;

	// This is completely unnessesary but I was going to hard at modelling the problem to begin with
	int GetWinners()
	{
		if (m_CachedValue != -1)
			return m_CachedValue;

		CalcWinners();
		
		return m_CachedValue;
	}

	void CalcWinners()
	{
		m_CachedValue = 0;
		for (int num : Numbers)
		{
			if (std::ranges::find(Winners.begin(), Winners.end(), num) != Winners.end())
				m_CachedValue++;
		}
	}

private:
	int m_CachedValue = -1;
};

void Day2(std::ifstream& inputFile)
{
	std::string line;
	std::vector<Scratchcard> input;
	std::queue<Scratchcard*> needsProcessing;

	// Process input data
	int i = 1;
	while (std::getline(inputFile, line))
	{
		Scratchcard scratchcard;
		// scratchcard.Index = i;

		std::vector<std::string_view> tokens = split(line, ": ");
		tokens = split(tokens[1], " | ");

		tokens[0] = Trim(tokens[0]);
		tokens[1] = Trim(tokens[1]);
		std::vector<std::string_view> winningNumbersData = split(tokens[0], " ");
		std::vector<std::string_view> ourNumbersData = split(tokens[1], " ");

		scratchcard.Winners.reserve(winningNumbersData.size());
		for (const auto& number : winningNumbersData)
		{
			if (number.find_first_not_of(' ') == std::string::npos)
				continue;
			scratchcard.Winners.emplace_back(std::stoi(std::string(number)));
		}

		for (const auto& number : ourNumbersData)
		{
			if (number.find_first_not_of(' ') == std::string::npos)
				continue;
			scratchcard.Numbers.emplace_back(std::stoi(std::string(number)));
		}

		scratchcard.CalcWinners();

		input.push_back(scratchcard);
		i++;
	}

	// Process original input
	for (int j = 0; j < input.size(); j++)
	{
		// This for loop made this take wayy longer than it should've.. originally tried to use Scratchcard.Index, which ended up being completely unused anyways.
		const int max = std::min(static_cast<int>(input.size()), j + input[j].GetWinners() + 1);
		for (int index = j + 1; index < max; index++)
		{
			// std::cout << "Card " << scratchcard.Index << " gives us a copy of " << index << "\n";
			// needsProcessing.push(&input[index - 1]);
			input[index].Count += input[j].Count;
		}
	}

	// I can't believe I wanted to do it this way...
	// Process queue until we're done
	/*while (!needsProcessing.empty())
	{
		Scratchcard* scratchcard = needsProcessing.front();

		scratchcard->Count++;
		const int max = std::min(static_cast<int>(input.size()), scratchcard->Index + scratchcard->GetWinners());
		for (int index = scratchcard->Index + 1; index < max; index++)
			needsProcessing.push(&input[index - 1]);

		needsProcessing.pop();
	}*/

	// Finally, sum up our counts
	int sum = 0;
	for (const Scratchcard& scratchcard : input)
		sum += scratchcard.Count;
	std::cout << sum << "\n";
}

int main()
{
	std::cout << "AOC23 Day 4\n";

	std::ifstream input("input.txt");
	if (!input.is_open())
	{
		std::cout << "Failed to open input file.\n";
		std::cin.get();
		return -1;
	}

	std::cout << "Day 1: ";
	Day1(input);
	input.clear();
	input.seekg(0, std::ios::beg);
	std::cout << "Day 2: ";
	Day2(input);
	input.close();

	std::cin.get();
}
