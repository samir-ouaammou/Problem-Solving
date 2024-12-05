#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>

int	main(int ac, char **av)
{
	int	fd[2];
	pid_t	pid;
	char	buffer[1337];
	int	len;

	if (pipe(fd) < 0)
	{
		printf("Error (%s)\n", strerror(errno));
		exit(0);
	}
	len = write(fd[1], av[1], strlen(av[1]));	
	if (len < 0)
	{
		printf("Error (%s)\n", strerror(errno));
		exit(0);
	}
	len = read(fd[0], buffer, sizeof(buffer));
	if (len < 0)
	{
		printf("Error (%s)\n", strerror(errno));
		exit(0);
	}
	av = &av[2];
	execve(buffer, av, NULL);

	return (0);
}
