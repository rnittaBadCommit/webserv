#include "ServerConfig.hpp"

ServerConfig::ServerConfig()
	: server_name(), listen(), client_max_body_size(),
	  autoindex(), allow_method(), index(),
	  cgi_extension(), redirect(), error_page(),
	  upload_filepath(), location_config()
{
}

ServerConfig::~ServerConfig()
{
}

void ServerConfig::setServerName(const std::string &server_name)
{
	this->server_name = server_name;
}

void ServerConfig::setListen(const int port)
{
	this->listen = port;
}

void ServerConfig::setClientMaxBodySize(const std::string &client_max_body_size)
{
	this->client_max_body_size = client_max_body_size;
}

void ServerConfig::setAutoindex(const bool autoindex)
{
	this->autoindex = autoindex;
}

void ServerConfig::addAllowMethod(const std::string &allow_method)
{
	this->allow_method.push_back(allow_method);
}

void ServerConfig::addIndex(const std::string &index)
{
	this->index.push_back(index);
}

void ServerConfig::addCgiExtension(const std::string &cgi_extension)
{
	this->cgi_extension.push_back(cgi_extension);
}

void ServerConfig::addRedirect(const int redirect_status, const std::string &uri)
{
	this->redirect.insert(std::make_pair(redirect_status, uri));
}

void ServerConfig::addErrorPage(const int error_status, const std::string &uri)
{
	this->error_page.insert(std::make_pair(error_status, uri));
}

void ServerConfig::setUploadFilepath(const std::string &upload_filepath)
{
	this->upload_filepath = upload_filepath;
}

void ServerConfig::addLocationConfig(const std::string &path, const LocationConfig location_config)
{
	this->location_config.insert(std::make_pair(path, location_config));
}

const std::string &ServerConfig::getServerName() const
{
	return this->server_name;
}

const int &ServerConfig::getListen() const
{
	return this->listen;
}

const std::string &ServerConfig::getClientMaxBodySize() const
{
	return this->client_max_body_size;
}

const bool &ServerConfig::getAutoIndex() const
{
	return this->autoindex;
}

const std::vector<std::string> &ServerConfig::getAllowMethod() const
{
	return this->allow_method;
}

const std::vector<std::string> &ServerConfig::getIndex() const
{
	return this->index;
}

const std::vector<std::string> &ServerConfig::getCgiExtension() const
{
	return this->cgi_extension;
}

const std::map<int, std::string> &ServerConfig::getRedirect() const
{
	return this->redirect;
}

const std::map<int, std::string> &ServerConfig::getErrorPage() const
{
	return this->error_page;
}

const std::string &ServerConfig::getUploadFilepath() const
{
	return this->upload_filepath;
}

const std::map<std::string, LocationConfig> &ServerConfig::getLocationConfig() const
{
	return this->location_config;
}
