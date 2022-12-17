#include "ServerConfig.hpp"

ServerConfig::ServerConfig()
	: is_set(), server_name(), listen(), client_max_body_size(),
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

void ServerConfig::setListen(const unsigned int port)
{
	if (is_set.find(LISTEN) != is_set.end()) {
		throw std::runtime_error("Multiple listen directives");
	}
	this->is_set.insert(LISTEN);
	this->listen = port;
}

void ServerConfig::setClientMaxBodySize(const unsigned int client_max_body_size)
{
	if (is_set.find(CLIENT_MAX_BODY_SIZE) != is_set.end()) {
		throw std::runtime_error("Multiple client_max_body_size directives");
	}
	this->is_set.insert(CLIENT_MAX_BODY_SIZE);
	this->client_max_body_size = client_max_body_size;
}

void ServerConfig::addErrorPage(const std::map<unsigned int, std::string> &error_page)
{
	this->is_set.insert(ERROR_PAGE);
	this->error_page.insert(error_page.begin(), error_page.end());
}

void ServerConfig::addLocationConfig(const std::string &path, const LocationConfig location_config)
{
	if (this->location_config.find(path) != this->location_config.end()) {
		throw std::runtime_error("Multiple " + path + " location directives");
	}
	this->location_config.insert(std::make_pair(path, location_config));
}

const std::string &ServerConfig::getServerName() const
{
	return this->server_name;
}

const unsigned int &ServerConfig::getListen() const
{
	return this->listen;
}

const unsigned int &ServerConfig::getClientMaxBodySize() const
{
	return this->client_max_body_size;
}

const std::map<unsigned int, std::string> &ServerConfig::getErrorPage() const
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

void ServerConfig::print() {
	std::cout << "server_name: " << server_name << std::endl;
	std::cout << "listen: " << listen << std::endl;	
	std::cout << "client MBS: " << client_max_body_size << std::endl;
	std::cout << "error_page:\n";
	for (std::map<unsigned int, std::string>::iterator it = error_page.begin(); it != error_page.end(); ++it) {
		std::cout << "\t" << it->first << " - " << it->second << std::endl;
	}
}
