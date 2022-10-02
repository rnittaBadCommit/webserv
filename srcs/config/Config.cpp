#include "Config.hpp"

Config::Config()
	: client_max_body_size(), autoindex(), allow_method(),
	  index(), cgi_extension(), error_page(), upload_filepath()
{
}

Config::~Config()
{
}

void Config::setClientMaxBodySize(const std::string &client_max_body_size)
{
	this->client_max_body_size = client_max_body_size;
}

void Config::setAutoindex(const bool autoindex)
{
	this->autoindex = autoindex;
}

void Config::addAllowMethod(const std::string &allow_method)
{
	this->allow_method.push_back(allow_method);
}

void Config::addIndex(const std::string &index)
{
	this->index.push_back(index);
}

void Config::addCgiExtension(const std::string &cgi_extension)
{
	this->cgi_extension.push_back(cgi_extension);
}

void Config::addErrorPage(const int error_status, const std::string &uri)
{
	this->error_page.insert(std::make_pair(error_status, uri));
}

void Config::setUploadFilepath(const std::string &upload_filepath)
{
	this->upload_filepath = upload_filepath;
}

void Config::addServerConfig(const ServerConfig server_config)
{
	this->server_config.push_back(server_config);
}

const std::string &Config::getClientMaxBodySize() const
{
	return this->client_max_body_size;
}

const bool &Config::getAutoIndex() const
{
	return this->autoindex;
}

const std::vector<std::string> &Config::getAllowMethod() const
{
	return this->allow_method;
}

const std::vector<std::string> &Config::getIndex() const
{
	return this->index;
}

const std::vector<std::string> &Config::getCgiExtension() const
{
	return this->cgi_extension;
}

const std::map<int, std::string> &Config::getErrorPage() const
{
	return this->error_page;
}

const std::string &Config::getUploadFilepath() const
{
	return this->upload_filepath;
}

const std::vector<ServerConfig> &Config::getServerConfig() const
{
	return this->server_config;
}
