#include <sys/types.h>
#include <unistd.h>
int main()
{
	int pipefd[2];
	pipe(pipefd);
	pid_t pid = fork();
	dup2(1, 3);

	if (pid == 0)
	{
	
	}
}