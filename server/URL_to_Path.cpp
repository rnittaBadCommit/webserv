#include "URL_to_Path.hpp"

namespace ft
{
	URL_to_Path::URL_to_Path(const ServerConfig &server_config)
		: location_config_map_(server_config.getLocationConfig())
	{
	}

	const std::string &URL_to_Path::getFilePath(const std::string &url)
	{
	}

	bool URL_to_Path::is_redirect_(const std::string &url)
	{
	}

} // namespace ft
