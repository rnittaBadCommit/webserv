#include "socket.hpp"

namespace ft
{
	ft_socket::ft_socket()
	: port_num_(1)
	{
	}

	ft_socket::~ft_socket()
	{
		closeAllSocket_();
	}

	ft_socket::ft_socket(const char *ip_address, const std::vector<in_port_t>  port_vec)
	: port_num_(port_vec.size())
	{
		// initialize_();

		for (size_t i = 0; i < port_num_; ++i)
		{
			sockfd_vec_.push_back(socket(AF_INET, SOCK_STREAM, 0));
			if (sockfd_vec_.back() < 0)
			{
				std::cout << "Error: socket(), i: " << i << std::endl;
				exit(1);
				throw std::exception();
			}
			
			struct sockaddr_in server_sockaddr;
			set_sockaddr_(server_sockaddr, ip_address, port_vec[i]);
			if (bind(sockfd_vec_.back(), (struct sockaddr *)&server_sockaddr, 
						sizeof(server_sockaddr)) < 0)
			{
				std::cout << "Error: bind(), i: " << i << std::endl;
				exit(1);		
				throw std::exception();
			}

			if (listen(sockfd_vec_.back(), SOMAXCONN) < 0)
			{
				std::cout << "Error: listen(), i: " << i << std::endl;
				exit(1);
				throw std::exception();
			}

			struct pollfd poll_fd;
			poll_fd.fd = sockfd_vec_.back();
			poll_fd.events = POLLIN;
			poll_fd.revents = 0;
			poll_fd_vec_.push_back(poll_fd);
		}
		std::cout << "poll_fd_vec_.size(): " << poll_fd_vec_.size() <<  std::endl;
		
		poll(&poll_fd_vec_[0], poll_fd_vec_.size(), -1);
		std::cout << "poll done" << std::endl;
	}

	void ft_socket::initialize_()
	{
		poll_fd_vec_.reserve(port_num_);
		recieve_fd_vec_.reserve(port_num_);
	}

	std::string	ft_socket::recieve_msg()
	{
		for (size_t i = 0; i < port_num_; ++i)
		{
			if (poll_fd_vec_[i].revents & POLLIN)
			{
				std::cout << "msg recieved" << std::endl;
				#define BUFFER_SIZE 10
				char buf[BUFFER_SIZE + 1];
				struct sockaddr_in client_sockaddr;
				socklen_t client_sockaddr_len;

				int recieve_fd = accept(poll_fd_vec_[i].fd, 
										(struct sockaddr *)&client_sockaddr,
										&client_sockaddr_len);
				if (recieve_fd < 0)
				{
					std::cout << "Error: accept()" << std::endl;
					exit(1);
					throw std::exception();
				}

				int recv_ret = recv(recieve_fd, buf, BUFFER_SIZE, 0);
				buf[recv_ret] = '\0';
				return (std::string(buf));
			}
		}
		throw std::exception();
	}

// 	void ft_socket::tmp_()
// 	{
// 		struct pollfd poll_fd;

// 		poll_fd.fd = sockfd_;
// 		poll_fd.events = POLLIN;
// 		poll_fd.revents = 0;
// 		poll_fd_vec.push_back(poll_fd);

// #define BUFFER_SIZE 10
// 		char buf[BUFFER_SIZE + 1];
// 		struct sockaddr_in client_sockaddr;
// 		socklen_t client_sockaddr_len;
// 		while (1)
// 		{
// 			poll(&poll_fd_vec[0], poll_fd_vec.size(), -1);
// 			if (poll_fd_vec[0].revents & POLLIN)
// 			{
// 				std::cout << "request recieved" << std::endl;
// 				int connect = accept(sockfd_, (struct sockaddr *)&client_sockaddr, &client_sockaddr_len);
// 				if (connect < 0)
// 				{
// 					std::cout << "Error: accept()" << std::endl;
// 					exit(1);
// 				}
// 				int recv_ret = recv(connect, buf, BUFFER_SIZE, 0);
// 				buf[recv_ret] = '\0';
// 				std::cout << "====================" << std::endl
// 						  << buf;

// 				int read_sum = recv_ret;
// 				while (recv_ret == BUFFER_SIZE)
// 				{
// 					recv_ret = recv(connect, buf, BUFFER_SIZE, MSG_DONTWAIT);
// 					if (recv_ret > 0)
// 						read_sum += recv_ret;
// 					else
// 					{
// 						perror(NULL);
// 					}
// 					buf[recv_ret] = '\0';
// 					// std::cout << buf;
// 					printf("%s", buf);
// 				}
// 				std::cout << std::endl
// 						  << "====================" << std::endl
// 						  << "read: " << read_sum << "byte, done" << std::endl;
// 				send(connect, "HTTP/1.1 200 OK\nContent-Length: 11\nContent-Type: text/html\n\nHello World", 71, 0);
// 				usleep(1000);
// 				close(connect);
// 			}
// 		}
// 	}

	void ft_socket::closeAllSocket_()
	{
		for (size_t	i = 0; i < port_num_; ++i)
			close(poll_fd_vec_[i].fd);
	}

	void ft_socket::set_sockaddr_(struct sockaddr_in &server_sockaddr, const char *ip, const in_port_t port)
	{
		memset(&server_sockaddr, 0, sizeof(struct sockaddr_in));
		server_sockaddr.sin_family = AF_INET;
		server_sockaddr.sin_port = htons(port);
		server_sockaddr.sin_addr.s_addr = inet_addr(ip);
	}
}
