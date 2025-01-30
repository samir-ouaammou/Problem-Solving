#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int	main(int ac, char **av)
{
	int		pipefd[2];
	char	buffer[1337];
	ssize_t	len;

	if (ac < 2)
	{
		printf("Error\n");
		exit(0);
	}
	if (pipe(pipefd) < 0)
	{
		printf("Error (%s)\n", strerror(errno));
		exit(0);
	}
	len = write(pipefd[1], av[1], strlen(av[1]));
	if (len < 0)
	{
		printf("Error (%s)\n", strerror(errno));
		exit(0);
	}
	close(pipefd[1]);
	len = read(pipefd[0], buffer, sizeof(buffer));
	if (len < 0)
	{
		printf("Error (%s)\n", strerror(errno));
		exit(0);
	}
	close(pipefd[0]);
	printf("Result: (%s)\n", buffer);
	return (0);
}
