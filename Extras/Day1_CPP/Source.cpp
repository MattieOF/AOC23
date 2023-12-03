#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <string_view>

void Day1(std::ifstream& inputFile)
{
	std::vector<int> digits;
	std::string line;
	int sum = 0;

	while (std::getline(inputFile, line))
	{
		digits.clear();

		for (const char ch : line)
		{
			if (std::isdigit(ch))
				digits.emplace_back(ch - '0');
		}

		if (!digits.empty())
			sum += (digits.front() * 10) + digits.back();
	}

	std::cout << sum << "\n";
}

bool FollowingCharsEqualTo(const std::string& mainString, size_t startIndex, std::string_view lookingFor)
{
	if (mainString.length() - startIndex < lookingFor.length()) // Check lookingFor isn't too long
		return false;

	if (std::string_view(mainString.c_str() + (sizeof(*mainString.c_str()) * startIndex), sizeof(*mainString.c_str()) * lookingFor.length()) == lookingFor)
		return true;

	return false;
}

void Day2(std::ifstream& inputFile)
{
	std::vector<int> digits;
	std::string line;
	int sum = 0;

	while (std::getline(inputFile, line))
	{
		digits.clear();

		for (size_t i = 0; i < line.length(); i++)
		{
			if (std::isdigit(line[i]))
				digits.emplace_back(line[i] - '0');
			else
			{
				switch (line[i])
				{
				case 'o': // One
					if (FollowingCharsEqualTo(line, i, "one"))
						digits.emplace_back(1);
					break;
				case 't': // Two, Three
					if (FollowingCharsEqualTo(line, i, "two"))
						digits.emplace_back(2);
					else if (FollowingCharsEqualTo(line, i, "three"))
						digits.emplace_back(3);
					break;
				case 'f': // Four, Five
					if (FollowingCharsEqualTo(line, i, "four"))
						digits.emplace_back(4);
					else if (FollowingCharsEqualTo(line, i, "five"))
						digits.emplace_back(5);
					break;
				case 's': // Six, Seven
					if (FollowingCharsEqualTo(line, i, "six"))
						digits.emplace_back(6);
					else if (FollowingCharsEqualTo(line, i, "seven"))
						digits.emplace_back(7);
					break;
				case 'e': // Eight
					if (FollowingCharsEqualTo(line, i, "eight"))
						digits.emplace_back(8);
					break;
				case 'n': // Nine
					if (FollowingCharsEqualTo(line, i, "nine"))
						digits.emplace_back(9);
					break;
				default:
					continue;
				}
			}
		}

		if (!digits.empty())
			sum += (digits.front() * 10) + digits.back();
	}

	std::cout << sum << "\n";
}

int main()
{
	std::cout << "AOC23 Day 1\n";

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
