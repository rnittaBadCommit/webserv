#include "server.hpp"

namespace ft
{

	Server::Server(const std::vector<in_port_t> port_vec)
		: socket_("127.0.0.1", port_vec, 10)
	{
	}

	Server::Server(const std::string config_path)
		: config_()
	{
		import_config_(config_path);

		std::vector<in_port_t> port_vec;
		const std::vector<ServerConfig> &serverConfig = config_.getServerConfig();
		for (size_t i = 0; i < serverConfig.size(); ++i)
		{
			port_vec.push_back(serverConfig[i].getListen());
		}
		socket_("127.0.0.1", port_vec);
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
