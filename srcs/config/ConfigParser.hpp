#ifndef CONFIG_PARSER_HPP
#define CONFIG_PARSER_HPP

#include <string>
#include <vector>

class ConfigParser
{
private:
	std::vector<std::vector<std::string>> parser_line;

	bool isParamDelimiter(int c);

public:
	ConfigParser();
	~ConfigParser();

	void readFile(const std::string &filepath);
	std::vector<std::string> splitLine(const std::string line);

	void printParserLine();
};

#endif
