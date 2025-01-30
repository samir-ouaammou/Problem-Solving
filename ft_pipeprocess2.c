#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int	main(int ac, char **av)
{
	int		fd[2];
	ssize_t	len;
	pid_t	pid;

	if (ac < 3)
		return (0);
	pid = fork();
	if (pid < 0)
		return (printf("Error (%s)\n", strerror(errno)), 0);
	if (pid == 0)
		write(1, av[1], strlen(av[1]));
	else
	{
		wait(NULL);
		write(1, "\n", 1);
		write(1, av[2], strlen(av[2]));
		write(1, "\n", 1);
	}
	return (0);
}
