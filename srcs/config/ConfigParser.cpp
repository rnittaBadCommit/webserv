#include "ConfigParser.hpp"
#include <vector>
#include <fstream>
#include <iostream>

ConfigParser::ConfigParser()
{
}

ConfigParser::~ConfigParser()
{
}

void ConfigParser::printParserLine()
{
	for (int i = 0; i < this->parser_line.size(); i++)
	{
		for (const auto &e : this->parser_line[i])
		{
			std::cout << e << " ";
		}
		std::cout << std::endl;
	}
}

void ConfigParser::readFile(const std::string &filepath)
{
	std::ifstream ifs(filepath);

	std::string line;
	while (std::getline(ifs, line))
	{
		if (line.length() != 0 && line[0] == '#')
		{
			continue;
		}
		std::vector<std::string> params = this->splitLine(line);
		this->parser_line.push_back(params);
	}
}

std::vector<std::string> ConfigParser::splitLine(const std::string line)
{
	std::vector<std::string> params;
	size_t start = 0;
	size_t end = 0;

	while (line[start])
	{
		while (isspace(line[start]))
		{
			start++;
		}
		end = start;
		while (isprint(line[end]) && !(isspace(line[end]) || isParamDelimiter(line[end])))
		{
			end++;
		}
		if ((end - start) != 0)
		{
			params.push_back(line.substr(start, (end - start)));
		}
		if (isParamDelimiter(line[end]))
		{
			start = end;
			++end;
			params.push_back(line.substr(start, (end - start)));
		}
		start = end;
	}
	return params;
}

bool ConfigParser::isParamDelimiter(int c)
{
	return ((c == '{') || (c == '}') || (c == ';'));
}