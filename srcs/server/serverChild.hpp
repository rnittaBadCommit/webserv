#ifndef SERVERCHILD_HPP
#define SERVERCHILD_HPP

#include "../config/Config.hpp"
#include "Location.hpp"
#include <map>

namespace ft
{
	class ServerChild
	{

	public:
		typedef struct
		{
			std::string uri;
			int status_code;
			std::string dest_uri;
		} redirectConf;
		// typedef std::pair<const int, const std::string> redirectConf;
		ServerChild();
		ServerChild(const ServerConfig &server_config);
		bool is_redirect_(const std::string &url);

	private:
		const ServerConfig &server_config_;
		std::map<const std::string, Location> location_map_;
		std::map<const std::string, redirectConf> redirectList_map_;
	};
}

#endif
