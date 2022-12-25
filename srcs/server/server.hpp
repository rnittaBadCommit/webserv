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

		Server(const std::string config_path);
		~Server();

		void start_server();
		void print_server_config();

	private:
		Server();
		Server(const Server& src);
		Server& operator=(const Server&rhs);

		std::vector<ServerConfig>	server_config_;
		Socket 						socket_;
		ServerChildMap			serverChild_map_;
		DefaultServerChildMap	default_serverChild_map_;
		std::map<int, HTTPRequestPair>	httpRequest_pair_map_;

		void create_serverChild_map_();
		void import_config_(const std::string config_path);
		bool recieve_request_();
		ServerChild&	decide_serverChild_config_(const std::string& host, in_port_t port);
		void remove_timeout_clients_();
		void process_msg_(ServerChild& serverChild, const Socket::RecievedMsg& recieved_msg);

		void print_debug_(const Socket::RecievedMsg& recieved_msg);

	};

}
#endif
