#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <errno.h>

int	main(int ac, char **av)
{
	if (ac < 2)
		exit(0);

	int	fd[2];
	pid_t	pid;
	char	buffer[1337];
	ssize_t	len;

	if (pipe(fd) < 0)
	{
		printf("Error (%s)\n", strerror(errno));
		exit(0);
	}
	pid = fork();
	if (pid > 0)
	{
		close(fd[0]);
		write (fd[1], av[1], strlen(av[1]));
		exit(0);
	}

	else
	{
		close(fd[1]);
		len = read(fd[0], buffer, sizeof(buffer));
		if (len < 0)
		{
			printf("Error (%s)\n", strerror(errno));
			exit(0);
		}
		buffer[len] = '\0';
		while (len > 0)
		{
			len--;
			if (buffer[len] == ' ')
				buffer[len] = '-';
		}
		printf("Result: (%s)\n", buffer);
	}
	close(fd[0]);
	close(fd[1]);

	return (0);
}