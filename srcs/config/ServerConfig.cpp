#include "ServerConfig.hpp"

ServerConfig::ServerConfig()
	: server_name(), listen(), client_max_body_size(),
	  error_page(), location_config()
{
}

ServerConfig::~ServerConfig()
{
}

ServerConfig::ServerConfig(const ServerConfig& src) {
	is_set = src.is_set;
	server_name = src.server_name;
	listen = src.listen;
	client_max_body_size = src.client_max_body_size;
	error_page = src.error_page;
	location_config = src.location_config;
}
	
#include <iostream>
ServerConfig& ServerConfig::operator=(const ServerConfig& rhs) {
	if (this != &rhs) {
		is_set = rhs.is_set;
		server_name = rhs.server_name;
		listen = rhs.listen;
		client_max_body_size = rhs.client_max_body_size;
		error_page = rhs.error_page;
		location_config = rhs.location_config;
	}
	return (*this);
}

void ServerConfig::setServerName(const std::string &server_name)
{
	this->is_set.insert(SERVER_NAME);
	this->server_name = server_name;
}

void ServerConfig::setListen(const int port)
{
	this->is_set.insert(LISTEN);
	this->listen = port;
}

void ServerConfig::setClientMaxBodySize(const std::string &client_max_body_size)
{
	this->is_set.insert(CLIENT_MAX_BODY_SIZE);
	this->client_max_body_size = client_max_body_size;
}

void ServerConfig::addErrorPage(const int error_status, const std::string &uri)
{
	this->is_set.insert(ERROR_PAGE);
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

bool ServerConfig::isSet(E_DirectiveType type)
{
	return (this->is_set.find(type) != this->is_set.end());
}