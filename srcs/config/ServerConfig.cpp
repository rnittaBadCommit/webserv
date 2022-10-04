#include "ServerConfig.hpp"

ServerConfig::ServerConfig()
	: server_name(), listen(), client_max_body_size(),
	  error_page(), location_config()
{
}

ServerConfig::~ServerConfig()
{
}

void ServerConfig::setServerName(const std::string &server_name)
{
	this->is_set.insert(E_DirectiveType::SERVER_NAME);
	this->server_name = server_name;
}

void ServerConfig::setListen(const int port)
{
	this->is_set.insert(E_DirectiveType::LISTEN);
	this->listen = port;
}

void ServerConfig::setClientMaxBodySize(const std::string &client_max_body_size)
{
	this->is_set.insert(E_DirectiveType::CLIENT_MAX_BODY_SIZE);
	this->client_max_body_size = client_max_body_size;
}

void ServerConfig::addErrorPage(const int error_status, const std::string &uri)
{
	this->is_set.insert(E_DirectiveType::ERROR_PAGE);
	this->error_page.insert(std::make_pair(error_status, uri));
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

const std::map<int, std::string> &ServerConfig::getErrorPage() const
{
	return this->error_page;
}

const std::map<std::string, LocationConfig> &ServerConfig::getLocationConfig() const
{
	return this->location_config;
}

const bool ServerConfig::isSet(E_DirectiveType type)
{
	return (this->is_set.find(type) != this->is_set.end());
}