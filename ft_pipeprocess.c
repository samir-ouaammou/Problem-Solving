#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int	main(int ac, char **av)
{
	char	buffer[1337];
	int		fd[2];
	int		len;
	pid_t	pid;

	if (pipe(fd) < 0)
		return (printf("Error (%s)\n", strerror(errno)), 0);
	pid = fork();
	if (pid < 0)
		return (printf("Error (%s)\n", strerror(errno)), 0);
	if (pid == 0)
	{
		close(fd[0]);
		len = write(fd[1], av[1], strlen(av[1]));
		if (len < 0)
		{
			printf("Error (%s)\n", strerror(errno));
			exit(0);
		}
		close(fd[1]);
		exit(0);
	}
	else
	{
		wait(NULL);
		close(fd[1]);
		len = read(fd[0], buffer, sizeof(buffer));
		if (len < 0)
			return (printf("Error (%s)\n", strerror(errno)), 0);
		buffer[len] = '\0';
		write(1, buffer, strlen(buffer));
	}
	return (0);
}
