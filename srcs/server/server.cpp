#include "server.hpp"

namespace ft
{
	Server::Server(const std::string config_path)
	{
		import_config_(config_path);

		socket_.setup(server_config_);
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
		server_config_ = configParser.readFile(config_path).getServerConfig();
	}

	void Server::create_serverChild_map_()
	{
		std::vector<ServerConfig>::const_iterator end = server_config_.begin();
		for (std::vector<ServerConfig>::const_iterator it = server_config_.begin(); it != end; ++it)
		{
			std::pair<std::string, in_port_t> key_to_insert = std::make_pair((*it).getServerName(), (in_port_t)(*it).getListen());
			serverChild_map_.insert(std::make_pair(key_to_insert, ServerChild(*it)));
			if (default_serverChild_map_.count((in_port_t)(*it).getListen()))
				default_serverChild_map_.insert(std::make_pair((in_port_t)(*it).getListen(), (*(serverChild_map_.find(key_to_insert))).second));
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
			recieved_msg = socket_.recieve_msg();
			//socket_.send_msg(recieved_msg.client_id, "HTTP/1.1 200 OK\nContent-Length: 11\nContent-Type: text/html\n\nHello World");
			//if (cd)
			httpRequest_map_[recieved_msg.client_id] = recieved_msg.content;
			std::cout << "===============================" << std::endl
					  << httpRequest_map_[recieved_msg.client_id] << std::endl
					  << "===============================" << std::endl;

			HTTPHead& head = httpRequest_pair_map_[recieved_msg.client_id].first;
			ServerChild& serverChild = httpRequest_pair_map_[recieved_msg.client_id].second;

			if (head.GetParseStatus() != complete) {
				if (head.Parse(recieved_msg.content) == 0) {
					std::cout << "HEADER RECIEVED\n";
					head.PrintRequest();
					head.ParseRequestURI();
					serverChild = decide_serverChild_config_(head.GetHost(), recieved_msg.port);
					serverChild.SetUp(head);
					serverChild.Parse("");
				}
			} else if (serverChild.get_parse_status() != complete) {
				serverChild.Parse(recieved_msg.content);
			}
			if (serverChild.get_parse_status() == complete) {
				std::cout << "BODY RECEIVED: ";
				serverChild.PrintBody();
				// complete request
				httpRequest_pair_map_.erase(recieved_msg.client_id);
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
			std::cerr << "Error: undetermined" << e.what() << std::endl;
			exit(1);
		}

		return (false);
	}

	void run_cgi()
	{
	}

	ServerChild& Server::decide_serverChild_config_(const std::string& host, in_port_t port) {
        ServerChildMap::iterator confIt = serverChild_map_.find(std::make_pair(host, port));

        if (confIt != serverChild_map_.end()) {
            return (confIt->second);
        } else {
            return (default_serverChild_map_.find(port)->second);
        }

	}
}
