#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int	main(int ac, char **av)
{
	char	*str;
	pid_t	pid;
	int		status;

	if (ac < 2)
		return (0);
	pid = fork();
	if (pid < 0)
		return (0);
	if (pid == 0)
	{
		str = av[1];
		av = &av[2];
	}
	else
	{
		waitpid(pid, &status, 0);
		wait(NULL);
		execve(str, av, NULL);
	}
	return (0);
}
