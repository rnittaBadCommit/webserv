#include "server.hpp"

namespace ft
{
	Server::Server(const std::string config_path) : server_config_(), socket_(), serverChild_map_(),
		default_serverChild_map_(), httpRequest_map_(), httpRequest_pair_map_()
	{
		import_config_(config_path);
		socket_.setup(server_config_);
		create_serverChild_map_();
	}
	Server::~Server()
	{
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
		//print_server_config();
	}

	void Server::create_serverChild_map_()
	{
		std::vector<ServerConfig>::const_iterator end = server_config_.end();
		for (std::vector<ServerConfig>::const_iterator it = server_config_.begin(); it != end; ++it)
		{
			std::pair<std::string, in_port_t> key_to_insert = std::make_pair((*it).getServerName(), (in_port_t)(*it).getListen());
			serverChild_map_.insert(std::make_pair(key_to_insert, ServerChild(*it)));
			if (default_serverChild_map_.count((in_port_t)(*it).getListen()) == 0)
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
			std::vector<int>& closedfd_vec = socket_.check_keep_time_and_close_fd();
			for (std::vector<int>::iterator it = closedfd_vec.begin(); it != closedfd_vec.end(); ++it) {
				httpRequest_pair_map_.erase(*it);
			}
			closedfd_vec.clear();

			recieved_msg = socket_.recieve_msg();
			std::cout << "port: " << recieved_msg.port << std::endl;
			//socket_.send_msg(recieved_msg.client_id, "HTTP/1.1 200 OK\nContent-Length: 11\nContent-Type: text/html\n\nHello World");
			//if (cd)
			httpRequest_map_[recieved_msg.client_id] = recieved_msg.content;
			std::cout << "===============================" << std::endl
					  << httpRequest_map_[recieved_msg.client_id] << std::endl
					  << "===============================" << std::endl;

			HTTPHead& head = httpRequest_pair_map_[recieved_msg.client_id].first;
			ServerChild& serverChild = httpRequest_pair_map_[recieved_msg.client_id].second;

			try {
				if (head.GetParseStatus() != complete) {
					if (head.Parse(recieved_msg.content) == 0) {
						std::cout << "HEADER RECIEVED\n";
						head.ParseRequestURI();
						head.PrintRequest();
						serverChild = decide_serverChild_config_(head.GetHost(), recieved_msg.port);
						serverChild.SetUp(head);
						if (serverChild.Get_parse_status() != complete)
							serverChild.Parse("");
					}
				} else if (serverChild.Get_parse_status() != complete) {
					serverChild.Parse(recieved_msg.content);
				}
			} catch (const std::exception& e) {
				if (head.GetParseStatus() != complete) {
					serverChild.Set_response_code(head.GetResponseCode());
					serverChild.Set_parse_status(complete);
				}
				std::cout << "error while parsing http request: " << e.what() << std::endl;
			}

			if (serverChild.Get_parse_status() == complete) {
				std::cout << "PATH: " << serverChild.Get_path() << std::endl;
				std::cout << "BODY RECEIVED: ";
				std::cout << serverChild.Get_body() << std::endl;


				// complete request and send response
				
				httpRequest_pair_map_.erase(recieved_msg.client_id);
				if (serverChild.Get_response_code() != 200) {
					socket_.close_fd_(recieved_msg.client_id, recieved_msg.i_poll_fd);
				}
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
			throw std::runtime_error(e.what());
		}

		return (false);
	}

	void run_cgi()
	{
	}

	ServerChild& Server::decide_serverChild_config_(const std::string& host, in_port_t port) {
        ServerChildMap::iterator confIt = serverChild_map_.find(std::make_pair(host, port));

        if (confIt != serverChild_map_.end()) {
			std::cout << "found serverChild by httpRequest host\n";
            return (confIt->second);
        } else {
			std::cout << "could not find serverchild, using default\n";
			DefaultServerChildMap::iterator it = default_serverChild_map_.find(port);
			if (it == default_serverChild_map_.end()) {
				throw std::runtime_error("port does not match any default servers");
			}
            return (it->second);
        }
	}

	void Server::print_server_config() {
		for (std::vector<ServerConfig>::iterator it = server_config_.begin(); it != server_config_.end(); ++it) {
			std::cout << "\t\t-----------SERVER-----------" << std::endl;
			it->print();
			for (std::map<std::string, LocationConfig>::const_iterator lIt = it->getLocationConfig().begin(); lIt != it->getLocationConfig().end(); ++lIt) {
				std::cout << "\t------loc: " << lIt->first << " ------" << std::endl;
				lIt->second.print();
			}
		}
	}
}
