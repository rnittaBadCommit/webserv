#ifndef CONFIG_CONSTANT_HPP
#define CONFIG_CONSTANT_HPP

enum E_DirectiveType
{
	SERVER_NAME,
	LISTEN,
	ERROR_PAGE,
	CLIENT_MAX_BODY_SIZE,
	INDEX,
	ALLOW_METHOD,
	REDIRECT,
	ALIAS,
	AUTOINDEX,
	CGI_EXTENSION,
	UPLOAD_FILEPATH,
};

enum E_BlockType
{
	ROOT,
	SERVER,
	LOCATION,
};

#endif