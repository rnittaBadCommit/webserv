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

Config ConfigParser::readFile(const std::string &filepath)
{
	std::ifstream ifs(filepath);

	std::string line;
	while (std::getline(ifs, line))
	{
		if (line.length() == 0 || (line.length() != 0 && line[0] == '#'))
		{
			continue;
		}
		std::vector<std::string> params = this->splitLine(line);
		this->parser_line.push_back(params);
	}
	this->setConfigFromParseLine();
	return this->config;
}

void ConfigParser::setConfigFromParseLine()
{
	this->nowBlock = E_BlockType::ROOT;
	for (std::vector<std::string> line : this->parser_line)
	{
		switch (this->nowBlock)
		{
		case E_BlockType::ROOT:
			this->setConfigRoot(line);
			break;
		case E_BlockType::SERVER:
			this->setConfigServer(line);
			break;
		case E_BlockType::LOCATION:
			this->setConfigLocation(line);
			break;
		}
	}
}

void ConfigParser::setConfigRoot(std::vector<std::string> line)
{
	if (line[0] == "index")
		this->setConfigIndex(E_BlockType::ROOT, line);
	else if (line[0] == "autoindex")
		this->setConfigAutoIndex(E_BlockType::ROOT, line);
	else if (line[0] == "client_max_body_size")
		this->setConfigClientMaxBodySize(E_BlockType::ROOT, line);
	else if (line[0] == "allow_method")
		this->setConfigAllowMethod(E_BlockType::ROOT, line);
	else if (line[0] == "cgi_extension")
		this->setConfigCgiExtension(E_BlockType::ROOT, line);
	else if (line[0] == "error_page")
		this->setConfigErrorPage(E_BlockType::ROOT, line);
	else if (line[0] == "upload_filepath")
		this->setConfigUploadFilepath(E_BlockType::ROOT, line);
	else if (line[0] == "server" && line[1] == "{")
	{
		this->nowBlock = E_BlockType::SERVER;
	}
	else
	{
		throw std::invalid_argument("Root config Error");
	}
}

void ConfigParser::setConfigServer(std::vector<std::string> line)
{
	if (line[0] == "index")
		this->setConfigIndex(E_BlockType::SERVER, line);
	else if (line[0] == "server_name")
		this->setConfigServerName(E_BlockType::SERVER, line);
	else if (line[0] == "listen")
		this->setConfigListen(E_BlockType::SERVER, line);
	else if (line[0] == "return")
		this->setConfigRedirect(E_BlockType::SERVER, line);
	else if (line[0] == "autoindex")
		this->setConfigAutoIndex(E_BlockType::SERVER, line);
	else if (line[0] == "client_max_body_size")
		this->setConfigClientMaxBodySize(E_BlockType::SERVER, line);
	else if (line[0] == "allow_method")
		this->setConfigAllowMethod(E_BlockType::SERVER, line);
	else if (line[0] == "cgi_extension")
		this->setConfigCgiExtension(E_BlockType::SERVER, line);
	else if (line[0] == "error_page")
		this->setConfigErrorPage(E_BlockType::SERVER, line);
	else if (line[0] == "upload_filepath")
		this->setConfigUploadFilepath(E_BlockType::SERVER, line);
	else if (line[0] == "location" && line[2] == "{")
	{
		this->nowBlock = E_BlockType::LOCATION;
		this->location_config.setUri(line[1]);
	}
	else if (line[0] == "}")
	{
		this->config.addServerConfig(this->server_config);
		this->server_config = ServerConfig();
		this->nowBlock = E_BlockType::ROOT;
	}
	else
	{
		throw std::invalid_argument("Server config Error");
	}
}

void ConfigParser::setConfigLocation(std::vector<std::string> line)
{
	if (line[0] == "index")
		this->setConfigIndex(E_BlockType::LOCATION, line);
	else if (line[0] == "alias")
		this->setConfigAlias(E_BlockType::LOCATION, line);
	else if (line[0] == "return")
		this->setConfigRedirect(E_BlockType::LOCATION, line);
	else if (line[0] == "autoindex")
		this->setConfigAutoIndex(E_BlockType::LOCATION, line);
	else if (line[0] == "allow_method")
		this->setConfigAllowMethod(E_BlockType::LOCATION, line);
	else if (line[0] == "cgi_extension")
		this->setConfigCgiExtension(E_BlockType::LOCATION, line);
	else if (line[0] == "error_page")
		this->setConfigErrorPage(E_BlockType::LOCATION, line);
	else if (line[0] == "upload_filepath")
		this->setConfigUploadFilepath(E_BlockType::LOCATION, line);
	else if (line[0] == "}")
	{
		this->server_config.addLocationConfig(this->location_config.getUri(), this->location_config);
		this->location_config = LocationConfig();
		this->nowBlock = E_BlockType::SERVER;
	}
	else
	{
		throw std::invalid_argument("Location config Error");
	}
}

void ConfigParser::setConfigServerName(E_BlockType block_type, std::vector<std::string> line)
{
	switch (block_type)
	{
	case E_BlockType::ROOT:
		throw std::exception();
		break;
	case E_BlockType::SERVER:
		this->server_config.setServerName(line[1]);
		break;
	case E_BlockType::LOCATION:
		throw std::exception();
		break;
	}
}

