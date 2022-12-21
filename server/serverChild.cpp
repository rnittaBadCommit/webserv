#include "serverChild.hpp"
#include <iostream>
namespace ft
{

	ServerChild::ServerChild()
		: server_config_(ServerConfig())
	{
	}

	ServerChild::ServerChild(const ServerConfig &server_config)
		: server_config_(server_config)
	{
		std::map<std::string, LocationConfig>::const_iterator itend = server_config.getLocationConfig().end();
		for (std::map<std::string, LocationConfig>::const_iterator it = server_config.getLocationConfig().begin(); it != itend; ++it)
		{
			LocationConfig location_config = (*it).second;
			if (location_config.getRedirect().first != LocationConfig::NO_REDIRECT)
			{ // LocationConfig にredirectが設定されている
				std::pair<int, const std::string> tmp = location_config.getRedirect();
				const std::string &redirect_uri = location_config.getUri();
				redirectList_map_[redirect_uri].uri = redirect_uri;
				redirectList_map_[redirect_uri].status_code = tmp.first;
				redirectList_map_[redirect_uri].dest_uri = tmp.second;
			}
		}
	}

	bool ServerChild::is_redirect_(const std::string &url)
	{

		// std::cout <<"url" <<url << std::endl;
		// std::cout <<"url.dest" << redirectList_map_[url].dest_uri << std::endl;
		// std::cout << redirectList_map_["/redirect/"].dest_uri << std::endl;
		std::map<std::string, redirectConf>::const_iterator it = redirectList_map_.upper_bound(url);
		if (it == redirectList_map_.begin())
			return (false);
		--it;
		if ((*it).second.uri.compare(0, (*it).second.uri.size(), url, 0, (*it).second.uri.size()) == 0)
			return (true);
		return (false);
	}

} // namespace ft
