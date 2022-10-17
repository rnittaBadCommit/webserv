#include "server.hpp"

namespace ft
{
	Server::Server(const std::string config_path)
	{
		import_config_(config_path);

		socket_.setup(config_.getServerConfig());
	}

	void Server::start_server()
	{
		while (1)
		{
			if (recieve_request_())
			{
			}
		}
	}

	void Server::import_config_(const std::string config_path)
	{
		ConfigParser configParser;
		config_ = configParser.readFile(config_path);
	}

	void setup_()
	{
	}

	bool Server::recieve_request_()
	{
		Socket::RecievedMsg recieved_msg;

		try
		{
			recieved_msg = socket_.recieve_msg();
			// if (http_request_map_.count(recieved_msg.client_id))
			httpRequest_map_[recieved_msg.client_id] = recieved_msg.content;
			std::cout << "===============================" << std::endl
					  << httpRequest_map_[recieved_msg.client_id] << std::endl
					  << "===============================" << std::endl;
			if (!HTTPRequest_vec_[recieved_msg.client_id].Parse(recieved_msg.content))
			{
				std::cout << "REQUEST SUCCESSFULLY RECEIVED" << std::endl;
				std::cout << "request: " << std::endl;
				HTTPRequest_vec_[recieved_msg.client_id].PrintRequest();
				std::cout << "body: " << std::endl;
				HTTPRequest_vec_[recieved_msg.client_id].PrintBody();
			}
			return (true);
		}
		catch (const ft::Socket::recieveMsgFromNewClient &new_client)
		{
			httpRequest_map_[new_client.client_id];
		}
		catch (const ft::Socket::connectionHangUp &deleted_client)
		{
			httpRequest_map_.erase(deleted_client.client_id);
		}
		catch (const ft::Socket::NoRecieveMsg &e)
		{
			std::cerr << "no msg recieved" << std::endl;
		}
		catch (const std::exception &e)
		{
			std::cerr << e.what() << std::endl;
			// std::cerr << "Error: undetermined" << std::endl;
			exit(1);
		}

		return (false);
	}
}
