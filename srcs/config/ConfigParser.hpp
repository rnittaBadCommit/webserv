#ifndef CONFIG_PARSER_HPP
#define CONFIG_PARSER_HPP

#include <string>
#include <vector>
#include <map>

#include "Config.hpp"
#include "ConfigConstant.hpp"

class ConfigParser
{
private:
	std::vector<std::vector<std::string> > parser_line;

	Config config;
	ServerConfig server_config;
	LocationConfig location_config;

	E_BlockType nowBlock;
	bool isParamDelimiter(int c);

public:
	ConfigParser();
	~ConfigParser();
	ConfigParser(const ConfigParser& src);
	ConfigParser& operator=(const ConfigParser& rhs);

	Config readFile(const std::string &filepath);
	std::vector<std::string> splitLine(const std::string line);
	void setConfigFromParseLine();

	void setConfigRoot(std::vector<std::string> line);
	void setConfigServer(std::vector<std::string> line);
	void setConfigLocation(std::vector<std::string> line);

	void setConfigServerName(E_BlockType block_type, std::vector<std::string> line);
	void setConfigListen(E_BlockType block_type, std::vector<std::string> line);
	void setConfigErrorPage(E_BlockType block_type, std::vector<std::string> line);
	void setConfigClientMaxBodySize(E_BlockType block_type, std::vector<std::string> line);
	void setConfigAllowMethod(E_BlockType block_type, std::vector<std::string> line);
	void setConfigRedirect(E_BlockType block_type, std::vector<std::string> line);
	void setConfigAlias(E_BlockType block_type, std::vector<std::string> line);
	void setConfigAutoIndex(E_BlockType block_type, std::vector<std::string> line);
	void setConfigIndex(E_BlockType block_type, std::vector<std::string> line);
	void setConfigCgiExtension(E_BlockType block_type, std::vector<std::string> line);
	void setConfigUploadFilepath(E_BlockType block_type, std::vector<std::string> line);

	void validateServerName(std::vector<std::string> line);
	void validateErrorPage(std::vector<std::string> line);
	unsigned int validateListen(std::vector<std::string> line);
	void validateClientMaxBodySize(std::vector<std::string> line);
	/*


	void validateAllowMethod(std::vector<std::string> line);
	void validateRedirect(std::vector<std::string> line);
	void validateAlias(std::vector<std::string> line);
	void validateAutoIndex(std::vector<std::string> line);
	void validateIndex(std::vector<std::string> line);
	void validateCgiExtension(std::vector<std::string> line);
	void validateUploadFilepath(std::vector<std::string> line);*/

	void printParserLine();
};

#endif
