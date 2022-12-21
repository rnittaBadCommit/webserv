#include "socket.hpp"
#include <map>
int main()
{
	std::vector<in_port_t> port_vec;

	port_vec.push_back(8080);
	port_vec.push_back(8081);
	port_vec.push_back(8082);

	std::map<int, std::string> http_request_map;
	ft::Socket::RecievedMsg recieved_msg;

	// port_vec.push_back(8081);
	try
	{
		ft::Socket socket("127.0.0.1", port_vec, 10);

		while (1)
		{
			try
			{
				recieved_msg = socket.recieve_msg();
				http_request_map[recieved_msg.client_id] += recieved_msg.content;
				std::cout << "===============================" << std::endl
						  << http_request_map[recieved_msg.client_id] << std::endl
						  << "===============================" << std::endl;
				;
			}
			catch (const ft::Socket::recieveMsgFromNewClient &new_client)
			{
				http_request_map[new_client.client_id];
			}
			catch (const ft::Socket::connectionHangUp &deleted_client)
			{
				http_request_map.erase(deleted_client.client_id);
			}
			catch (const ft::Socket::NoRecieveMsg &e)
			{
				std::cerr << "no msg recieved" << std::endl;
			}
			catch (const std::exception &e)
			{
				std::cerr << "Error: undetermined" << std::endl;
			}
		}
	}
	catch (const ft::Socket::SetUpFailException &e)
	{
		std::cerr << e.what() << std::endl;
		return (1);
	}
}
