#include "LocationConfig.hpp"

LocationConfig::LocationConfig()
	: is_set(), uri(), alias(), autoindex(), allow_method(),
	  index(), cgi_extension(), redirect(-1, ""),
	  upload_filepath()
{
}

LocationConfig::~LocationConfig()
{
}

LocationConfig::LocationConfig(const LocationConfig& src)
{
	is_set = src.is_set;
	uri = src.uri;
	alias = src.alias;
	autoindex = src.autoindex;
	allow_method = src.allow_method;
	index = src.index;
	cgi_extension = src.cgi_extension;
	redirect = src.redirect;
	upload_filepath = src.upload_filepath;
}

LocationConfig& LocationConfig::operator=(const LocationConfig& rhs)
{
	if (this != &rhs) {
		is_set = rhs.is_set;
		uri = rhs.uri;
		alias = rhs.alias;
		autoindex = rhs.autoindex;
		allow_method = rhs.allow_method;
		index = rhs.index;
		cgi_extension = rhs.cgi_extension;
		redirect = rhs.redirect;
		upload_filepath = rhs.upload_filepath;
	}
	return (*this);
}

void LocationConfig::setUri(const std::string &uri)
{
	this->uri = uri;
}

void LocationConfig::setAlias(const std::string &alias)
{
	if (directiveSet(ALIAS)) {
		throw std::runtime_error("Multiple alias directives");
	}
	this->is_set.insert(ALIAS);
	this->alias = alias;
}

void LocationConfig::setAutoindex(const bool autoindex)
{
	if (directiveSet(AUTOINDEX)) {
		throw std::runtime_error("Multiple autoindex directives");
	}
	this->is_set.insert(AUTOINDEX);
	this->autoindex = autoindex;
}

void LocationConfig::setAllowMethod(const std::set<std::string> &allow_method)
{
	if (directiveSet(ALLOW_METHOD)) {
		throw std::runtime_error("Multiple allow_method directives");
	}
	if (directiveSet(REDIRECT)
		&& (allow_method.find("GET") == allow_method.end() || allow_method.size() > 1)) {
			throw std::runtime_error("Redirect only allowed with GET");
	}
	this->is_set.insert(ALLOW_METHOD);
	this->allow_method = allow_method;
}

void LocationConfig::addIndex(const std::vector<std::string> &index)
{
	this->is_set.insert(INDEX);
	this->index.insert(this->index.end(), index.begin(), index.end());
}

void LocationConfig::setCgiExtension(const std::pair<std::string, std::string> &cgi_extension)
{
	if (directiveSet(CGI_EXTENSION)) {
		throw std::runtime_error("Multiple cgi_extension directives");
	}
	this->is_set.insert(CGI_EXTENSION);
	this->cgi_extension = cgi_extension;
}

void LocationConfig::setRedirect(const std::pair<int, std::string>& redirect)
{
	if (directiveSet(REDIRECT)) {
		return;
	}
	if (directiveSet(ALLOW_METHOD)
		&& (allow_method.find("GET") == allow_method.end() || allow_method.size() > 1)) {
			throw std::runtime_error("Redirect only allowed with GET");
	}
	this->is_set.insert(REDIRECT);
	this->redirect = redirect;
}

void LocationConfig::setUploadFilepath(const std::string &upload_filepath)
{
	if (directiveSet(UPLOAD_FILEPATH)) {
		throw std::runtime_error("Multiple upload_filepath directives");
	}
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

bool LocationConfig::getAutoIndex() const
{
	return this->autoindex;
}

const std::set<std::string> &LocationConfig::getAllowMethod() const
{
	return this->allow_method;
}

const std::vector<std::string> &LocationConfig::getIndex() const
{
	return this->index;
}

const std::pair<std::string, std::string> &LocationConfig::getCgiExtension() const
{
	return this->cgi_extension;
}

const std::pair<int, std::string> &LocationConfig::getRedirect() const
{
	return this->redirect;
}

const std::string &LocationConfig::getUploadFilepath() const
{
	return this->upload_filepath;
}

void	LocationConfig::print() const {
	std::cout << "uri: " << uri << std::endl;
	std::cout << "alias: " << alias << std::endl;
	std::cout << "autoindex: " << (autoindex == true ? "true" : "false") << std::endl;
	std::cout << "allow_method: ";
	for (std::set<std::string>::iterator it = allow_method.begin(); it != allow_method.end(); ++it) {
		std::cout << *it << ' ';
	}
	std::cout << std::endl;
	std::cout << "index: ";
	for (std::vector<std::string>::const_iterator it = index.begin(); it != index.end(); ++it) {
		std::cout << *it << ' ';
	}
	std::cout << std::endl;
	std::cout << "cgi_extension: " << cgi_extension.first << " " << cgi_extension.second << std::endl;
	std::cout << "redirect: " << redirect.first << " " << redirect.second << std::endl;
	std::cout << "upload_filepath: " << upload_filepath << std::endl;
}

bool	LocationConfig::directiveSet(E_DirectiveType directive) {
	return (is_set.find(directive) != is_set.end());
}
