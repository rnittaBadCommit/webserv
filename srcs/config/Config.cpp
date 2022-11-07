#include "Config.hpp"

Config::Config() : server_config()
{
}

Config::~Config()
{
}

Config::Config(const Config& src) {
	server_config = src.server_config;
}

Config& Config::operator=(const Config& rhs) {
	if (this != &rhs) {
		server_config = rhs.server_config;
	}
	return (*this);
}

void Config::addServerConfig(const ServerConfig server_config)
{
	this->server_config.push_back(server_config);
}

const std::vector<ServerConfig> &Config::getServerConfig() const
{
	return this->server_config;
}
