#include "server.hpp"

int main()
{
	std::vector<in_port_t> port_vec;

	port_vec.push_back(8080);
	ft::Server server(port_vec);
	server.start_server();
}
