#ifndef CGI_HPP
#define CGI_HPP

#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <vector>

namespace ft
{

	class Cgi
	{
	public:
		Cgi(const std::string cgi_path);
		void run(/*const int fd*/);

	private:
		const std::string cgi_path_;
		int pipefd[2];
		std::vector<char *> argv;
		std::vector<char *> envp;

		void run_cgi();
	};

} // namespace ft

#endif
