#include "Cgi.hpp"

namespace ft
{

	Cgi::Cgi(const std::string cgi_path)
		: cgi_path_(cgi_path)
	{
		argv.push_back(NULL);
		envp.push_back(NULL);
	}

	void Cgi::run(const int fd)
	{
		if (pipe(pipefd) == -1)
			throw std::runtime_error("Cgi: pipe fail");

		pid_t pid = fork();

		if (pid == 0)
			run_cgi();
		else if (pid == -1)
			throw std::runtime_error("Cgi: fork fail");

		close(pipefd[1]);
	}

	void Cgi::run_cgi()
	{
		close(pipefd[0]);
		dup2(1, pipefd[1]);
		close(pipefd[1]);
		execve(cgi_path_.c_str(), argv.data(), envp.data());
	}

} // namespace ft
