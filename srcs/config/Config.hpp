#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>
#include <vector>

#include "ServerConfig.hpp"

class Config
{
private:
	std::string client_max_body_size;
	bool autoindex;
	std::vector<std::string> allow_method;
	std::vector<std::string> index;
	std::vector<std::string> cgi_extension;
	std::map<int, std::string> error_page;
	std::string upload_filepath;

	std::vector<ServerConfig> server_config;

public:
	Config();
	~Config();

	void setClientMaxBodySize(const std::string &client_max_body_size);
	void setAutoindex(const bool autoindex);
	void addAllowMethod(const std::string &allow_method);
	void addIndex(const std::string &index);
	void addCgiExtension(const std::string &cgi_extension);
	void addErrorPage(const int error_status, const std::string &uri);
	void setUploadFilepath(const std::string &upload_filepath);
	void addServerConfig(const ServerConfig server_config);

	const std::string &getClientMaxBodySize() const;
	const bool &getAutoIndex() const;
	const std::vector<std::string> &getAllowMethod() const;
	const std::vector<std::string> &getIndex() const;
	const std::vector<std::string> &getCgiExtension() const;
	const std::map<int, std::string> &getErrorPage() const;
	const std::string &getUploadFilepath() const;
	const std::vector<ServerConfig> &getServerConfig() const;
};

#endif
