#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int	main(int ac, char **av)
{
	pid_t	pid;
	char	*str;

	if (ac < 3)
		return (0);
	if (access(av[1], F_OK) != 0)
		return (printf("Error (%s)\n", strerror(errno)), 0);
	if (access(av[1], X_OK) != 0)
		return (printf("Error (%s)\n", strerror(errno)), 0);
	str = strrchr(av[1], '/');
	if (strcmp(&str[1], av[2]) != 0)
		return (printf("Error (Commond not found)\n"));
	pid = fork();
	if (pid < 0)
		return (printf("Error (%s)\n", strerror(errno)), 0);
	if (pid == 0)
	{
		execve(av[1], &av[2], NULL);
		printf("Error (%s)\n", strerror(errno));
		exit(1);
	}
	else
		wait(NULL);
	return (0);
}
