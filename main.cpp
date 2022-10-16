#include "srcs/socket/server.hpp"
#include <fstream>
int main()
{
	ft::HTTPRequest Req;	
	Req.CreateFile("test.txt");
	/*ft::Server server("config/hoge.conf");

	server.start_server();*/
	return 0;
}
