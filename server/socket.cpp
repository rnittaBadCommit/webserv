
// #define _GNU_SOURCE   // 一部のオペレーティング・システムでは、_GNU_SOURCEの定義は不要。(https://docs.oracle.com/cd/E39368_01/porting/ch03s06.html)
#include "socket.hpp"

namespace ft
{
	Socket::Socket()
	{
	}

	Socket::~Socket()
	{
		closeAllSocket_();
	}

	Socket::RecievedMsg::RecievedMsg()
		: content(""), client_id(0)
	{
	}

	Socket::RecievedMsg::RecievedMsg(const std::string content, const int client_id)
		: content(content), client_id(client_id)
	{
	}

	Socket::RecievedMsg Socket::RecievedMsg::operator=(const Socket::RecievedMsg &other)
	{
		if (this == &other)
			return (*this);

		content = other.content;
		client_id = other.client_id;
		return (*this);
	}

	void Socket::setup(const std::vector<ServerConfig> &server_config_vec)
	{
		struct sockaddr_in server_sockaddr;
		struct pollfd poll_fd;

		for (size_t i = 0; i < server_config_vec.size(); ++i)
		{
			sockfd_vec_.push_back(socket(AF_INET, SOCK_STREAM, 0));
			if (sockfd_vec_.back() < 0)
				throw SetUpFailException("Error: socket()");
			
			set_sockaddr_(server_sockaddr, "127.0.0.1", server_config_vec[i].getListen());
			std::cout << "127.0.0.1" << " " << server_config_vec[i].getListen() << std::endl;

			if (bind(sockfd_vec_.back(), (struct sockaddr *)&server_sockaddr,
						sizeof(server_sockaddr)) < 0)
				throw SetUpFailException("Error: bind()");

			if (listen(sockfd_vec_.back(), SOMAXCONN) < 0)
				throw SetUpFailException("Error: listen()");

			poll_fd.fd = sockfd_vec_.back();
			poll_fd.events = POLLIN;
			poll_fd.revents = 0;
			poll_fd_vec_.push_back(poll_fd);

			last_recieve_time_map_[sockfd_vec_.back()] = -1;
		}
	}

	Socket::RecievedMsg	Socket::recieve_msg()
	{
		std::cout << "poll_fd_vec_.size(): " << poll_fd_vec_.size() << std::endl;
		check_keep_time_and_close_fd();
		poll(&poll_fd_vec_[0], poll_fd_vec_.size(), 1000);
		for (size_t i = 0; i < poll_fd_vec_.size(); ++i)
		{
			if (poll_fd_vec_[i].revents & POLLERR)
			{
				close_fd_(poll_fd_vec_[i].fd, i);
				poll_fd_vec_.erase(poll_fd_vec_.begin() + i);
				throw connectionHangUp(poll_fd_vec_[i].fd);
			}
			else if (poll_fd_vec_[i].revents & POLLHUP)
			{
				close_fd_(poll_fd_vec_[i].fd, i);
				poll_fd_vec_.erase(poll_fd_vec_.begin() + i);
				throw connectionHangUp(poll_fd_vec_[i].fd);
			}
			else if (poll_fd_vec_[i].revents & POLLRDHUP)
			{
				close_fd_(poll_fd_vec_[i].fd, i);
				poll_fd_vec_.erase(poll_fd_vec_.begin() + i);
				throw connectionHangUp(poll_fd_vec_[i].fd);
			}
			else if (poll_fd_vec_[i].revents & POLLIN)
			{
				poll_fd_vec_[i].revents = 0;
				if (used_fd_set_.count(poll_fd_vec_[i].fd))
				{
					poll_fd_vec_[i].revents = 0;
					return (recieve_msg_from_connected_client_(poll_fd_vec_[i].fd));
				}
				else
				{
					register_new_client_(poll_fd_vec_[i].fd);
					poll_fd_vec_[i].revents = 0;
					poll_fd_vec_[i].events = POLLIN | POLLERR;
					throw recieveMsgFromNewClient(poll_fd_vec_[i].fd);
				}
			}
		}
		// throw recieveMsgException();	// pollにタイムアウトを設定するので除外
		throw NoRecieveMsg();
	}

	void Socket::check_keep_time_and_close_fd()
	{
		time_t current_time = time(NULL);
		time_t tmp_last_recieve_time;

		for (size_t i = 0; i < poll_fd_vec_.size(); ++i)
		{
			tmp_last_recieve_time = last_recieve_time_map_[poll_fd_vec_[i].fd];
			if (tmp_last_recieve_time != (time_t)-1)
			{ // fd made by accept(), not sockfd
				if (current_time - tmp_last_recieve_time > keep_connect_time_len_)
					close_fd_(poll_fd_vec_[i].fd, i);
			}
		}
	}

	void Socket::register_new_client_(int sock_fd)
	{
		int connection = accept(sock_fd, NULL, NULL);
		if (connection < 0)
			throw SetUpFailException("Error: accept()");

		struct pollfd poll_fd;
		poll_fd.fd = connection;
		poll_fd.events = POLLIN | POLLRDHUP;
		poll_fd.revents = 0;
		poll_fd_vec_.push_back(poll_fd);
		used_fd_set_.insert(connection);

		last_recieve_time_map_[connection] = time(NULL);
	}

	Socket::RecievedMsg Socket::recieve_msg_from_connected_client_(int connection)
	{
		char buf[BUFFER_SIZE + 1];

		last_recieve_time_map_[connection] = time(NULL);
		int recv_ret = recv(connection, buf, BUFFER_SIZE, 0);
		buf[recv_ret] = '\0';
		return (RecievedMsg(std::string(buf), connection));
	}

	void Socket::close_fd_(const int fd, const int i_poll_fd)
	{
		close(fd);
		poll_fd_vec_.erase(poll_fd_vec_.begin() + i_poll_fd);
		used_fd_set_.erase(fd);
		throw connectionHangUp(fd);
	}

	void Socket::closeAllSocket_()
	{
		for (size_t i = 0; i < port_num_; ++i)
			close(poll_fd_vec_[i].fd);
		used_fd_set_.clear();
	}

	void Socket::set_sockaddr_(struct sockaddr_in &server_sockaddr, const char *ip, const in_port_t port)
	{
		memset(&server_sockaddr, 0, sizeof(struct sockaddr_in));
		server_sockaddr.sin_family = AF_INET;
		server_sockaddr.sin_port = htons(port);
		server_sockaddr.sin_addr.s_addr = inet_addr(ip);
	}

	Socket::SetUpFailException::SetUpFailException(const std::string err_msg)
		: err_msg(err_msg)
	{
	}

	Socket::SetUpFailException::~SetUpFailException() throw()
	{
	}

	const char *Socket::SetUpFailException::what() const throw()
	{
		return (err_msg.c_str());
	}

	const char *Socket::RecieveMsgException::what() const throw()
	{
		return ("Error: recieve msg fail, shouldn't happen");
	}

	Socket::recieveMsgFromNewClient::recieveMsgFromNewClient(const int client_id)
		: client_id(client_id)
	{
	}

	Socket::connectionHangUp::connectionHangUp(const int client_id)
		: client_id(client_id)
	{
	}
}
