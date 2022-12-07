#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>
#include <vector>

#include "ServerConfig.hpp"

class Config
{
private:
	std::vector<ServerConfig> server_config;

public:
	Config();
	~Config();
	Config(const Config& src);
	Config& operator=(const Config& rhs);

	void addServerConfig(const ServerConfig server_config);
	const std::vector<ServerConfig> &getServerConfig() const;
};

#endif
