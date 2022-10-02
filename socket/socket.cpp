#include "socket.hpp"

namespace ft
{
	ft_socket::ft_socket()
	{
	}

	ft_socket::~ft_socket()
	{
		closeSocket_();
	}

	ft_socket::ft_socket(const char *ip_address, const in_port_t port)
	{
		sockfd_ = socket(AF_INET, SOCK_STREAM, 0);
		if (sockfd_ < 0)
			throw std::exception();

		set_sockaddr_(ip_address, port);

		if (bind(sockfd_, (struct sockaddr *)&server_sockaddr_,
				 sizeof(server_sockaddr_)) < 0)
			throw std::exception();

		if (listen(sockfd_, SOMAXCONN) < 0)
			throw std::exception();

		ft_socket::tmp_();
	}

	void ft_socket::tmp_()
	{
		struct pollfd poll_fd;

		poll_fd.fd = sockfd_;
		poll_fd.events = POLLIN;
		poll_fd.revents = 0;
		poll_fd_vec.push_back(poll_fd);

#define BUFFER_SIZE 10
		char buf[BUFFER_SIZE + 1];
		struct sockaddr_in client_sockaddr;
		socklen_t client_sockaddr_len;
		while (1)
		{
			poll(&poll_fd_vec[0], poll_fd_vec.size(), -1);
			if (poll_fd_vec[0].revents & POLLIN)
			{
				std::cout << "request recieved" << std::endl;
				int connect = accept(sockfd_, (struct sockaddr *)&client_sockaddr, &client_sockaddr_len);
				if (connect < 0)
				{
					std::cout << "Error: accept()" << std::endl;
					exit(1);
				}
				int recv_ret = recv(connect, buf, BUFFER_SIZE, 0);
				buf[recv_ret] = '\0';
				std::cout << "====================" << std::endl
						  << buf;

				int read_sum = recv_ret;
				while (recv_ret == BUFFER_SIZE)
				{
					recv_ret = recv(connect, buf, BUFFER_SIZE, MSG_DONTWAIT);
					if (recv_ret > 0)
						read_sum += recv_ret;
					else
					{
						perror(NULL);
					}
					buf[recv_ret] = '\0';
					// std::cout << buf;
					printf("%s", buf);
				}
				std::cout << std::endl
						  << "====================" << std::endl
						  << "read: " << read_sum << "byte, done" << std::endl;
				send(connect, "HTTP/1.1 200 OK\nContent-Length: 11\nContent-Type: text/html\n\nHello World", 71, 0);
				usleep(1000);
				close(connect);
			}
		}
	}

	void ft_socket::closeSocket_()
	{
		close(sockfd_);
	}

	void ft_socket::set_sockaddr_(const char *ip, const in_port_t port)
	{
		memset(&server_sockaddr_, 0, sizeof(struct sockaddr_in));
		server_sockaddr_.sin_family = AF_INET;
		server_sockaddr_.sin_port = htons(port);
		server_sockaddr_.sin_addr.s_addr = inet_addr(ip);
	}
}
