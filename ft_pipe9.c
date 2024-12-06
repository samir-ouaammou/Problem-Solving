#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>

int	main(int ac, char **av)
{
	int	fd[2];
	pid_t	pid;

	if (ac < 3)
		return (printf("Error (%s)\n", strerror(errno)), -1);
	
	char	*s1[]={"ls", "-l", NULL};
	char	*s2[]={"wc", "-l", NULL};
	
	if (pipe(fd) < 0)
		return (printf("Error (%s)\n", strerror(errno)), -1);	
	pid = fork();
	if (pid < 0)
		return (printf("Error (%s)\n", strerror(errno)), -1);	
	
	else if (pid == 0)
	{
		if (dup2(fd[1], 1) < 0)
			return (printf("Error (%s)\n", strerror(errno)), -1);
		close(fd[0]);
		execve("/bin/ls", s1, NULL);
		close(fd[1]);
		return (printf("Error (%s)\n", strerror(errno)), -1);
	}
	else
	{
		if (dup2(fd[0], 0) < 0)
			return (printf("Error (%s)\n", strerror(errno)), -1);
		wait(NULL);
		close(fd[1]);
		execve("/bin/wc", s2, NULL);
	}

	return (0);
}
