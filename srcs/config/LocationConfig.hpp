#ifndef LOCATION_CONFIG_HPP
#define LOCATION_CONFIG_HPP

#include <string>
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include "ConfigConstant.hpp"

class LocationConfig
{
private:
	std::set<E_DirectiveType> is_set;

	std::string uri;
	std::string alias;
	bool autoindex;
	std::set<std::string> allow_method;
	std::vector<std::string> index;
	std::pair<std::string, std::string> cgi_extension;
	std::pair<int, std::string> redirect;
	std::string upload_filepath;

public:
	static const int NO_REDIRECT = -1;
	LocationConfig();
	~LocationConfig();
	LocationConfig(const LocationConfig& src);
	LocationConfig& operator=(const LocationConfig& rhs);

	void setUri(const std::string &uri);
	void setAlias(const std::string &alias);
	void setAutoindex(const bool autoindex);
	void setAllowMethod(const std::set<std::string> &allow_method);
	void addIndex(const std::vector<std::string> &index);
	void setCgiExtension(const std::pair<std::string, std::string> &cgi_extension);
	void setRedirect(const std::pair<int, std::string>& redirect);
	void setUploadFilepath(const std::string &upload_filepath);

	const std::string &getUri() const;
	const std::string &getAlias() const;
	const bool &getAutoIndex() const;
	const std::set<std::string> &getAllowMethod() const;
	const std::vector<std::string> &getIndex() const;
	const std::pair<std::string, std::string> &getCgiExtension() const;
	const std::pair<int, std::string> &getRedirect() const;
	const std::string &getUploadFilepath() const;

	void print() const;
};

#endif