#ifndef SERVER_CONFIG_HPP
#define SERVER_CONFIG_HPP

#include <string>
#include <vector>
#include <map>

#include "LocationConfig.hpp"

class ServerConfig
{
private:
	std::string server_name;
	int listen;
	std::string client_max_body_size;
	bool autoindex;
	std::vector<std::string> allow_method;
	std::vector<std::string> index;
	std::vector<std::string> cgi_extension;
	std::map<int, std::string> redirect;
	std::map<int, std::string> error_page;
	std::string upload_filepath;

	std::map<std::string, LocationConfig> location_config;

public:
	ServerConfig();
	~ServerConfig();

	void setServerName(const std::string &server_name);
	void setListen(const int port);
	void setClientMaxBodySize(const std::string &client_max_body_size);
	void setAutoindex(const bool autoindex);
	void addAllowMethod(const std::string &allow_method);
	void addIndex(const std::string &index);
	void addCgiExtension(const std::string &cgi_extension);
	void addRedirect(const int redirect_status, const std::string &uri);
	void addErrorPage(const int error_status, const std::string &uri);
	void setUploadFilepath(const std::string &upload_filepath);
	void addLocationConfig(const std::string &path, const LocationConfig location_config);

	const std::string &getServerName() const;
	const int &getListen() const;
	const std::string &getClientMaxBodySize() const;
	const bool &getAutoIndex() const;
	const std::vector<std::string> &getAllowMethod() const;
	const std::vector<std::string> &getIndex() const;
	const std::vector<std::string> &getCgiExtension() const;
	const std::map<int, std::string> &getRedirect() const;
	const std::map<int, std::string> &getErrorPage() const;
	const std::string &getUploadFilepath() const;
	const std::map<std::string, LocationConfig> &getLocationConfig() const;
};

#endif