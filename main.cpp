#include "srcs/server/server.hpp"

int main(int argc, char** argv)
{
	if (argc == 2) {
		try {
			ft::Server server(argv[1]);
			server.start_server();	
		} catch (const std::exception& e) {		
			std::cout << "[exception]: " << e.what() << std::endl;
		}
	}
	return 0;
}
