#include "serverChild.hpp"

namespace ft
{

	ServerChild::ServerChild(const ServerConfig &server_config)
		: server_config_(server_config)
	{
		std::map<std::string, LocationConfig>::const_iterator itend = server_config.getLocationConfig().end();
		for (std::map<std::string, LocationConfig>::const_iterator it = server_config.getLocationConfig().begin(); it != itend; ++it)
		{
			LocationConfig location_config = (*it).second;
			if (!location_config.getRedirect().first != LocationConfig::NO_REDIRECT)
			{ // LocationConfig にredirectが設定されている
				redirectList_map_[location_config.getUri()] = location_config.getRedirect();
			}
		}
	}

	bool ServerChild::is_redirect_(const std::string &url)
	{
		std::map<std::string, redirectConf>::const_iterator it = redirectList_map_.upper_bound(url);
		if ((*it).second.uri.compare(0, (*it).second.uri.size(), url) == 0)
			return (true);
		return (false);
	}

} // namespace ft
