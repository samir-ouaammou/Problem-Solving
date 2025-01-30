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
	int		len;
	char	buffer[1337];

	if (ac < 3)
		exit(0);
	pid_t pid1, pid2;
	if (pipe(fd) < 0)
	{
		printf("Error (%s)\n", strerror(errno));
		exit(0);
	}
	pid1 = fork();
	if (pid1 > 0)
	{
		close(fd[0]);
		write(fd[1], av[1], strlen(av[1]));
		exit(0);
	}
	pid2 = fork();
	if (pid2 > 0)
	{
		close(fd[0]);
		write(fd[1], av[2], strlen(av[2]));
		exit(0);
	}
	close(fd[1]);
	printf("Result: ");
	while ((len = read(fd[0], buffer, sizeof(buffer))) > 0)
	{
		buffer[len] = '\n';
		printf("%s", buffer);
	}
	close(fd[0]);
	return (0);
}
