#ifndef FT_SOCKET_HPP
#define FT_SOCKET_HPP

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <cstring>
#include <poll.h>
#include <time.h>

#include <errno.h>
#include <stdio.h>

#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <fcntl.h>

#include "../config/Config.hpp"

#define BUFFER_SIZE 10

namespace ft
{

	class Socket
	{
	public:
		// canonical
		Socket();
		virtual ~Socket();

		class RecievedMsg
		{
		public:
			RecievedMsg();
			RecievedMsg(const RecievedMsg& src);
			RecievedMsg operator=(const RecievedMsg &other);
			RecievedMsg(const std::string content, const int client_id, in_port_t port, size_t i_poll_fd);
			~RecievedMsg();
			std::string content;
			int client_id;
			in_port_t port;
			size_t i_poll_fd;
		};

		void setup(const std::vector<ServerConfig> &server_config);

		RecievedMsg recieve_msg();

		void send_msg(int fd, const std::string msg);

		std::vector<int>& check_keep_time_and_close_fd();

		void close_fd_(const int fd, const int i_poll_fd);

		class SetUpFailException : public std::exception
		{
		public:
			SetUpFailException(const std::string err_msg);
			virtual ~SetUpFailException() throw();
			const char *what() const throw();
			const std::string err_msg;
		};

		class RecieveMsgException : public std::exception
		{
		public:
			const char *what() const throw();
		};

		class recieveMsgFromNewClient : public std::exception
		{
		public:
			recieveMsgFromNewClient(const int client_id);
			const int client_id;
		};

		class connectionHangUp : public std::exception
		{
		public:
			connectionHangUp(const int client_id);
			const int client_id;
		};

		class NoRecieveMsg : public std::exception
		{
		};

	private:
		Socket(const Socket& src);
		Socket& operator=(const Socket& rhs);

		std::vector<int> sockfd_vec_;
		std::vector<int> closedfd_vec_;
		std::vector<struct pollfd> poll_fd_vec_;
		std::map<int, time_t> last_recieve_time_map_; // sockfd => -1
		std::map<int, std::string> msg_to_send_map_;
		std::map<int, in_port_t> fd_to_port_map_;

		std::set<int> used_fd_set_;

		time_t keep_connect_time_len_;

		RecievedMsg recieve_msg_from_connected_client_(int connection, size_t i_poll_fd);
		void register_new_client_(int sock_fd);
	
		void closeAllSocket_();
		void set_sockaddr_(struct sockaddr_in &server_sockaddr, const char *ip, const in_port_t port);
		void set_nonblock_(int fd);
	};

}

#endif
