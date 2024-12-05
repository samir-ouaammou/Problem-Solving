#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>

int	main(int ac, char **av)
{	
	if (ac < 2)
		return (0);
	
	char	*str;
	pid_t	pid;	
	
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
		int status;
        	waitpid(pid, &status, 0);
		wait(NULL);
		execve(str, av, NULL);
	}
	
	return (0);
}
