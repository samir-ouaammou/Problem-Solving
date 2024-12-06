#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>

int	main(int ac, char **av)
{
	int	fd[2];
	pid_t	pid;
	
	if (ac < 2)
		return (printf("Error (%s)\n", strerror(errno)), 0);
	
	if (pipe(fd) < 0)
		return (-1);
	pid = fork();
	if (pid < 0)
		return (printf("Error (%s)\n", strerror(errno)), -1);
	else if (pid == 0)
	{
		close(fd[0]);
		if (dup2(fd[1], 1) < 0)
			return (printf("Error (%s)\n", strerror(errno)), -1);
		write(fd[1], av[1], strlen(av[1]));
		write (1, "\n", 1);
		close(fd[1]);
		exit(0);
	}
	else
	{
		wait(NULL);
		close(fd[1]);
		if (read(fd[0], av[0], strlen(av[1])) < 0)
			return (printf("Error (%s)\n", strerror(errno)), -1);
		av[0][strlen(av[1])] = '\0';
		close(fd[0]);
		printf("Result: (%s)\n", av[0]);
	}

	return (0);
}
