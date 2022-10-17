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
#include <stdlib.h> //exit()

#include <errno.h>
#include <stdio.h>

#include <vector>

#include "socket.hpp"
#include "../config/Config.hpp"
#include "../config/ConfigParser.hpp"
#include "../HTTP/HTTPRequst.hpp"

namespace ft
{

	class Server
	{
	public:
		Server(); // default conf
		// Server(const std::string conf_path); // custom conf
		Server(const std::vector<in_port_t> port_vec);
		Server(const std::string config_path);
		// Server(const ServerConfig server_config);

		void start_server();

	private:
		Config config_;
		Socket socket_;
		std::map<int, HTTPRequest> HTTPRequest_vec_;

		void import_config_(const std::string config_path);
		void setup_();
		bool recieve_request_();
		std::map<int, std::string> httpRequest_map_;
	};

}
#endif
