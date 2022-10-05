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
	int listen;
	std::string client_max_body_size;
	std::map<int, std::string> error_page;
	std::map<std::string, LocationConfig> location_config;

public:
	ServerConfig();
	~ServerConfig();

	void setServerName(const std::string &server_name);
	void setListen(const int port);
	void setClientMaxBodySize(const std::string &client_max_body_size);
	void addErrorPage(const int error_status, const std::string &uri);
	void addLocationConfig(const std::string &path, const LocationConfig location_config);

	const std::string &getServerName() const;
	const int &getListen() const;
	const std::string &getClientMaxBodySize() const;
	const std::map<int, std::string> &getErrorPage() const;
	const std::map<std::string, LocationConfig> &getLocationConfig() const;

	bool isSet(E_DirectiveType type);
};

#endif