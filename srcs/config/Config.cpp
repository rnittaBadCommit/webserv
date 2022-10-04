#include "Config.hpp"

Config::Config()
{
}

Config::~Config()
{
}

void Config::addServerConfig(const ServerConfig server_config)
{
	this->server_config.push_back(server_config);
}
const std::vector<ServerConfig> &Config::getServerConfig() const
{
	return this->server_config;
}
