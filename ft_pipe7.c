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
	
	int	fd[2];
	pid_t	pid;
	char	buffer[1337];
	int	len;

	if (pipe(fd) < 0)
		return (printf("Error (%s)\n", strerror(errno)), 0);
	pid = fork();
	if (pid < 0)
		return (printf("Error (%s)\n", strerror(errno)), 0);
	else if (pid == 0)
	{
		close(fd[0]);
		write (fd[1], av[1], strlen(av[1]));
		close(fd[1]);
		exit(1);
	}
	else
	{
		wait(NULL);
		close(fd[1]);
		len = read(fd[0], buffer, sizeof(buffer));
		if (len < 0)
			return (printf("Error (%s)\n", strerror(errno)), 0);
		buffer[len] = '\0';
		close(fd[0]);
	}
	printf("Result: (%s)\n", buffer);

	return (0);
}
