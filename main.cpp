#include "srcs/socket/server.hpp"
#include "srcs/utils.hpp"

int main()
{	
	/*std::set<std::string> lst = ft::CreateDirectoryList("/home/aurora/webserv");
	for (std::set<std::string>::iterator it = lst.begin(); it != lst.end(); ++it) {
		std::cout << *it << ' ';
	}
	std::cout << std::endl;*/
	ft::Server server("config/hoge.conf");

	server.start_server();
	return 0;
}