void ConfigParser::setConfigListen(E_BlockType block_type, std::vector<std::string> line)
{
	switch (block_type)
	{
	case E_BlockType::ROOT:
		throw std::exception();
		break;
	case E_BlockType::SERVER:
		this->server_config.setListen(std::atoi(line[1].c_str()));
		break;
	case E_BlockType::LOCATION:
		throw std::exception();
		break;
	}
}

void ConfigParser::setConfigErrorPage(E_BlockType block_type, std::vector<std::string> line)
{
	switch (block_type)
	{
	case E_BlockType::ROOT:
		throw std::exception();
		break;
	case E_BlockType::SERVER:
		for (int i = 1; i < line.size() - 1; i++)
		{
			this->server_config.addRedirect(atoi(line[1].c_str()), line[2]);
		}
		break;
	case E_BlockType::LOCATION:
		for (int i = 1; i < line.size() - 1; i++)
		{
			this->location_config.addRedirect(atoi(line[1].c_str()), line[2]);
		}
		break;
	}
}

void ConfigParser::setConfigClientMaxBodySize(E_BlockType block_type, std::vector<std::string> line)
{
	switch (block_type)
	{
	case E_BlockType::ROOT:
		this->config.setClientMaxBodySize(line[1]);
		break;
	case E_BlockType::SERVER:
		this->server_config.setClientMaxBodySize(line[1]);
		break;
	case E_BlockType::LOCATION:
		throw std::exception();
		break;
	}
}

void ConfigParser::setConfigAllowMethod(E_BlockType block_type, std::vector<std::string> line)
{
	switch (block_type)
	{
	case E_BlockType::ROOT:
		for (int i = 1; i < line.size() - 1; i++)
		{
			this->config.addAllowMethod(line[i]);
		}
		break;
	case E_BlockType::SERVER:
		for (int i = 1; i < line.size() - 1; i++)
		{
			this->server_config.addAllowMethod(line[i]);
		}
		break;
	case E_BlockType::LOCATION:
		for (int i = 1; i < line.size() - 1; i++)
		{
			this->location_config.addAllowMethod(line[i]);
		}
		break;
	}
}

void ConfigParser::setConfigRedirect(E_BlockType block_type, std::vector<std::string> line)
{
	switch (block_type)
	{
	case E_BlockType::ROOT:
		throw std::exception();
		break;
	case E_BlockType::SERVER:
		for (int i = 1; i < line.size() - 1; i++)
		{
			this->server_config.addRedirect(atoi(line[1].c_str()), line[2]);
		}
		break;
	case E_BlockType::LOCATION:
		for (int i = 1; i < line.size() - 1; i++)
		{
			this->location_config.addRedirect(atoi(line[1].c_str()), line[2]);
		}
		break;
	}
}

void ConfigParser::setConfigAlias(E_BlockType block_type, std::vector<std::string> line)
{
	switch (block_type)
	{
	case E_BlockType::ROOT:
		throw std::exception();
		break;
	case E_BlockType::SERVER:
		throw std::exception();
		break;
	case E_BlockType::LOCATION:
		this->location_config.setAlias(line[1]);
		break;
	}
}

void ConfigParser::setConfigAutoIndex(E_BlockType block_type, std::vector<std::string> line)
{
	bool autoindex;
	if (line[1] == "on")
		autoindex = true;
	else if (line[1] == "off")
		autoindex = false;
	else
		throw std::exception();

	switch (block_type)
	{
	case E_BlockType::ROOT:
		this->config.setAutoindex(autoindex);
		break;
	case E_BlockType::SERVER:
		this->server_config.setAutoindex(autoindex);
		break;
	case E_BlockType::LOCATION:
		this->location_config.setAutoindex(autoindex);
		break;
	}
}

void ConfigParser::setConfigIndex(E_BlockType block_type, std::vector<std::string> line)
{
	switch (block_type)
	{
	case E_BlockType::ROOT:
		for (int i = 1; i < line.size() - 1; i++)
		{
			this->config.addIndex(line[i]);
		}
		break;
	case E_BlockType::SERVER:
		for (int i = 1; i < line.size() - 1; i++)
		{
			this->server_config.addIndex(line[i]);
		}
		break;
	case E_BlockType::LOCATION:
		for (int i = 1; i < line.size() - 1; i++)
		{
			this->location_config.addIndex(line[i]);
		}
		break;
	}
}

void ConfigParser::setConfigCgiExtension(E_BlockType block_type, std::vector<std::string> line)
{
	switch (block_type)
	{
	case E_BlockType::ROOT:
		for (int i = 1; i < line.size() - 1; i++)
		{
			this->config.addCgiExtension(line[i]);
		}
		break;
	case E_BlockType::SERVER:
		for (int i = 1; i < line.size() - 1; i++)
		{
			this->server_config.addCgiExtension(line[i]);
		}
		break;
	case E_BlockType::LOCATION:
		for (int i = 1; i < line.size() - 1; i++)
		{
			this->location_config.addCgiExtension(line[i]);
		}
		break;
	}
}

void ConfigParser::setConfigUploadFilepath(E_BlockType block_type, std::vector<std::string> line)
{
	switch (block_type)
	{
	case E_BlockType::ROOT:
		this->config.setUploadFilepath(line[1]);
		break;
	case E_BlockType::SERVER:
		this->server_config.setUploadFilepath(line[1]);
		break;
	case E_BlockType::LOCATION:
		this->location_config.setUploadFilepath(line[1]);
		break;
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