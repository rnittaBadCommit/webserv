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
public:
	typedef std::map<std::string, LocationConfig> loc_conf_map;
	typedef std::map<unsigned int, std::string> err_page_map;

private:
	std::set<E_DirectiveType> is_set;

	std::string server_name;
	unsigned int listen;
	unsigned int client_max_body_size;
	err_page_map error_page;
	loc_conf_map location_config;

public:
	ServerConfig();
	~ServerConfig();
	ServerConfig(const ServerConfig& src);
	ServerConfig& operator=(const ServerConfig& rhs);

	void setServerName(const std::string &server_name);
	void setListen(const unsigned int port);
	void setClientMaxBodySize(const unsigned int client_max_body_size);
	void addErrorPage(const err_page_map &error_page);
	void addLocationConfig(const std::string &path, const LocationConfig location_config);

	const std::string &getServerName() const;
	const unsigned int &getListen() const;
	const unsigned int &getClientMaxBodySize() const;
	const err_page_map &getErrorPage() const;
	const loc_conf_map &getLocationConfig() const;

	bool isSet(E_DirectiveType type);
	void print();
};

#endif