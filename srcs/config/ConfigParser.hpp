#ifndef CONFIG_PARSER_HPP
#define CONFIG_PARSER_HPP

#include <string>
#include <vector>
#include <map>

#include "Config.hpp"

enum class E_DirectibeType
{
	SERVER_NAME,
	LISTEN,
	ERROR_PAGE,
	CLIENT_MAX_BODY_SIZE,
	INDEX,
	ALLOW_METHOD,
	REDIRECT,
	ALIAS,
	AUTOINDEX,
	CGI_EXTENSION,
	UPLOAD_FILEPATH,
};

enum class E_BlockType
{
	ROOT,
	SERVER,
	LOCATION,
};

class ConfigParser
{
private:
	std::vector<std::vector<std::string>> parser_line;

	Config config;
	ServerConfig server_config;
	LocationConfig location_config;

	E_BlockType nowBlock;
	bool isParamDelimiter(int c);

public:
	ConfigParser();
	~ConfigParser();

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

	void printParserLine();
};

#endif
