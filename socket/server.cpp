#include "server.hpp"

namespace ft
{

	Server::Server(std::vector<in_port_t> port_vec)
		: socket("127.0.0.1", port_vec, 10)
	{
	}

	void Server::start_server()
	{
		try
		{
			setup_();
		}
		catch (const std::exception &e)
		{
			exit(1);
		}

		while (1)
		{
			if (recieve_request_())
			{
			}
		}
	}

	void setup_()
	{
	}

	bool Server::recieve_request_()
	{
		Socket::RecievedMsg recieved_msg;

		try
		{
			recieved_msg = socket.recieve_msg();
			http_request_map_[recieved_msg.client_id] += recieved_msg.content;
			std::cout << "===============================" << std::endl
					  << http_request_map_[recieved_msg.client_id] << std::endl
					  << "===============================" << std::endl;

			return (true);
		}
		catch (const ft::Socket::recieveMsgFromNewClient &new_client)
		{
			http_request_map_[new_client.client_id];
		}
		catch (const ft::Socket::connectionHangUp &deleted_client)
		{
			http_request_map_.erase(deleted_client.client_id);
		}
		catch (const ft::Socket::NoRecieveMsg &e)
		{
			std::cerr << "no msg recieved" << std::endl;
		}
		catch (const std::exception &e)
		{
			std::cerr << "Error: undetermined" << std::endl;
			exit(1);
		}

		return (false);
	}
}
