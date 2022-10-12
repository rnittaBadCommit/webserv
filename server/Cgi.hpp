#ifndef CGI_HPP
# define CGI_HPP

# include <iostream>
#include <sys/types.h>
#include <unistd.h>

namespace ft
{
	

class Cgi
{
	public:
		Cgi();
		Cgi(const std::string cgi_path);
		void run(const int fd);

	private:
		std::string cgi_path_;
		int pipefd[2];

		void run_cgi(const int fd);
};


} // namespace ft


#endif
