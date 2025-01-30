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

	str = av[1];
	av = &av[2];
	pid = fork();
	if (pid < 0)
		printf("Error (%s)\n", strerror(errno));
	if (pid == 0)
		execve(str, av, NULL);
	else
		wait(NULL);
	return (0);
}
