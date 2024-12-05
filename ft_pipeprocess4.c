#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>

int	main(int ac, char **av)
{
	pid_t	pid;
	char	*str;

	if (ac < 3)	
		return (0);
	str = av[1];
	av = &av[2];

	pid = fork();
	if (pid < 0)
		return (printf("Error (%s)\n", strerror(errno)), 0);
	if (pid == 0)
	{
		execve(str, av, NULL);
	}
	else
	{
		if (access(str, F_OK) != 0)
			return (printf("Error (%s)\n", strerror(errno)), 0);
		if (access(str, X_OK) != 0)
			return (printf("Error (%s)\n", strerror(errno)), 0);
	}


	return (0);
}
