#ifndef SERVERCHILD_HPP
#define SERVERCHILD_HPP

#include "../srcs/config/Config.hpp"

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
		ServerChild(const ServerConfig &server_config);

	private:
		const ServerConfig &server_config_;
		const std::map<const std::string, redirectConf> redirectList_map_;

		bool is_redirect_(const std::string &url);
	};
}

#endif
