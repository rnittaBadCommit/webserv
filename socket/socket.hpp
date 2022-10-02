#ifndef FT_SOCKET_HPP
#define FT_SOCKET_HPP

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

namespace ft
{

	class ft_socket
	{
	public:
		// canonical
		ft_socket();
		// socket(const socket &other);
		virtual ~ft_socket();
		// socket &operator=(const socket &other);

		// other constructors
		ft_socket(const char *ip_address, const in_port_t port);

	private:
		int sockfd_;
		struct sockaddr_in server_sockaddr_;
		std::vector<struct pollfd> poll_fd_vec;

		void tmp_();

		void closeSocket_();
		void set_sockaddr_(const char *ip, const in_port_t port);
	};

}

#endif
