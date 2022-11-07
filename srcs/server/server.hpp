#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <cstring>
#include <poll.h>

#include <errno.h>
#include <stdio.h>

#include <vector>

#include "socket.hpp"
#include "../config/Config.hpp"
#include "../config/ConfigParser.hpp"
#include "../HTTP/HTTPHead.hpp"
#include "serverChild.hpp"

namespace ft
{

	class Server
	{
	public:
		typedef std::map<std::pair<std::string, in_port_t>, ServerChild>	ServerChildMap;
		typedef std::map<in_port_t, ServerChild>	DefaultServerChildMap;
		typedef std::pair<HTTPHead, ServerChild>	HTTPRequestPair;


		~Server();
		// Server(const std::string conf_path); // custom conf
		Server(const std::vector<in_port_t> port_vec);
		Server(const std::string config_path);
		// Server(const ServerConfig server_config);

		void start_server();

	private:
		Server(); // default conf
		Server(const Server& src);
		Server& operator=(const Server&rhs);

		std::vector<ServerConfig>	server_config_;
		Socket 						socket_;
		ServerChildMap			serverChild_map_;
		DefaultServerChildMap	default_serverChild_map_;
		std::map<int, std::string>		httpRequest_map_;
		std::map<int, HTTPRequestPair>	httpRequest_pair_map_;

		void create_serverChild_map_();
		void import_config_(const std::string config_path);
		void setup_();
		bool recieve_request_();
		void run_cgi_();
		ServerChild&	decide_serverChild_config_(const std::string& host, in_port_t port);
	};

}
#endif
