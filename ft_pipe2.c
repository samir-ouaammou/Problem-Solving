#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int	main(int ac, char **av)
{
	int		pipefd[2];
	char	buffer[1337];
	int		len;
	int		temp;

	if (ac < 2)
		exit(0);
	if (pipe(pipefd) < 0)
	{
		printf("Error (%s)\n", strerror(errno));
		exit(0);
	}
	temp = fork();
	if (temp > 0)
	{
		close(pipefd[0]);
		len = write(pipefd[1], av[1], strlen(av[1]));
		if (len < 0)
		{
			printf("Error (%s)\n", strerror(errno));
			exit(0);
		}
	}
	else
	{
		close(pipefd[1]);
		len = read(pipefd[0], buffer, sizeof(buffer));
		if (len < 0)
		{
			printf("Error (%s)\n", strerror(errno));
			exit(0);
		}
		buffer[len] = '\0';
		printf("Reult: (%s)\n", buffer);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	return (0);
}
