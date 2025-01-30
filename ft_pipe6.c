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
	pid_t	pid;
	ssize_t	len;
	char	buffer[1337];

	if (ac < 2)
		exit(0);
	if (pipe(fd) < 0)
	{
		printf("Error (%s)\n", strerror(errno));
		exit(0);
	}
	pid = fork();
	if (pid < 0)
	{
		printf("Error (%s)\n", strerror(errno));
		exit(0);
	}
	else if (pid == 0)
	{
		close(fd[0]);
		len = write(fd[1], av[1], strlen(av[1]));
		if (len < 0)
		{
			printf("Error (%s)\n", strerror(errno));
			exit(0);
		}
	}
	else
	{
		wait(NULL);
		len = read(fd[0], buffer, sizeof(buffer));
		if (len < 0)
		{
			printf("Error (%s)\n", strerror(errno));
			exit(0);
		}
		buffer[len] = '\0';
		len = 0;
		while (buffer[len])
		{
			if (buffer[len] >= 'a' && buffer[len] <= 'z')
				buffer[len] = buffer[len] - 32;
			len++;
		}
		printf("Result: (%s)\n", buffer);
	}
	close(fd[0]);
	close(fd[1]);
	return (0);
}
