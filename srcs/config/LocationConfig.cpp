#include "LocationConfig.hpp"

LocationConfig::LocationConfig()
	: uri(), alias(), autoindex(), allow_method(),
	  index(), cgi_extension(), redirect(),
	  upload_filepath()
{
}

LocationConfig::~LocationConfig()
{
}

void LocationConfig::setUri(const std::string &uri)
{
	this->uri = uri;
}

void LocationConfig::setAlias(const std::string &alias)
{
	this->is_set.insert(ALIAS);
	this->alias = alias;
}

void LocationConfig::setAutoindex(const bool autoindex)
{
	this->is_set.insert(AUTOINDEX);
	this->autoindex = autoindex;
}

void LocationConfig::addAllowMethod(const std::string &allow_method)
{
	this->is_set.insert(ALLOW_METHOD);
	this->allow_method.push_back(allow_method);
}

void LocationConfig::addIndex(const std::string &index)
{
	this->is_set.insert(INDEX);
	this->index.push_back(index);
}

void LocationConfig::addCgiExtension(const std::string &cgi_extension)
{
	this->is_set.insert(CGI_EXTENSION);
	this->cgi_extension.push_back(cgi_extension);
}

void LocationConfig::addRedirect(const int redirect_status, const std::string &uri)
{
	this->is_set.insert(REDIRECT);
	this->redirect.insert(std::make_pair(redirect_status, uri));
}

void LocationConfig::setUploadFilepath(const std::string &upload_filepath)
{
	this->is_set.insert(UPLOAD_FILEPATH);
	this->upload_filepath = upload_filepath;
}

const std::string &LocationConfig::getUri() const
{
	return this->uri;
}

const std::string &LocationConfig::getAlias() const
{
	return this->alias;
}

const bool &LocationConfig::getAutoIndex() const
{
	return this->autoindex;
}

const std::vector<std::string> &LocationConfig::getAllowMethod() const
{
	return this->allow_method;
}

const std::vector<std::string> &LocationConfig::getIndex() const
{
	return this->index;
}

const std::vector<std::string> &LocationConfig::getCgiExtension() const
{
	return this->cgi_extension;
}

const std::map<int, std::string> &LocationConfig::getRedirect() const
{
	return this->redirect;
}

const std::string &LocationConfig::getUploadFilepath() const
{
	return this->upload_filepath;
}
