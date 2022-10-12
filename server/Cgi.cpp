#include "Cgi.hpp"

namespace ft
{


Cgi::Cgi()
{

}

Cgi::Cgi(const std::string cgi_path)
: cgi_path_(cgi_path)
{

}

void Cgi::run(const int fd)
{
	if (pipe(pipefd) == -1)
		throw std::runtime_error("pipe fail");
	
	pid_t	pid = fork();
	
	if (pid == 0)
		run_cgi(fd);
	else if (pid == -1)
		throw std::runtime_error("fork fail");
}

void Cgi::run_cgi(const int fd)
{

}

} // namespace ft

