#include "srcs/server/server.hpp"

int main()
{
	ft::Server server("config/basic.conf");

	server.start_server();
	return 0;
}
