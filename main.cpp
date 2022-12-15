#include "srcs/server/server.hpp"

int main(int argc, char** argv)
{
	ft::HTTPHead req;
    std::string line = "GET http://example.com/private/index.html HTTP/1.1\r\nhost: hostname\r\n\r\n";

    req.Parse(std::string(line));
	std::cout << "rc: " << req.GetResponseCode() << std::endl;
	std::cout << "host: " << req.GetHost() << std::endl;
	req.ParseRequestURI();
	std::cout << "host: " << req.GetHost() << std::endl;

	return 0;
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
