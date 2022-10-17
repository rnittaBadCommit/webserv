#include "srcs/socket/server.hpp"
#include "srcs/utils.hpp"

int main()
{	
	try {
		ft::CreateFile("/home/aurora/webserv/dira/dirb/dirc/HEYTHERE", "This file is in the previous directory");
	} catch(const std::exception& e) {
		std::cout << "[exception]: " << e.what() << std::endl;
	}
	
	/*std::set<std::string> lst = ft::CreateDirectoryList("/home/aurora/webserv");
	for (std::set<std::string>::iterator it = lst.begin(); it != lst.end(); ++it) {
		std::cout << *it << ' ';
	}
	std::cout << std::endl;*/
	/*ft::Server server("config/hoge.conf");

	server.start_server();*/
	return 0;
}
