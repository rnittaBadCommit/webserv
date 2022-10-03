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
#include <set>

#define BUFFER_SIZE 10
#define _GNU_SOURCE
namespace ft
{

	class ft_socket
	{
	public:
		// canonical
		ft_socket();
		virtual ~ft_socket();

		// other constructors
		// ft_socket(const char *ip_address, const in_port_t port);
		ft_socket(const char *ip_address, const std::vector<in_port_t> portvec);

		std::string	recieve_msg();

	private:
		std::vector<int> sockfd_vec_;
		// struct sockaddr_in server_sockaddr_;
		std::vector<struct pollfd> poll_fd_vec_;
		std::vector<int> recieve_fd_vec_;
		const size_t port_num_;

		std::set<int> used_fd_set_;

		std::string recieve_msg_from_connected_client_(int connection);
		void	register_new_client_(int sock_fd);

		void initialize_();
		void tmp_();

		void closeAllSocket_();
		void set_sockaddr_(struct sockaddr_in &server_sockaddr, const char *ip, const in_port_t port);
	};

}

#endif
