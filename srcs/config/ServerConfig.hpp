#ifndef SERVER_CONFIG_HPP
#define SERVER_CONFIG_HPP

#include <string>
#include <vector>
#include <map>
#include <set>

#include "LocationConfig.hpp"
#include "ConfigConstant.hpp"

class ServerConfig
{
private:
	std::set<E_DirectiveType> is_set;

	std::string server_name;
	unsigned int listen;
	unsigned int client_max_body_size;
	std::map<unsigned int, std::string> error_page;
	std::map<std::string, LocationConfig> location_config;

public:
	ServerConfig();
	~ServerConfig();
	ServerConfig(const ServerConfig& src);
	ServerConfig& operator=(const ServerConfig& rhs);

	void setServerName(const std::string &server_name);
	void setListen(const unsigned int port);
	void setClientMaxBodySize(const unsigned int client_max_body_size);
	void addErrorPage(const std::map<unsigned int, std::string> &error_page);
	void addLocationConfig(const std::string &path, const LocationConfig location_config);

	const std::string &getServerName() const;
	const unsigned int &getListen() const;
	const unsigned int &getClientMaxBodySize() const;
	const std::map<unsigned int, std::string> &getErrorPage() const;
	const std::map<std::string, LocationConfig> &getLocationConfig() const;

	bool isSet(E_DirectiveType type);
	void print();
};

#endif