

#include "serverChild.hpp"
#include "server.hpp"

#define CONFIG_PATH "../config/hoge.conf"

int main()
{

		ConfigParser configParser;
		Config config_ = configParser.readFile(CONFIG_PATH);

		ft::ServerChild serverChild(config_.getServerConfig()[0]);
		std::cout << serverChild.is_redirect_("/redirect/") << std::endl;
		std::cout << serverChild.is_redirect_("/redirect/abc") << std::endl;
		std::cout << serverChild.is_redirect_("/redirect/abc/def") << std::endl;
		std::cout << serverChild.is_redirect_("/redirecta/") << std::endl;
		std::cout << serverChild.is_redirect_("/redirect") << std::endl;
		std::cout << serverChild.is_redirect_("") << std::endl;

}

